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

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  void CoreWindow::init(const int32 width, const int32 height, const char * name) {

    instance_handle_ = GetModuleHandle(NULL);
    width_ = width;
    height_ = height;

    setupWindowClassInfo();
    setupWindowHandle(name);

    is_opened_ = true;
  }

  bool CoreWindow::updateMessages() {

    // We use PeekMessage because getmessage is blocking until receives a message, and PeekMessage is not blocking.
    if (PeekMessage(&message_, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message_); //In case we got a keyboard message, translate it in a right way.
      DispatchMessage(&message_); // Dispatch the message to the WinProc function.
    }
 
    if (message_.message == WM_QUIT)
      return false;

    return true;
  }

  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/

  void CoreWindow::setupWindowClassInfo() {

    //-------------- Fill window info (wndclassex). -----------------//
    window_class_info_.cbSize = sizeof(WNDCLASSEX); // assign struct size
    window_class_info_.hInstance = instance_handle_; // assign instance handle
    window_class_info_.lpfnWndProc = WndProc; // assign the callback function to receive events

                                              // Window style flags
    window_class_info_.style = CS_HREDRAW | CS_VREDRAW;

    // If we need more memory for the instance we would assign it here
    window_class_info_.cbClsExtra = 0;
    window_class_info_.cbWndExtra = 0;

    // Window cursor handles, icon, menu...
    window_class_info_.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    window_class_info_.hIconSm = window_class_info_.hIcon;
    window_class_info_.hCursor = LoadCursor(NULL, IDC_HAND);
    window_class_info_.hbrBackground = NULL;
    window_class_info_.lpszMenuName = NULL;

    // Assign window class name to be redirected to the instance
    window_class_info_.lpszClassName = "SilverLynxWindowClass";

    //-------------- Register class in the system -----------------//
    if (!RegisterClassEx(&window_class_info_)) {
      OutputDebugString(" ERROR: Window could not be registered.");
    }
  }

  void CoreWindow::setupWindowHandle(const char* window_display_name) {

    //-------------- Prepare quad -----------------//
    RECT quad = { 0, 0, width_, height_ };
    AdjustWindowRect(&quad, WS_OVERLAPPEDWINDOW, FALSE);

    //-------------- Create window -----------------//
    window_handle_ = CreateWindow(window_class_info_.lpszClassName, // class name
                                  window_display_name, // title name
                                  WS_OVERLAPPEDWINDOW, //  (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
                                  CW_USEDEFAULT, // X Position
                                  CW_USEDEFAULT, // Y Position
                                  quad.right - quad.left, // Width
                                  quad.bottom - quad.top, // Height
                                  NULL, // Parent window handle
                                  NULL, // Menu handle
                                  instance_handle_, // Instance application handle
                                  NULL);

    if (!window_handle_) {
      OutputDebugString(" ERROR: Window couldn't be created.");
    }

    ShowWindow(window_handle_, nCmdShow);
    SetForegroundWindow(window_handle_);
    SetFocus(window_handle_);
  }

  /*******************************************************************************
  ***                              Window callback                             ***
  *******************************************************************************/

  LRESULT CALLBACK CoreWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
