/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/globals.h"
#include "core/window.h"
#include "core/core.h"
#include "core/input.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"

namespace W3D {

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

    Core::instance().d3d_.init();
    Core::instance().init();

    is_opened_ = true;
  }

  bool CoreWindow::startFrame() {
    Core::instance().input_.refreshButtonsUp();
    if (!updateMessages()) {
      return false;
    }
    Core::instance().cam_.update();
    Core::instance().d3d_.startRenderFrame();
    setupCameraIntoImguiMenu();
    return true;
  }

  void CoreWindow::endFrame() {
    Core::instance().d3d_.endRenderFrame();
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

  void CoreWindow::shutdown() {
	  ImGui_ImplDX11_Shutdown();
    Core::instance().d3d_.shutdown();
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
    window_class_info_.lpszClassName = "Wolfy3DWindowClass";

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

  void CoreWindow::setupCameraIntoImguiMenu() {
    
    auto& camera = Core::instance().cam_;
    
    ImGui::PushID(&camera);

    if(ImGui::TreeNode("GoPro")) {
      DirectX::XMFLOAT3 temp;
      DirectX::XMStoreFloat3(&temp, camera.position());
      ImGui::DragFloat3("Position", &temp.x);
      camera.set_position(temp.x, temp.y, temp.z);
      DirectX::XMStoreFloat3(&temp, camera.target());
      ImGui::DragFloat3("Target", &temp.x);
      camera.set_target(temp.x, temp.y, temp.z);
      ImGui::TreePop();
    }

    ImGui::PopID();
  }

  /*******************************************************************************
  ***                              Window callback                             ***
  *******************************************************************************/

  LRESULT CALLBACK CoreWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;

  auto& input = W3D::Core::instance().input_;
	ImGuiIO& io = ImGui::GetIO();

	switch (message) {
	
		/////////////////////////////////
		// Window

		case WM_PAINT: {
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			W3D::Core::instance().window_.is_opened_ = false;
			break;
		}
		/* @TODO case WM_SIZE
		* reescale rendertargets for Imgui to prevent
		* distortion of the widgets when resizing the window.
		*/

		/////////////////////////////////
		// INPUT MOUSE
		case WM_LBUTTONDOWN: {
      io.MouseDown[0] = true; 
      input.mouse_button_[0].is_down = true;
      input.mouse_button_[0].is_pressed = true;
      input.mouse_button_[0].is_up = false;
      return true; 
    }
		case WM_LBUTTONUP: {
      io.MouseDown[0] = false; 
      input.mouse_button_[0].is_down = false;
      input.mouse_button_[0].is_pressed = false;
      input.mouse_button_[0].is_up = true;
      return true; 
    }
		case WM_RBUTTONDOWN: {
      io.MouseDown[1] = true;
      input.mouse_button_[1].is_down = true;
      input.mouse_button_[1].is_pressed = true;
      input.mouse_button_[1].is_up = false;
      return true; 
    }
		case WM_RBUTTONUP: {
      io.MouseDown[1] = false; 
      input.mouse_button_[1].is_down = false;
      input.mouse_button_[1].is_pressed = false;
      input.mouse_button_[1].is_up = true;
      return true; 
    }
		case WM_MBUTTONDOWN: {
      io.MouseDown[2] = true;
      input.mouse_button_[2].is_down = true;
      input.mouse_button_[2].is_pressed = true;
      input.mouse_button_[2].is_up = false;
      return true; 
    }
		case WM_MBUTTONUP: {
      io.MouseDown[2] = false; 
      input.mouse_button_[2].is_down = false;
      input.mouse_button_[2].is_pressed = false;
      input.mouse_button_[2].is_up = true;
      return true; 
    }
		case WM_MOUSEWHEEL: {
			io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
      input.mouse_wheel_ = io.MouseWheel;
			return true;
		}
		case WM_MOUSEMOVE: {
			io.MousePos.x = (signed short)(lParam);
			io.MousePos.y = (signed short)(lParam >> 16);
      input.mouse_position_.x = (float)(io.MousePos.x);
      input.mouse_position_.y = (float)(io.MousePos.y);
			return true;
		}
		case WM_KEYDOWN: {
      // Para probar y añadir nuevas teclas 
      /*
      char prueba[128] = "";
      sprintf(prueba, "Tecla: %d\n", wParam);
      OutputDebugString(prueba);
      */
      
      if (ButtonStatus* button = input.getButton(wParam)) {
        button->is_down = true;
        button->is_pressed = true;
        button->is_up = false;
      }
			if (wParam < 256)
				io.KeysDown[wParam] = 1;
			return true;
		}
		case WM_KEYUP: {
      if (ButtonStatus* button = input.getButton(wParam)) {
        button->is_down = false;
        button->is_pressed = false;
        button->is_up = true;
      }
			if (wParam < 256)
				io.KeysDown[wParam] = 0;
			return true;
		}
		case WM_CHAR: {
			// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
			if (wParam > 0 && wParam < 0x10000)
				io.AddInputCharacter((unsigned short)wParam);
			return true;
		}
    } // switch (message)

    return DefWindowProc(hWnd, message, wParam, lParam);
  }

}; /* W3D */
