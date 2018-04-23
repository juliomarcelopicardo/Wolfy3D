/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "robot.h"
#include "animation_controller.h"
#include "imgui/imgui.h"

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

AnimationController::AnimationController() {
  robot = nullptr;
  current_animation = nullptr;
}

AnimationController::~AnimationController() {}

AnimationController::AnimationController(const AnimationController& copy) {
  robot = copy.robot;
  current_animation = copy.current_animation;
  idle = copy.idle;
  attack = copy.attack;
  die = copy.die;
}

AnimationController& AnimationController::operator=(const AnimationController& copy) {
  robot = copy.robot;
  current_animation = copy.current_animation;
  idle = copy.idle;
  attack = copy.attack;
  die = copy.die;
  return *this;
}
/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void AnimationController::init() {
  idle.initFromFile("../data/animations/robot/RobotIdleAnimDAE.txt");
  attack.initFromFile("../data/animations/robot/RobotAttackAnimDAE.txt");
  die.initFromFile("../data/animations/robot/RobotDieAnimDAE.txt");
  idle.robot = robot;
  attack.robot = robot;
  die.robot = robot;
}

void AnimationController::update(const float32& delta_time) {
  if (current_animation) {
    current_animation->update(delta_time);
  }
}






/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/




}; /* W3D */