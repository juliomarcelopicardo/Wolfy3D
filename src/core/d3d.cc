/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/d3d.h"
#include "core/core.h"

namespace SLX {


  DirectXFramework::DirectXFramework() {

  }

  DirectXFramework::~DirectXFramework() {
    // close and release all existing COM objects
    swap_chain_->Release();
    device_->Release();
    backbuffer_->Release();
    device_context_->Release();
  }

  void DirectXFramework::init() {

    /////////////////////////////////////////////////////////////////
    // D3D Initialization
    ////////////////////////////////////////////////////////////////

    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC swap_chain_description;

    // clear out the struct for use
    ZeroMemory(&swap_chain_description, sizeof(DXGI_SWAP_CHAIN_DESC));

    
    // fill the swap chain description struct
    swap_chain_description.BufferCount = 1;                                                      // one back buffer
    swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                       // use 32-bit color
    swap_chain_description.BufferDesc.Width = Core::instance().window_.width_;
    swap_chain_description.BufferDesc.Height = Core::instance().window_.height_;
    swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                        // how swap chain is to be used
    swap_chain_description.OutputWindow = Core::instance().window_.window_handle_;               // the window to be used
    swap_chain_description.SampleDesc.Count = 4;                                                 // how many multisamples                                              // quality of the multisampling
    swap_chain_description.Windowed = TRUE;                                                      // windowed/full-screen mode
    swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                       // allows swithing between fullscreen and windowed.        
    swap_chain_description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;   // Set the scan line ordering to unspecified.
    swap_chain_description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                   // Set the scaling to unspecified.
    swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                                // Discard the back buffer contents after presenting.                                                     // Don't set the advanced flags.
    
    // create a device, device context and swap chain using the information in the scd struct
    HRESULT result = D3D11CreateDeviceAndSwapChain(NULL,
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
  
    /////////////////////////////////////////////
    // Create D3D Backbuffer (main render target)

    // An ID3D11Texture2D is an object that stores a flat image.
    ID3D11Texture2D *pBackBuffer;

    // get the address of the back buffer
    // The first parameter is the number of the back buffer to get. We are only using one back buffer on this chain, and it is back buffer #0.
    // The second parameter is a number identifying the ID3D11Texture2D COM object. __uuidof extracts the info from it.
    swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    result = device_->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer_);
    pBackBuffer->Release();

    // set the render target as the back buffer
    device_context_->OMSetRenderTargets(1, &backbuffer_, NULL);

    /////////////////////////////////////////////
    // Create D3D Viewport

    ID3D11Texture2D* stencil_depth_buffer;
    D3D11_TEXTURE2D_DESC texture_stencil_depth_description;
    ZeroMemory(&texture_stencil_depth_description, sizeof(D3D11_TEXTURE2D_DESC));

    texture_stencil_depth_description.Width = SLX::Core::instance().window_.width_;
    texture_stencil_depth_description.Height = SLX::Core::instance().window_.height_;
    texture_stencil_depth_description.MipLevels = 1;
    texture_stencil_depth_description.ArraySize = 1;
    texture_stencil_depth_description.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    texture_stencil_depth_description.SampleDesc.Count = 1;
    texture_stencil_depth_description.SampleDesc.Quality = 0;
    texture_stencil_depth_description.Usage = D3D11_USAGE_DEFAULT;
    texture_stencil_depth_description.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    texture_stencil_depth_description.CPUAccessFlags = 0;
    texture_stencil_depth_description.MiscFlags = 0;
    result = device_->CreateTexture2D(&texture_stencil_depth_description, NULL, &stencil_depth_buffer);
    if (FAILED(result)) {
      MessageBox(NULL, "Error creating texture", "Error", MB_OK);
    }

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


    //////////////////////////////////////////////
    // Setup State of Stencil 

    ID3D11DepthStencilState* depth_stencil_state;
    device_->CreateDepthStencilState(&depth_stencil_description, &depth_stencil_state);
    device_context_->OMSetDepthStencilState(depth_stencil_state, 1);

    //////////////////////////////////////////////
    // Setup Depth Stencil View

    D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
    ZeroMemory(&depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

    depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
    depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depth_stencil_view_desc.Texture2D.MipSlice = 0;

    device_->CreateDepthStencilView(stencil_depth_buffer, &depth_stencil_view_desc, &depth_stencil_view);
    
    // Bind the render target view and depth stencil buffer to the output render pipeline.
    device_context_->OMSetRenderTargets(1, &backbuffer_, depth_stencil_view);

    //////////////////////////////////////////////
    // Setup the raster description which will determine
    // how and what polygons will be drawn.

    ID3D11RasterizerState* rasterizer;
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

    result = device_->CreateRasterizerState(&rasterizer_desc, &rasterizer);
    if (FAILED(result)) {
      MessageBox(NULL, "Rasterizer not created", "Warning", MB_OK);
    }

    // Now set the rasterizer state.
    device_context_->RSSetState(rasterizer);

    //////////////////////////////////////////////
    // Setup Viewport for Rendering

    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.Width = SLX::Core::instance().window_.width_;
    viewport.Height = SLX::Core::instance().window_.height_;

    // RSSetViewports() is a function that activates viewport structs.
    // The first parameter is the number of viewports being used, 
    // and the second parameter is the address of a list of pointers to the viewport structs.
    device_context_->RSSetViewports(1, &viewport);

    //////////////////////////////////////////////
    // Setup The Projection Matrix

    // Setup the projection matrix.
    float fov = (float)D3DX_PI / 4.0f;
    float aspect = (float)SLX::Core::instance().window_.width_ / (float)SLX::Core::instance().window_.height_;

    // Create the projection matrix for 3D rendering.
    D3DXMatrixPerspectiveFovLH(&projection_matrix_, fov, aspect, SCREEN_NEAR, SCREEN_DEPTH);

    // Initialize the world matrix to the identity matrix.
    D3DXMatrixIdentity(&world_matrix_);

    // Create an orthographic projection matrix for 2D rendering.
    D3DXMatrixOrthoLH(&ortho_matrix_, (float)SLX::Core::instance().window_.width_,
      (float)SLX::Core::instance().window_.height_, SCREEN_NEAR, SCREEN_DEPTH);

  }

  void DirectXFramework::startRenderFrame(float r, float g, float b, float a) {
    // clear the back buffer to a deep blue
    device_context_->ClearRenderTargetView(backbuffer_, D3DXCOLOR(r, g, b, a));
    device_context_->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
  }

  void DirectXFramework::endRenderFrame() {
    // switch the back buffer and the front buffer
    swap_chain_->Present(0, 0);
  }

  void DirectXFramework::shutdown() {
    // close and release all existing COM objects
    swap_chain_->Release();
    device_->Release();
    backbuffer_->Release();
    device_context_->Release();
  }

}; /* SLX */
