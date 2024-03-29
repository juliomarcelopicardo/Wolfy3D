﻿/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/globals.h"
#include "core/directx.h"
#include "core/core.h"
#include <string>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"

namespace W3D {

  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

DirectXFramework::DirectXFramework() {
  device_ = 0;
  device_context_ = 0;
  swap_chain_ = 0;
  render_target_view_ = 0;
  depth_stencil_view_ = 0;
  depth_stencil_buffer_ = 0;
  depth_stencil_state_ = 0;
  raster_state_ = 0;
}

DirectXFramework::~DirectXFramework() {
  shutdown();
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

bool DirectXFramework::init() {

  float32 screen_width = (float32)Core::instance().window_.width_;
  float32 screen_height = (float32)Core::instance().window_.height_;

  // Init Video card adapter and settings
  if (!initVideoCard()) {
    MessageBox(NULL, "[D3D] Error initVideoCard.", "Error", MB_OK);
    return false;
  }

  // Init Swap chain description
  if (!initSwapChainDescription()) {
    MessageBox(NULL, "[D3D] Error initSwapChainDescription.", "Error", MB_OK);
    return false;
  }

  if (!initBackBuffer()) {
    MessageBox(NULL, "[D3D] Error initBackBuffer.", "Error", MB_OK);
    return false;
  }

  if (!initDepthBufferDescription()) {
    MessageBox(NULL, "[D3D] Error initDepthBufferDescription.", "Error", MB_OK);
    return false;
  }

  if (!initDepthStencilDescription()) {
    MessageBox(NULL, "[D3D] Error initDepthStencilDescription.", "Error", MB_OK);
    return false;
  }

  if (!initStencilView()) {
    MessageBox(NULL, "[D3D] Error initStencilView.", "Error", MB_OK);
    return false;
  }

  if (!initRaster()) {
    MessageBox(NULL, "[D3D] Error initRaster.", "Error", MB_OK);
    return false;
  }

  if (!initBlending()) {
    MessageBox(NULL, "[D3D] Error initBlending.", "Error", MB_OK);
    return false;
  }

  //////////////////////////////////////////////
  // Setup Viewport for Rendering

  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;
  viewport.Width = screen_width;
  viewport.Height = screen_height;

  // RSSetViewports() is a function that activates viewport structs.
  // The first parameter is the number of viewports being used, 
  // and the second parameter is the address of a list of pointers to the viewport structs.
  device_context_->RSSetViewports(1, &viewport);

  //////////////////////////////////////////////
  // Setup The Projection Matrix

  // Setup the projection matrix.
  float32 fov = DirectX::XM_PI / 4.0f;
  float32 aspect = screen_width / (float32)Core::instance().window_.height_;

  // Create the projection matrix for 3D rendering.
  DirectX::XMStoreFloat4x4(&projection_matrix_, DirectX::XMMatrixPerspectiveFovLH(fov, aspect, SCREEN_NEAR, SCREEN_DEPTH));

  // Initialize the world matrix to the identity matrix.
  DirectX::XMStoreFloat4x4(&world_matrix_, DirectX::XMMatrixIdentity());

  // Create an orthographic projection matrix for 2D rendering.
  DirectX::XMStoreFloat4x4(&ortho_matrix_, DirectX::XMMatrixOrthographicLH(screen_width, screen_height, SCREEN_NEAR, SCREEN_DEPTH));

	
//////////////////////////////////////////////
// Setup the ImGui binding
ImGui_ImplDX11_Init(W3D::Core::instance().window_.window_handle_, device_, device_context_);

  return true;

}

void DirectXFramework::startRenderFrame(float32 r, float32 g, float32 b, float32 a) {
  // clear the back buffer to a deep blue
  float32 color[4] = { r, g, b, a };
  device_context_->ClearRenderTargetView(render_target_view_, color);
  device_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
ImGui_ImplDX11_NewFrame();
}

void DirectXFramework::endRenderFrame() {
	
ImGui::Render();

  // Present the back buffer to the screen since rendering is complete.
  if (VSYNC_ENABLED) {
    // Lock to screen refresh rate.
    swap_chain_->Present(1, 0);
  } else {
    // Present as fast as possible.
    swap_chain_->Present(0, 0);
  }

}

void DirectXFramework::shutdown() {
  // close and release all existing COM objects
  // Before shutting down set to windowed mode or 
  // when you release the swap chain it will throw an exception.
  if (swap_chain_) {
    swap_chain_->SetFullscreenState(false, NULL);
  }

  if (raster_state_) {
    raster_state_->Release();
    raster_state_ = 0;
  }

  if (depth_stencil_view_) {
    depth_stencil_view_->Release();
    depth_stencil_view_ = 0;
  }

  if (depth_stencil_state_) {
    depth_stencil_state_->Release();
    depth_stencil_state_ = 0;
  }

  if (depth_stencil_buffer_) {
    depth_stencil_buffer_->Release();
    depth_stencil_buffer_ = 0;
  }

  if (render_target_view_) {
    render_target_view_->Release();
    render_target_view_ = 0;
  }

  if (device_context_) {
    device_context_->Release();
    device_context_ = 0;
  }

  if (device_) {
    device_->Release();
    device_ = 0;
  }

  if (swap_chain_) {
    swap_chain_->Release();
    swap_chain_ = 0;
  }
}

/*******************************************************************************
***                           Setters & Getters                              ***
*******************************************************************************/

ID3D11Device* DirectXFramework::device() {
  return device_;
}

ID3D11DeviceContext* DirectXFramework::deviceContext() {
  return device_context_;
}

ID3D11BlendState * DirectXFramework::blendState() {
  return blend_state_;
}

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

bool DirectXFramework::initVideoCard() {

  // Variables used for error checking
  HRESULT result;
  int32 error;

  // Video card variables
  IDXGIFactory* factory;
  IDXGIAdapter* adapter;
  IDXGIOutput* adapterOutput;
  DXGI_MODE_DESC* displayModeList;
  DXGI_ADAPTER_DESC adapterDesc;
  uint32 number_modes;

  uint32 i, numerator, denominator, stringLength;
  uint32 screen_width = (uint32)Core::instance().window_.width_;
  uint32 screen_height = (uint32)Core::instance().window_.height_;

  // Create a DirectX graphics interface factory.
  result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error creating DirectX graphics interface factory.", "Error", MB_OK);
    return false;
  }

  // Use the factory to create an adapter for the primary graphics interface (video card).
  result = factory->EnumAdapters(0, &adapter);
  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error creating adapter for primary graphics interface.", "Error", MB_OK);
    return false;
  }

