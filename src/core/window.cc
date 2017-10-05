/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/window.h"
#include "core/core.h"

namespace SLX {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

CoreWindow::CoreWindow() {
  width_ = 800;
  height_ = 600;
  is_opened_ = false;
}

CoreWindow::~CoreWindow() {}

void CoreWindow::init(const int32 width, const int32 height, const char * name) {

  instance_handle_ = GetModuleHandle(NULL);
  width_ = width;
  height_ = height;

  //-------------- Rellenamos la info ventana (wndclassex). -----------------//
  window_class_info_.cbSize = sizeof(WNDCLASSEX); // le asignamos un tamaño a la estructura.
  window_class_info_.hInstance = instance_handle_; // Le decimos el handle de la instancia.
  window_class_info_.lpfnWndProc = WndProc; // Definimos la funcion callback para recibir eventos.

  // estilos posibles de ventana (TODO: Mirar los que hay), estos son para que se redimensione.
  window_class_info_.style = CS_HREDRAW | CS_VREDRAW;

  //Si necesitaramos mas memoria para la instancia, se indicaria en estos dos valores.
  window_class_info_.cbClsExtra = 0;
  window_class_info_.cbWndExtra = 0;

  // punteros o handles al cursor, icono, recursos de menu... por defecto no se usan.
  window_class_info_.hIcon = LoadIcon(NULL, IDI_WINLOGO);
  window_class_info_.hIconSm = window_class_info_.hIcon;
  window_class_info_.hCursor = LoadCursor(NULL, IDC_HAND);
  window_class_info_.hbrBackground = NULL;
  window_class_info_.lpszMenuName = NULL;

  // Le asignamos un nombre a la clase, para luego relacionarla con la instancia.
  window_class_info_.lpszClassName = "SilverLynxWindowClass";

  //-------------- Registramos la clase en el sistema. -----------------//
  if (!RegisterClassEx(&window_class_info_)) {
    OutputDebugString(" ERROR: No se ha podido registrar la clase de la ventana.");
  }

  //-------------- Preparamos el quad -----------------//
  RECT quad = { 0, 0, width_, height_ };
  AdjustWindowRect(&quad, WS_OVERLAPPEDWINDOW, FALSE);

  //-------------- Creamos la ventanica -----------------//
  window_handle_ = CreateWindow(window_class_info_.lpszClassName, // nombre de la clase.
                                name, // Nombre mostrado en la barra de titulo.
                                WS_OVERLAPPEDWINDOW, //  (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
                                CW_USEDEFAULT, // Posicion X
                                CW_USEDEFAULT, // Posicion Y
                                quad.right - quad.left, // Ancho
                                quad.bottom - quad.top, // Alto
                                NULL, // Handle a una ventana padre.
                                NULL, // Handle a un menu.
                                instance_handle_, // Handle a la handle de la instancia de la app.
                                NULL); // Opcional, no se lo que hace.

  if (!window_handle_) {
    OutputDebugString(" ERROR: No se ha podido crear la ventana.");
  }

  ShowWindow(window_handle_, nCmdShow);
  SetForegroundWindow(window_handle_);
  SetFocus(window_handle_);

  /////////////////////////////////////////////////////////////////
  // D3D Initialization
  ////////////////////////////////////////////////////////////////

  // create a struct to hold information about the swap chain
  DXGI_SWAP_CHAIN_DESC swap_chain_description;

  // clear out the struct for use
  ZeroMemory(&swap_chain_description, sizeof(DXGI_SWAP_CHAIN_DESC));

  // fill the swap chain description struct
  swap_chain_description.BufferCount = 1;                                    // one back buffer
  swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
  swap_chain_description.BufferDesc.Width = width_;                          // buffer width
  swap_chain_description.BufferDesc.Height = height_;                        // buffer height
  swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
  swap_chain_description.OutputWindow = window_handle_;                      // the window to be used
  swap_chain_description.SampleDesc.Count = 4;                               // how many multisamples
  swap_chain_description.Windowed = TRUE;                                    // windowed/full-screen mode
  swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allows swithing between fullscreen and windowed. 

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

#pragma region prueba

  ID3D11Texture2D* stencil_depth_buffer;
  D3D11_TEXTURE2D_DESC texture_stencil_depth_description;
  ZeroMemory(&texture_stencil_depth_description, sizeof(D3D11_TEXTURE2D_DESC));

  texture_stencil_depth_description.Width = width;
  texture_stencil_depth_description.Height = height;
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
  if (FAILED(result))
  {
    MessageBox(NULL, "Error creating texture", "Error", MB_OK);
  }

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

  ID3D11DepthStencilState* depth_stencil_state;
  device_->CreateDepthStencilState(&depth_stencil_description, &depth_stencil_state);
  device_context_->OMSetDepthStencilState(depth_stencil_state, 1);

  D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
  ZeroMemory(&depth_stencil_view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
  depth_stencil_view_desc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
  depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  depth_stencil_view_desc.Texture2D.MipSlice = 0;

  device_->CreateDepthStencilView(stencil_depth_buffer, &depth_stencil_view_desc, &depth_stencil_view);
  device_context_->OMSetRenderTargets(1, &backbuffer_, depth_stencil_view);

  ID3D11RasterizerState* rasterizer;
  D3D11_RASTERIZER_DESC rasterizer_desc;
  ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

  rasterizer_desc.FillMode = D3D11_FILL_SOLID; // Determines how we want to render a primitive, for example solid or wireframe.
  rasterizer_desc.CullMode = D3D11_CULL_BACK; // The faces that we want to cull or not.
  rasterizer_desc.FrontCounterClockwise = true; // If we want to render the triangles counter clock wise or not

                                                // TODO: Calculate this value when depth buffer created.
  rasterizer_desc.DepthBias = 0;
  rasterizer_desc.DepthBiasClamp = 0.0f;
  rasterizer_desc.SlopeScaledDepthBias = 0.0f;
  rasterizer_desc.DepthClipEnable = true;
  //TODOEND

  rasterizer_desc.ScissorEnable = false; // If we have pixels outside a rectagle we will cull them (false until scissor activated)
  rasterizer_desc.MultisampleEnable = false;
  rasterizer_desc.AntialiasedLineEnable = false;

  result = device_->CreateRasterizerState(&rasterizer_desc, &rasterizer);
  if (FAILED(result)) {
    MessageBox(NULL, "Rasterizer not created", "Warning", MB_OK);
  }

  device_context_->RSSetState(rasterizer);

#pragma endregion 

  D3D11_VIEWPORT viewport;
  ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width = width_;
  viewport.Height = height_;

  // RSSetViewports() is a function that activates viewport structs.
  // The first parameter is the number of viewports being used, 
  // and the second parameter is the address of a list of pointers to the viewport structs.
  device_context_->RSSetViewports(1, &viewport);

  is_opened_ = true;
}

void CoreWindow::close() {
  // close and release all existing COM objects
  swap_chain_->Release();
  device_->Release();
  backbuffer_->Release();
  device_context_->Release();
}

void CoreWindow::startRenderFrame(float r, float g, float b, float a) {
  MSG message;
  // We use PeekMessage because getmessage is blocking until receives a message, and PeekMessage is not blocking.
  if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message); //In case we got a keyboard message, translate it in a right way.
    DispatchMessage(&message); // Dispatch the message to the WinProc function.
  }
  // clear the back buffer to a deep blue
  device_context_->ClearRenderTargetView(backbuffer_, D3DXCOLOR(r,g,b,a));
  device_context_->ClearDepthStencilView(depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void CoreWindow::endRenderFrame() {
  // switch the back buffer and the front buffer
  swap_chain_->Present(0, 0);
}

/*******************************************************************************
***         Se entrara aqui cada vez que el sistema mande un mensaje         ***
*******************************************************************************/
LRESULT CALLBACK CoreWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  /* TODO: Entender que cojones pasa aqui dentro*/
  PAINTSTRUCT ps;
  HDC hdc;
  
  switch (message) {
    
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    SLX::Core::instance().window_.is_opened_ = false;
    break;


  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}

}; /* SLX */
