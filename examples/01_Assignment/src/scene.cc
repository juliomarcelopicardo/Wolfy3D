/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "scene.h"
#include "imgui/imgui.h"

namespace W3D {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Scene::Scene() {
  camera_mode_ = kCameraMode_Plane3rdPerson;
  debug_mode_speed_ = 1.0f;
  key_frame_step_time_ = 0.166666f;
  is_debug_mode_active_ = false;
  last_speed_saved_ = 2.0f;
  animations_speed_ = 2.0f;
}

Scene::~Scene() {}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Scene::init() {
  plane_.init();
  terrain_.init();
  sky_box_.init();
  initRobots();

  root_.transform().set_position(0.0f, 0.0f, 0.0f);
  root_.addChild(&sky_box_.root_);
  root_.addChild(&plane_.root_);
  root_.addChild(&terrain_.root_);
  root_.addChild(&landing_track_);
  landing_track_.addChild(&landing_track_camera_);

  for (uint32 i = 0; i < plane_.num_bullets_; ++i) {
    plane_.bullet_[i].init();
    root_.addChild(&plane_.bullet_[i].root_);
  }

  landing_track_.transform().set_position(319.0f, 2.5f, 500.0f);
  landing_track_camera_.transform().set_position(0.0f, 7.0f, 15.0f);
}

void Scene::update(const float32 delta_time) {
  updateImgui();
  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Enter) && 
      !plane_.is_plane_engine_active_) {
    plane_.is_plane_engine_active_ = true;
    activeRobots();
  }
  plane_.update(delta_time);
  updateRobots(delta_time);
  landing_track_.transform().rotate(0.0f, delta_time * 0.0005f, 0.0f);
  updateCameraMode();
  sky_box_.root_.transform().set_position(plane_.root_.transform().position_float3().x,
                                          0.0f, 
                                          plane_.root_.transform().position_float3().z);
}

void Scene::render() {}



/*******************************************************************************
***                            Setters and Getters                           ***
*******************************************************************************/


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Scene::updateCameraMode() {
  auto& camera = Core::instance().cam_;

  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_C)) {
    switchCameraMode();
  }

  switch (camera_mode_) {
  case kCameraMode_Plane3rdPerson: {
    camera.set_position(plane_.back_camera_.transform().world_position_float3());
    camera.set_target(plane_.plane_.transform().world_position_float3());
  } break;
  case kCameraMode_LandingTrack: {
    camera.set_position(landing_track_camera_.transform().world_position_float3());
    camera.set_target(landing_track_.transform().world_position_float3());
  } break;
  case kCameraMode_PlaneGun: {
    camera.set_position(plane_.gun_camera_.transform().world_position_float3());
    camera.set_target(plane_.turret_.transform().world_position_float3());
  } break;
  case kCameraMode_RedRobot: {
    camera.set_position(red_robot_.camera_node_.transform().world_position_float3());
    camera.set_target(red_robot_.body_.transform().world_position_float3());
  } break;
  case kCameraMode_GreenRobot: {} break;
  case kCameraMode_BlueRobot: {
    camera.set_position(blue_robot_.camera_node_.transform().world_position_float3());
    camera.set_target(blue_robot_.body_.transform().world_position_float3());
  } break;
  case kCameraMode_YellowRobot: {} break;
  };

}

void Scene::switchCameraMode() {
  auto& camera = Core::instance().cam_;
  switch (camera_mode_) {
  case kCameraMode_Plane3rdPerson: {
    camera_mode_ = kCameraMode_LandingTrack;
  } break;
  case kCameraMode_LandingTrack: {
    camera_mode_ = kCameraMode_PlaneGun;
  } break;
  case kCameraMode_PlaneGun: {
    camera_mode_ = kCameraMode_RedRobot;
  } break;
  case kCameraMode_RedRobot: {
    camera_mode_ = kCameraMode_GreenRobot;
    camera.moveTo(green_robot_.camera_node_.transform().world_position_float3(),
                  green_robot_.body_.transform().world_position_float3());
  } break;
  case kCameraMode_GreenRobot: {
    camera_mode_ = kCameraMode_BlueRobot;
  } break;
  case kCameraMode_BlueRobot: {
    camera_mode_ = kCameraMode_YellowRobot;
    camera.moveTo(yellow_robot_.camera_node_.transform().world_position_float3(),
                  yellow_robot_.body_.transform().world_position_float3());
  } break;
  case kCameraMode_YellowRobot: {
    camera_mode_ = kCameraMode_Plane3rdPerson;
  } break;
  };
}