  // Enumerate the primary adapter output (monitor).
  result = adapter->EnumOutputs(0, &adapterOutput);
  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error creating primary adapter output (monitor)", "Error", MB_OK);
    return false;
  }

  // Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &number_modes, NULL);
  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error obtaining number of modes DXGI_FORMAT_R8G8B8A8_UNORM.", "Error", MB_OK);
    return false;
  }

  // Create a list to hold all the possible display modes for this monitor/video card combination.
  displayModeList = new DXGI_MODE_DESC[number_modes];
  if (!displayModeList) {
    return false;
  }

  // Now fill the display mode list structures.
  result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &number_modes, displayModeList);
  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error obtaining display mode list structures.", "Error", MB_OK);
    return false;
  }

  // Now go through all the display modes and find the one that matches the screen width and height.
  // When a match is found store the numerator and denominator of the refresh rate for that monitor.
  for (i = 0; i < number_modes; i++) {
    if (displayModeList[i].Width == screen_width) {
      if (displayModeList[i].Height == screen_height) {
        numerator = displayModeList[i].RefreshRate.Numerator;
        denominator = displayModeList[i].RefreshRate.Denominator;
      }
    }
  }

  // Get the adapter (video card) description.
  result = adapter->GetDesc(&adapterDesc);
  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error obtaining adapter video card description.", "Error", MB_OK);
    return false;
  }

  // Store the dedicated video card memory in megabytes.
  video_card_memory_ = (W3D::int32)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

  // Convert the name of the video card to a charactver array and store it.
  error = wcstombs_s(&stringLength, video_card_description_, 128, adapterDesc.Description, 128);
  if (error != 0) {
    return false;
  }

  // Release the display mode list.
  delete[] displayModeList;
  displayModeList = 0;

  // Release the adapter output.
  adapterOutput->Release();
  adapterOutput = 0;

  // Release the adapter.
  adapter->Release();
  adapter = 0;

  // Release the factory.
  factory->Release();
  factory = 0;

  return true;
}

