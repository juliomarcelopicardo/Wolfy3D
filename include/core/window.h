/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include "silverlynx.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <Windows.h>


namespace SLX {

class CoreWindow {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/
  CoreWindow();
  ~CoreWindow();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  void init(const int32 width, const int32 height, const char* name = "SilverLynx Engine");
  void close();
  void startRenderFrame(float r = 0.0f, float g = 0.2f, float b = 0.4f, float a = 1.0f);
  void endRenderFrame();

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  int32 width_;
  int32 height_;
  bool is_opened_;

  WNDCLASSEX window_class_info_; // Esta es la clase que guarda la informacion de la ventana.
  HINSTANCE instance_handle_; // handle, id o puntero a la instancia actual (de la APP).
  HWND window_handle_; // Handle en esta ocasion de la ventana.
  int32 nCmdShow; // por defecto SW_SHOWNORMAL que no se lo que es.
  static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // callback de eventos.

/*******************************************************************************
***                         Private Copy Constructor                         ***
*******************************************************************************/
 private:
  CoreWindow(const CoreWindow& copy);
  CoreWindow& operator=(const CoreWindow& copy);

  // This variable is a pointer to a device. In Direct3D, a device is an object that is intended to be a virtual representation of your video adapter.
  // What this line of code means is that we will create a COM object called ID3D11Device.
  // When COM makes this object, we will ignore it, and access it only indirectly using this pointer.
  ID3D11Device *device_;
  // A device context is similar to a device, but it is responsible for managing the GPU
  // and the rendering pipeline(the device mostly handles video memory).
  // This object is used to render graphics and to determine how they will be rendered.
  ID3D11DeviceContext *device_context_;
  // the swap chain is the series of buffers which take turns being rendered on.
  IDXGISwapChain *swap_chain_;
  // Render target used to render our main window.
  ID3D11RenderTargetView *backbuffer_;
  ID3D11DepthStencilView *depth_stencil_view;


}; /* WINDOW */

}; /* SLX */

#endif
