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
#include <Windows.h>

namespace SLX {

class CoreWindow {

 public:

  /*******************************************************************************
  ***                        Public Attributes                                 ***
  *******************************************************************************/

  /// Window width.
  int32 width_;
  /// Window height.
  int32 height_;
  /// Specifies how the application windows should be display( to O.S.)
  int32 nCmdShow;
  /// Whether the window is opened or not.
  bool is_opened_;
  /// MSG struct to hold and peek new system messages.
  MSG message_;
  /// Struct holding all the window related information.
  WNDCLASSEX window_class_info_;
  /// Handle to the current application instance.
  HINSTANCE instance_handle_;
  /// Handle to the current window.
  HWND window_handle_;

  /// Window callback for handling events.
  static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  /// Default class constructor.
  CoreWindow();
  
  /// Default class destructor.
  ~CoreWindow();

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   init(const int32 width, const int32 height, const char* name = "SilverLynx Engine");
  ///
  /// @brief  Initializes the window with the specified width, height and window name.
  /// @param  width width of the window.
  /// @param  height height of the window.
  /// @param  name name of the window.
  ///--------------------------------------------------------------------------
  void init(const int32 width, const int32 height, const char* name = "SilverLynx Engine");

  ///--------------------------------------------------------------------------
  /// @fn   bool updateMessages();
  ///
  /// @brief  Updates and processes windows system messages on window.
  /// @return true if the window should keep updating, false if user closed it.
  ///--------------------------------------------------------------------------
  bool updateMessages();

  /*******************************************************************************
  ***                               Private                                    ***
  *******************************************************************************/

 private:

   /*******************************************************************************
   ***                              Private methods                             ***
   *******************************************************************************/

   ///--------------------------------------------------------------------------
   /// @fn  void setupWindowClassInfo();
   ///
   /// @brief  setups the window info such as window class name, mouse icons...
   ///--------------------------------------------------------------------------
   void setupWindowClassInfo();

   ///--------------------------------------------------------------------------
   /// @fn  setupWindowHandle(const char* window_display_name);
   ///
   /// @brief  creates the window handle with it's flag and initial config.
   ///--------------------------------------------------------------------------
   void setupWindowHandle(const char* window_display_name);


}; /* WINDOW */

}; /* SLX */

#endif