bool DirectXFramework::initSwapChainDescription() {

  HRESULT result;
  uint32 numerator, denominator;

  // create a struct to hold information about the swap chain
  DXGI_SWAP_CHAIN_DESC swap_chain_description;
  // clear out the struct for use
  ZeroMemory(&swap_chain_description, sizeof(DXGI_SWAP_CHAIN_DESC));

  // Set to a single back buffer.
  swap_chain_description.BufferCount = 1;

  // Set the width and height of the back buffer.
  swap_chain_description.BufferDesc.Width = Core::instance().window_.width_;
  swap_chain_description.BufferDesc.Height = Core::instance().window_.height_;

  // Set regular 32-bit surface for the back buffer.
  swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // use 32-bit color

  // Set the refresh rate of the back buffer.
  if (VSYNC_ENABLED) {
    swap_chain_description.BufferDesc.RefreshRate.Numerator = numerator;
    swap_chain_description.BufferDesc.RefreshRate.Denominator = denominator;
  } else {
    swap_chain_description.BufferDesc.RefreshRate.Numerator = 0;
    swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
  }

  // Turn multisampling off.
  swap_chain_description.SampleDesc.Count = 1;
  swap_chain_description.SampleDesc.Quality = 0;

  // Set to full screen or windowed mode.
  if (FULLSCREEN) {
    swap_chain_description.Windowed = false;
  } else {
    swap_chain_description.Windowed = true;
  }

  // fill the swap chain description struct
  swap_chain_description.BufferCount = 1;                                                      // one back buffer                  
  swap_chain_description.BufferDesc.Width = Core::instance().window_.width_;
  swap_chain_description.BufferDesc.Height = Core::instance().window_.height_;
  swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                        // how swap chain is to be used
  swap_chain_description.OutputWindow = Core::instance().window_.window_handle_;               // the window to be used
  swap_chain_description.SampleDesc.Count = 1;                                                 // how many multisamples 
  swap_chain_description.Windowed = TRUE;                                                      // windowed/full-screen mode
  swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                       // allows swithing between fullscreen and windowed.        
  swap_chain_description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;   // Set the scan line ordering to unspecified.
  swap_chain_description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                   // Set the scaling to unspecified.
  swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                                // Discard the back buffer contents after presenting.                                                     // Don't set the advanced flags.

                                                                                                // create a device, device context and swap chain using the information in the scd struct
  result = D3D11CreateDeviceAndSwapChain(NULL,
                                          D3D_DRIVER_TYPE_HARDWARE,
                                          NULL,
                                          NULL,
                                          NULL,
                                          NULL,
                                          D3D11_SDK_VERSION,
                                          &swap_chain_description,
                                          &swap_chain_,
                                          &device_,
                                          NULL,
                                          &device_context_);

  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error creating device context and swap chain.", "Error", MB_OK);
    return false;
  }

  return true;
}

bool DirectXFramework::initBackBuffer() {

  HRESULT result;

  /////////////////////////////////////////////
  // Create D3D Backbuffer (main render target)

  // An ID3D11Texture2D is an object that stores a flat image.
  ID3D11Texture2D *pBackBuffer;

  // get the address of the back buffer
  // The first parameter is the number of the back buffer to get. We are only using one back buffer on this chain, and it is back buffer #0.
  // The second parameter is a number identifying the ID3D11Texture2D COM object. __uuidof extracts the info from it.
  result = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  if (FAILED(result)) {
    return false;
  }

  // use the back buffer address to create the render target
  result = device_->CreateRenderTargetView(pBackBuffer, NULL, &render_target_view_);
  if (FAILED(result)) {
    MessageBox(NULL, "[D3D] Error creating back buffer rendertarget.", "Error", MB_OK);
    return false;
  }

  pBackBuffer->Release();
  pBackBuffer = 0;

  // set the render target as the back buffer
  device_context_->OMSetRenderTargets(1, &render_target_view_, NULL);

  return true;
}

bool DirectXFramework::initDepthBufferDescription() {

  HRESULT result;
  D3D11_TEXTURE2D_DESC depth_buffer_description;

  // Initialize the description of the depth buffer.
  ZeroMemory(&depth_buffer_description, sizeof(D3D11_TEXTURE2D_DESC));

  // Set up the description of the depth buffer.
  depth_buffer_description.Width = Core::instance().window_.width_;
  depth_buffer_description.Height = Core::instance().window_.height_;
  depth_buffer_description.MipLevels = 1;
  depth_buffer_description.ArraySize = 1;
  depth_buffer_description.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depth_buffer_description.SampleDesc.Count = 1;
  depth_buffer_description.SampleDesc.Quality = 0;
  depth_buffer_description.Usage = D3D11_USAGE_DEFAULT;
  depth_buffer_description.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depth_buffer_description.CPUAccessFlags = 0;
  depth_buffer_description.MiscFlags = 0;

  // Create the texture for the depth buffer using the filled out description.
  result = device_->CreateTexture2D(&depth_buffer_description, NULL, &depth_stencil_buffer_);
  if (FAILED(result)) {
    MessageBox(NULL, "Error creating the texture for the depth buffer.", "Error", MB_OK);
    return false;
  }

  return true;
}