void Scene::initRobots() {
  red_robot_.init();
  root_.addChild(&red_robot_.root_);
  red_robot_.root_.name_ = "Red Robot";
  red_robot_.set_material_color(1.0f, 0.0f, 0.0f);
  red_robot_.root_.transform().set_position(376.0f, 2.5f, 471.0f);
  red_robot_.root_.transform().set_euler_rotation(-0.0f, 0.2f, 0.0f);

  blue_robot_.init();
  root_.addChild(&blue_robot_.root_);
  blue_robot_.root_.name_ = "Blue Robot";
  blue_robot_.set_material_color(0.0f, 0.0f, 1.0f);
  blue_robot_.root_.transform().set_position(452.0f, 2.5f, 479.0f);
  blue_robot_.root_.transform().set_euler_rotation(-0.0f, -2.733f, 0.0f);

  green_robot_.init();
  root_.addChild(&green_robot_.root_);
  green_robot_.root_.name_ = "Green Robot";
  green_robot_.set_material_color(0.0f, 1.0f, 0.0f);
  green_robot_.root_.transform().set_position(444.0f, 2.5f, 452.0f);
  green_robot_.root_.transform().set_euler_rotation(-0.0f, 0.2f, 0.0f);

  yellow_robot_.init();
  root_.addChild(&yellow_robot_.root_);
  yellow_robot_.root_.name_ = "Yellow Robot";
  yellow_robot_.set_material_color(1.0f, 1.0f, 0.0f);
  yellow_robot_.root_.transform().set_position(386.0f, 2.5f, 497.0f);
  yellow_robot_.root_.transform().set_euler_rotation(-0.0f, -2.733f, 0.0f);
  setRototsAnimationSpeed(animations_speed_);
}

void Scene::updateRobots(const float32 delta_time) {
  float32 delta = delta_time;
  checkDistancesBetweenRobotsAndPlane();
  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Num1)) {
    red_robot_.anim_controller_.current_animation = &red_robot_.anim_controller_.idle;
    red_robot_.anim_controller_.current_animation->start(true, 0.5f);
    blue_robot_.anim_controller_.current_animation = &blue_robot_.anim_controller_.idle;
    blue_robot_.anim_controller_.current_animation->start(true, 0.5f);
    yellow_robot_.anim_controller_.current_animation = &yellow_robot_.anim_controller_.idle;
    yellow_robot_.anim_controller_.current_animation->start(true, 0.5f);
    green_robot_.anim_controller_.current_animation = &green_robot_.anim_controller_.idle;
    green_robot_.anim_controller_.current_animation->start(true, 0.5f);
  }
  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Num2)) {
    red_robot_.anim_controller_.current_animation = &red_robot_.anim_controller_.attack;
    red_robot_.anim_controller_.current_animation->start(true, 0.5f);
    blue_robot_.anim_controller_.current_animation = &blue_robot_.anim_controller_.attack;
    blue_robot_.anim_controller_.current_animation->start(true, 0.5f);
    yellow_robot_.anim_controller_.current_animation = &yellow_robot_.anim_controller_.attack;
    yellow_robot_.anim_controller_.current_animation->start(true, 0.5f);
    green_robot_.anim_controller_.current_animation = &green_robot_.anim_controller_.attack;
    green_robot_.anim_controller_.current_animation->start(true, 0.5f);
  }
  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Num3)) {
    red_robot_.anim_controller_.current_animation = &red_robot_.anim_controller_.die;
    red_robot_.anim_controller_.current_animation->start(true, 0.5f);
    blue_robot_.anim_controller_.current_animation = &blue_robot_.anim_controller_.die;
    blue_robot_.anim_controller_.current_animation->start(true, 0.5f);
    yellow_robot_.anim_controller_.current_animation = &yellow_robot_.anim_controller_.die;
    yellow_robot_.anim_controller_.current_animation->start(true, 0.5f);
    green_robot_.anim_controller_.current_animation = &green_robot_.anim_controller_.die;
    green_robot_.anim_controller_.current_animation->start(true, 0.5f);
  }
  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Tab)) {
    if (is_debug_mode_active_) {
      disableAnimationsDebugMode();
    }
    else {
      enableAnimationsDebugMode();
    }
  }
  if (is_debug_mode_active_) {
    delta = 0.0f;
    if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_E)) {
      delta = 166.0f; // Jump directly to the next key frame.
    }
  }
  if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_F)) {
    delta = delta_time / 5.0f / animations_speed_; // 2fps 
  }
  red_robot_.update(delta);
  blue_robot_.update(delta);
  yellow_robot_.update(delta);
  green_robot_.update(delta);
}

