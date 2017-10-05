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
  void setupWindowClassInfo();
  void setupWindowHandle(const char* window_display_name);
  void updateMessages();
  

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


}; /* WINDOW */

}; /* SLX */

#endif
