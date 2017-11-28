/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __CORE_INPUT_H__
#define __CORE_INPUT_H__ 1

#include "Wolfy3D/globals.h"
#include "Wolfy3D/input.h"
#include "DirectXMath.h"

namespace W3D {

const int32 kNumMouseButtons = 3;

/// Contains all the info of the button status.
struct ButtonStatus {
  ButtonStatus() : is_pressed(false),
                   is_up(false),
                   is_down(false) {}
  bool is_pressed;
  bool is_up;
  bool is_down;

  ///--------------------------------------------------------------------------
  /// @fn   resetStatus();
  ///
  /// @brief  Reset all the status (all values = false).
  ///--------------------------------------------------------------------------
  void resetStatus() {
    is_pressed = false;
    is_up = false;
    is_down = false;
  }
};


class CoreInput {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  CoreInput();
  
  /// Default class destructor.
  ~CoreInput();

/*******************************************************************************
***                           Public Methods                                 ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   ButtonStatus* getInputButton(const int32 key_id);
  ///
  /// @brief  Button getter based on a glfw key id
  /// @param  key_id id of the button in directx.
  /// @return ButtonStatus pointer.
  ///--------------------------------------------------------------------------
  ButtonStatus* getButton(const int32 key_id);

  ///--------------------------------------------------------------------------
  /// @fn   resetInputButtonStatus();
  ///
  /// @brief  Reset all the buttons status.
  ///--------------------------------------------------------------------------
  void resetInputButtonsStatus();

  ///--------------------------------------------------------------------------
  /// @fn   refreshButtonsUp();
  ///
  /// @brief  Refresh all the buttons up setting their UP state to false.
  ///--------------------------------------------------------------------------
  void refreshButtonsUp();

  ///--------------------------------------------------------------------------
  /// @fn   checkCursorPosition();
  ///
  /// @brief  Checks if the cursor is out of the window.
  ///--------------------------------------------------------------------------
  void checkCursorPosition();

/*******************************************************************************
***                             Getters                                      ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   bool isMouseButtonDown(Input::MouseButton button);
  ///
  /// @brief  Button status getter
  /// @param  button id of the button that we want to check.
  /// @return true if positive.
  ///--------------------------------------------------------------------------
  bool isMouseButtonDown(Input::MouseButton button);

  ///--------------------------------------------------------------------------
  /// @fn   bool isMouseButtonUp(Input::MouseButton button);
  ///
  /// @brief  Button status getter
  /// @param  button id of the button that we want to check.
  /// @return true if positive.
  ///--------------------------------------------------------------------------
  bool isMouseButtonUp(Input::MouseButton button);

  ///--------------------------------------------------------------------------
  /// @fn   bool isMouseButtonPressed(Input::MouseButton button);
  ///
  /// @brief  Button status getter
  /// @param  button id of the button that we want to check.
  /// @return true if positive.
  ///--------------------------------------------------------------------------
  bool isMouseButtonPressed(Input::MouseButton button);

  ///--------------------------------------------------------------------------
  /// @fn   bool isKeyboardButtonDown(Input::KeyboardButton button);
  ///
  /// @brief  Button status getter
  /// @param  button id of the button that we want to check.
  /// @return true if positive.
  ///--------------------------------------------------------------------------
  bool isKeyboardButtonDown(Input::KeyboardButton button);

  ///--------------------------------------------------------------------------
  /// @fn   bool isKeyboardButtonUp(Input::KeyboardButton button);
  ///
  /// @brief  Button status getter
  /// @param  button id of the button that we want to check.
  /// @return true if positive.
  ///--------------------------------------------------------------------------
  bool isKeyboardButtonUp(Input::KeyboardButton button);

  ///--------------------------------------------------------------------------
  /// @fn   bool isKeyboardButtonPressed(Input::KeyboardButton button);
  ///
  /// @brief  Button status getter
  /// @param  button id of the button that we want to check.
  /// @return true if positive.
  ///--------------------------------------------------------------------------
  bool isKeyboardButtonPressed(Input::KeyboardButton button);

/*******************************************************************************
***                        Public Attributes                                 ***
*******************************************************************************/
  /// Mouse Buttons status. 
  ButtonStatus mouse_button_[kNumMouseButtons];
  /// Keyboard A button status.
  ButtonStatus keyboard_A_button_;
  /// Keyboard W button status.
  ButtonStatus keyboard_W_button_;
  /// Keyboard S button status.
  ButtonStatus keyboard_S_button_;
  /// Keyboard D button status.
  ButtonStatus keyboard_D_button_;
  /// Keyboard Q button status.
  ButtonStatus keyboard_Q_button_;
  /// Keyboard E button status.
  ButtonStatus keyboard_E_button_;
  /// Keyboard C button status.
  ButtonStatus keyboard_C_button_;
  /// Keyboard F button status.
  ButtonStatus keyboard_F_button_;
  /// Keyboard O button status.
  ButtonStatus keyboard_O_button_;
  /// Keyboard P button status.
  ButtonStatus keyboard_P_button_;
  /// Keyboard Tab button status.
  ButtonStatus keyboard_Tab_button_;
  /// Keyboard SpaceBar button status.
  ButtonStatus keyboard_SpaceBar_button_;
  /// Keyboard Up button status.
  ButtonStatus keyboard_Up_button_;
  /// Keyboard Down button status.
  ButtonStatus keyboard_Down_button_;
  /// Keyboard Left button status.
  ButtonStatus keyboard_Left_button_;
  /// Keyboard Right button status.
  ButtonStatus keyboard_Right_button_;
  /// Keyboard Escape button status.
  ButtonStatus keyboard_Escape_button_;
  /// Keyboard Enter button status.
  ButtonStatus keyboard_Enter_button_;
  /// Keyboard Number button status
  ButtonStatus keyboard_Number_button_[10];
  /// Mouse wheel status
  float mouse_wheel_;
  /// Mouse cursor position.
  DirectX::XMFLOAT2 mouse_position_;


/*******************************************************************************
***                         Private Copy Constructor                         ***
*******************************************************************************/

private:

  /// Copy constructor.
  CoreInput(const CoreInput& copy);
  /// Assignment operator.
  CoreInput& operator=(const CoreInput& copy);


}; /* INPUTMANAGER */

}; /* W3D */

#endif