void Scene::activeRobots() {
  red_robot_.anim_controller_.current_animation = &red_robot_.anim_controller_.idle;
  red_robot_.anim_controller_.current_animation->start(true, 0.5f);
  blue_robot_.anim_controller_.current_animation = &blue_robot_.anim_controller_.idle;
  blue_robot_.anim_controller_.current_animation->start(true, 0.5f);
  green_robot_.anim_controller_.current_animation = &green_robot_.anim_controller_.idle;
  green_robot_.anim_controller_.current_animation->start(true, 0.5f);
  yellow_robot_.anim_controller_.current_animation = &yellow_robot_.anim_controller_.idle;
  yellow_robot_.anim_controller_.current_animation->start(true, 0.5f);
}

void Scene::setRototsAnimationSpeed(const float32 speed) {
  red_robot_.set_animations_speed(speed);
  blue_robot_.set_animations_speed(speed);
  yellow_robot_.set_animations_speed(speed);
  green_robot_.set_animations_speed(speed);
}

void Scene::enableAnimationsDebugMode() {
  is_debug_mode_active_ = true;
  last_speed_saved_ = animations_speed_;
  animations_speed_ = debug_mode_speed_;
  setRototsAnimationSpeed(animations_speed_);
}

void Scene::disableAnimationsDebugMode() {
  is_debug_mode_active_ = false;
  animations_speed_ = last_speed_saved_;
  setRototsAnimationSpeed(animations_speed_);
}


void Scene::checkDistancesBetweenRobotsAndPlane() {

  DirectX::XMVECTOR plane_pos = plane_.root_.transform().world_position_vector();

  red_robot_.checkDistanceToPlane(plane_pos);
  green_robot_.checkDistanceToPlane(plane_pos);
  yellow_robot_.checkDistanceToPlane(plane_pos);
  blue_robot_.checkDistanceToPlane(plane_pos);
}

void Scene::updateImgui() {
  ImGui::PushID(this);

  ImGui::Text("Real 3D Techniques assignment (first semester).");
  ImGui::Text("Made by Julio Marcelo Picardo. Student Number: 27026027.");
  ImGui::Separator();
  ImGui::Text("INSTRUCTIONS:");
  ImGui::Text("   KEY         - ACTION");
  ImGui::BulletText("ENTER       - Start scene and turn on the plane engine to start flying.");
  ImGui::BulletText("Q-A-O-P     - Airplane navigation.");
  ImGui::BulletText("SPACEBAR    - Fire.");
  ImGui::BulletText("C           - Switch between camera modes.");
  ImGui::BulletText("1-2-3       - Select default robots animation (1-Idle, 2-Attack, 3-Die).");
  ImGui::BulletText("TAB         - Enable / Disable animations debug mode.");
  ImGui::BulletText("E           - In debug mode, jump to the next animation step (10 per anim)");
  ImGui::BulletText("F           - If held down, will slowmotion the animations to 2fps");
  ImGui::Separator();

  if (ImGui::TreeNode("Scene and Animations")) {

    if (!is_debug_mode_active_) {

      float32 temp = animations_speed_;
      ImGui::SliderFloat("Animations Speed", &temp, 0.1f, 5.0f);
      if (temp != animations_speed_) {
        animations_speed_ = temp;
        setRototsAnimationSpeed(animations_speed_);
      }
      
      if (ImGui::Button("Active Debug Mode")) {
        enableAnimationsDebugMode();
      }

    }
    else {
      ImGui::BulletText("Press Mouse Wheel Button to debug animations steps.");
      if (ImGui::Button("Disable Debug Mode")) {
        disableAnimationsDebugMode();
      }
    }

    //ImGui::Combo("Select Default Animation")
    ImGui::TreePop();
  }



  ImGui::PopID();
}


}; /* W3D */