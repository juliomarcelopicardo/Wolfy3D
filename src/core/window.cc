/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/window.h"

namespace SLX {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

CoreWindow::CoreWindow() {
  width_ = 800;
  height_ = 600;
}

CoreWindow::~CoreWindow() {}

void CoreWindow::init(const int32 width, const int32 height, const char * name) {

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
  window_class_info_.hIcon = NULL;
  window_class_info_.hIconSm = NULL;
  window_class_info_.hCursor = NULL;
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
  swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
  swap_chain_description.OutputWindow = window_handle_;                      // the window to be used
  swap_chain_description.SampleDesc.Count = 4;                               // how many multisamples
  swap_chain_description.Windowed = TRUE;                                    // windowed/full-screen mode

                                                                             // create a device, device context and swap chain using the information in the scd struct
  D3D11CreateDeviceAndSwapChain(NULL,
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
}

void CoreWindow::close() {
  // close and release all existing COM objects
  swap_chain_->Release();
  device_->Release();
  device_context_->Release();
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
    break;

  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }

  return 0;
}

}; /* SLX */
