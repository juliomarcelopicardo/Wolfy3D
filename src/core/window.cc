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

    setupWindowClassInfo();
    setupWindowHandle(name);

    is_opened_ = true;
  }

  void CoreWindow::setupWindowClassInfo() {

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
  }

  void CoreWindow::setupWindowHandle(const char* window_display_name) {

  //-------------- Preparamos el quad -----------------//
  RECT quad = { 0, 0, width_, height_ };
  AdjustWindowRect(&quad, WS_OVERLAPPEDWINDOW, FALSE);

  //-------------- Creamos la ventanica -----------------//
  window_handle_ = CreateWindow(window_class_info_.lpszClassName, // nombre de la clase.
    window_display_name, // Nombre mostrado en la barra de titulo.
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
}

void CoreWindow::updateMessages() {
  MSG message;
  // We use PeekMessage because getmessage is blocking until receives a message, and PeekMessage is not blocking.
  if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message); //In case we got a keyboard message, translate it in a right way.
    DispatchMessage(&message); // Dispatch the message to the WinProc function.
  }
 
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