bool DirectXFramework::initDepthStencilDescription() {

  HRESULT result;

  //////////////////////////////////////////////
  // Setup description of Stencil 

  D3D11_DEPTH_STENCIL_DESC depth_stencil_description;
  ZeroMemory(&depth_stencil_description, sizeof(D3D11_DEPTH_STENCIL_DESC));

  //Depth configuration
  depth_stencil_description.DepthEnable = true;
  depth_stencil_description.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depth_stencil_description.DepthFunc = D3D11_COMPARISON_LESS;

  // Stencil configuration
  depth_stencil_description.StencilEnable = true;
  depth_stencil_description.StencilReadMask = 0xFF;
  depth_stencil_description.StencilWriteMask = 0xFF;

  // Stencil operations in case pixel is front
  depth_stencil_description.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_description.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
  depth_stencil_description.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_description.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  // Stencil operations in case pixel is back
  depth_stencil_description.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_description.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
  depth_stencil_description.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
  depth_stencil_description.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

  // Create the depth stencil state.
  result = device_->CreateDepthStencilState(&depth_stencil_description, &depth_stencil_state_);
  if (FAILED(result)) {
    MessageBox(NULL, "Error creating the stencil state.", "Error", MB_OK);
    return false;
  }

  // Set the depth stencil state.
  device_context_->OMSetDepthStencilState(depth_stencil_state_, 1);

  return true;
}

bool DirectXFramework::initStencilView() {

  HRESULT result;

  //////////////////////////////////////////////
  // Setup Depth Stencil View

  D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
  ZeroMemory(&depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

  depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depth_stencil_view_desc.Texture2D.MipSlice = 0;

  result = device_->CreateDepthStencilView(depth_stencil_buffer_, &depth_stencil_view_desc, &depth_stencil_view_);
    
  // Bind the render target view and depth stencil buffer to the output render pipeline.
  device_context_->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);

  if (FAILED(result)) {
    MessageBox(NULL, "Error creating the stencil view description.", "Error", MB_OK);
    return false;
  }

  return true;
}

bool DirectXFramework::initRaster() {

  //////////////////////////////////////////////
  // Setup the raster description which will determine
  // how and what polygons will be drawn.

  HRESULT result;
  D3D11_RASTERIZER_DESC rasterizer_desc;
  ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

  rasterizer_desc.CullMode = D3D11_CULL_BACK; // The faces that we want to cull or not.
  rasterizer_desc.FillMode = D3D11_FILL_SOLID; // Determines how we want to render a primitive, for example solid or wireframe.
  rasterizer_desc.FrontCounterClockwise = true; // If we want to render the triangles counter clock wise or not
                                                // TODO: Calculate this value when depth buffer created.
  rasterizer_desc.DepthBias = 0;
  rasterizer_desc.DepthBiasClamp = 0.0f;
  rasterizer_desc.SlopeScaledDepthBias = 0.0f;
  rasterizer_desc.DepthClipEnable = true;
  rasterizer_desc.ScissorEnable = false; // If we have pixels outside a rectagle we will cull them (false until scissor activated)
  rasterizer_desc.MultisampleEnable = false;
  rasterizer_desc.AntialiasedLineEnable = false;

  result = device_->CreateRasterizerState(&rasterizer_desc, &raster_state_);
  if (FAILED(result)) {
    MessageBox(NULL, "Rasterizer not created.", "Warning", MB_OK);
    return false;
  }

  return true;
}

bool DirectXFramework::initBlending() {
  
  HRESULT result;
  D3D11_BLEND_DESC blend_desc;
  ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

  blend_desc.RenderTarget[0].BlendEnable = TRUE;
  blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
  blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
  blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
  blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
  blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
  blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
  blend_desc.IndependentBlendEnable = FALSE;
  blend_desc.AlphaToCoverageEnable = FALSE;


  result = device_->CreateBlendState(&blend_desc, &blend_state_);
  if (FAILED(result)) {
    MessageBox(NULL, "Rasterizer not created.", "Warning", MB_OK);
    return false;
  }
  

  return true;
}

}; /* W3D */
