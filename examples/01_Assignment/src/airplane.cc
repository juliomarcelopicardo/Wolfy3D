/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "airplane.h"
#include "imgui/imgui.h"

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Airplane::Airplane() {
  prop_rotation_speed_ = 0.5f;
  z_rotation_constraint_degrees = 50.0f;
  z_rotation_alpha_ = 0.0f;
  z_rotation_speed_ = 0.001f;
  z_rotation_to_idle_speed_ = z_rotation_speed_ * 0.3f;
  z_quaternion_limit_[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
  z_quaternion_limit_[1] = { 0.0f, 0.0f, 0.0f, 1.0f };
  z_quaternion_rotation_ = { 0.0f, 0.0f, 0.0f, 1.0f };
  x_rotation_constraint_degrees = 50.0f;
  x_rotation_alpha_ = 0.0f;
  x_rotation_speed_ = 0.001f;
  x_rotation_to_idle_speed_ = x_rotation_speed_ * 0.3f;
  x_quaternion_limit_[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
  x_quaternion_limit_[1] = { 0.0f, 0.0f, 0.0f, 1.0f };
  x_quaternion_rotation_ = { 0.0f, 0.0f, 0.0f, 1.0f };
  quaternion_idle_rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
}

Airplane::~Airplane() {

}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Airplane::init() {
  initGeometries();
  initHierarchy();
  initTransforms();
  initRenderComponents();
  setupLerpQuaternionConstraints();
}

void Airplane::update(const float32& delta_time) {
  
  updateInput();
  updateRotations(delta_time);
  debugImgui(delta_time);
}


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Airplane::initGeometries() {  
  geo_plane_.initFromFile("../data/geometries/plane/plane.x");
  geo_prop_.initFromFile("../data/geometries/plane/prop.x");
  geo_turret_.initFromFile("../data/geometries/plane/turret.x");
  geo_gun_.initFromFile("../data/geometries/plane/gun.x");
}

void Airplane::initHierarchy() {  
  root_.addChild(&back_camera_);
  root_.addChild(&plane_root_);
  plane_root_.addChild(&plane_);
  plane_.addChild(&prop_);
  plane_.addChild(&turret_);
  turret_.addChild(&gun_);
  gun_.addChild(&bullet_spawn_point_);
}

void Airplane::initTransforms() {
  back_camera_.transform().set_position(0.0f, 7.0f, -25.0f);
  prop_.transform().set_position(0.0f, 0.0f, 1.9f);
  turret_.transform().set_position(0.0f, 1.05f, -1.3f);
  gun_.transform().set_position(0.0f, 0.5f, 0.0f);
  bullet_spawn_point_.transform().set_position(0.0f, 0.0f, 2.0f);
}

void Airplane::initRenderComponents() {
  plane_.addComponent(W3D::kComponentType_Render, &material_, &geo_plane_);
  prop_.addComponent(W3D::kComponentType_Render, &material_, &geo_prop_);
  turret_.addComponent(W3D::kComponentType_Render, &material_, &geo_turret_);
  gun_.addComponent(W3D::kComponentType_Render, &material_, &geo_gun_);
}

void Airplane::setupLerpQuaternionConstraints() {
  plane_.transform().set_euler_rotation(0.0f, 0.0f, -DirectX::XMConvertToRadians(z_rotation_constraint_degrees));
  z_quaternion_limit_[0] = plane_.transform().quaternion_rotation_float4();
  plane_.transform().set_euler_rotation(0.0f, 0.0f, DirectX::XMConvertToRadians(z_rotation_constraint_degrees));
  z_quaternion_limit_[1] = plane_.transform().quaternion_rotation_float4();
  plane_.transform().set_euler_rotation(-DirectX::XMConvertToRadians(x_rotation_constraint_degrees), 0.0f, 0.0f);
  x_quaternion_limit_[0] = plane_.transform().quaternion_rotation_float4();
  plane_.transform().set_euler_rotation(DirectX::XMConvertToRadians(x_rotation_constraint_degrees), 0.0f, 0.0f);
  x_quaternion_limit_[1] = plane_.transform().quaternion_rotation_float4();
  plane_.transform().set_euler_rotation(0.0f, 0.0f, 0.0f);
  quaternion_idle_rotation = plane_.transform().quaternion_rotation_float4();
}

void Airplane::updateRotations(const float32& delta_time) {

  // PROP 
  prop_.transform().rotate(0.0f, 0.0f, prop_rotation_speed_ * delta_time);

  // PLANE
  updateRotationLerpingValues(delta_time);
  DirectX::XMVECTOR rot_z = DirectX::XMLoadFloat4(&z_quaternion_rotation_);
  DirectX::XMVECTOR rot_x = DirectX::XMLoadFloat4(&x_quaternion_rotation_);
  plane_.transform().set_quaternion_rotation(DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(rot_z, rot_x)));
}

void Airplane::updateRotationLerpingValues(const float32 & delta_time) {
  updateRotationLerpingValuesX(delta_time);
  updateRotationLerpingValuesZ(delta_time);
}

void Airplane::updateRotationLerpingValuesZ(const float32 & delta_time) {
  
  // If any key is pressed -> rotate
  if (is_D_key_pressed_) {
    z_rotation_alpha_ -= z_rotation_speed_ * delta_time;
    if (z_rotation_alpha_ < -1.0f) { z_rotation_alpha_ = -1.0f; }
  }
  else if (is_A_key_pressed_) {
    z_rotation_alpha_ += z_rotation_speed_ * delta_time;
    if (z_rotation_alpha_ > 1.0f) { z_rotation_alpha_ = 1.0f; }
  }
  // else -> rotating back to idle.
  else {
    if (z_rotation_alpha_ <= 0.0f) {
      z_rotation_alpha_ += z_rotation_to_idle_speed_ * delta_time;
      if (z_rotation_alpha_ > 0.0f) { z_rotation_alpha_ = 0.0f; }
    }
    else {
      z_rotation_alpha_ -= z_rotation_to_idle_speed_ * delta_time;
      if (z_rotation_alpha_ < 0.0f) { z_rotation_alpha_ = 0.0f; }
    }
  }

  // Lerp to save the actual rotation.
  if (z_rotation_alpha_ > 0.0f) {
    z_quaternion_rotation_ = Math::QuaternionLerpFloat4(quaternion_idle_rotation, z_quaternion_limit_[1], z_rotation_alpha_);
  }
  else {
    z_quaternion_rotation_ = Math::QuaternionLerpFloat4(quaternion_idle_rotation, z_quaternion_limit_[0], z_rotation_alpha_ * -1.0f);
  }
}

void Airplane::updateRotationLerpingValuesX(const float32 & delta_time) {

  // If any key is pressed -> rotate
  if (is_W_key_pressed_) {
    x_rotation_alpha_ -= x_rotation_speed_ * delta_time;
    if (x_rotation_alpha_ < -1.0f) { x_rotation_alpha_ = -1.0f; }
  }
  else if (is_S_key_pressed_) {
    x_rotation_alpha_ += x_rotation_speed_ * delta_time;
    if (x_rotation_alpha_ > 1.0f) { x_rotation_alpha_ = 1.0f; }
  }
  // else -> rotating back to idle.
  else {
    if (x_rotation_alpha_ <= 0.0f) {
      x_rotation_alpha_ += x_rotation_to_idle_speed_ * delta_time;
      if (x_rotation_alpha_ > 0.0f) { x_rotation_alpha_ = 0.0f; }
    }
    else {
      x_rotation_alpha_ -= x_rotation_to_idle_speed_ * delta_time;
      if (x_rotation_alpha_ < 0.0f) { x_rotation_alpha_ = 0.0f; }
    }
  }

  // Lerp to save the actual rotation.
  if (x_rotation_alpha_ > 0.0f) {
    x_quaternion_rotation_ = Math::QuaternionLerpFloat4(quaternion_idle_rotation, x_quaternion_limit_[1], x_rotation_alpha_);
  }
  else {
    x_quaternion_rotation_ = Math::QuaternionLerpFloat4(quaternion_idle_rotation, x_quaternion_limit_[0], x_rotation_alpha_ * -1.0f);
  }
}

void Airplane::updateInput() {
  is_A_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_A);
  is_D_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_D);
  is_W_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_W);
  is_S_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_S);
}

void Airplane::debugImgui(const float32& delta_time) {
  float32 delta = delta_time;
  //ImGui::PushID(&plane_);
  if (ImGui::TreeNode("Debug Plane")) {
    ImGui::DragFloat("Z_ROTATION_ALPHA", &z_rotation_alpha_);
    ImGui::DragFloat("DELTA", &delta);
    ImGui::DragFloat("Z_ROTATION_SPEED", &z_rotation_speed_);
    ImGui::TreePop();
  }
  //ImGui::PopID();
}


}; /* W3D */