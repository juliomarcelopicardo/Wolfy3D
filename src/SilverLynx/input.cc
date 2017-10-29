/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/input.h"
#include "core/core.h"
#include "core/input.h"


namespace SLX {
namespace Input {


const float MousePosX() {
  return Core::instance().input_.mouse_position_.x;
}

const float MousePosY() {
  return Core::instance().input_.mouse_position_.y;
}

const bool IsMouseButtonDown(MouseButton button) {
  return Core::instance().input_.isMouseButtonDown(button);
}
const bool IsMouseButtonUp(MouseButton button) {
  return Core::instance().input_.isMouseButtonUp(button);
}
const bool IsMouseButtonPressed(MouseButton button) {
  return Core::instance().input_.isMouseButtonPressed(button);
}

const bool IsKeyboardButtonDown(KeyboardButton button) {
  return Core::instance().input_.isKeyboardButtonDown(button);
}
const bool IsKeyboardButtonUp(KeyboardButton button) {
  return Core::instance().input_.isKeyboardButtonUp(button);
}
const bool IsKeyboardButtonPressed(KeyboardButton button) {
  return Core::instance().input_.isKeyboardButtonPressed(button);
}


}; /* Input */
}; /* SLX */
