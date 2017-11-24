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
  prop_rotation_speed_ = 0.055f;
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
  updateImGui();
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
  root_.transform().set_position(319.0f, 2.5f, 500.0f);
  root_.transform().rotate(0.0f, DirectX::XMConvertToRadians(105.0f), 0.0f);
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

void Airplane::updateImGui() {
  ImGui::PushID(this);
  if (ImGui::TreeNode("AirPlane")) {
    
    ImGui::SliderFloat("Prop Rotation Speed", &prop_rotation_speed_, 0.01f, 0.1f, "%.3f");
    updateImGuiRotationX();
    updateImGuiRotationZ();

    ImGui::TreePop();
  }
  ImGui::PopID();
}

void Airplane::updateImGuiRotationX() {
  ImGui::PushID("XRotation");
  if (ImGui::TreeNode("X Rotation")) {

    float32 rot_speed = x_rotation_speed_;
    float32 rot_to_idle_speed = x_rotation_to_idle_speed_;
    float32 constraint_degrees = x_rotation_constraint_degrees;

    ImGui::SliderFloat("Max Degrees", &x_rotation_constraint_degrees, 10.0f, 70.0f);
    ImGui::SliderFloat("Rotation Speed", &x_rotation_speed_, 0.0001f, 0.01f, "%.4f");
    ImGui::SliderFloat("Back To Idle Speed", &x_rotation_to_idle_speed_, 0.0001f, 0.01f, "%.4f");

    if (x_rotation_speed_ != rot_speed ||
        x_rotation_to_idle_speed_ != rot_to_idle_speed ||
        constraint_degrees != x_rotation_constraint_degrees) {
      setupLerpQuaternionConstraints();
    }

    ImGui::TreePop();
  }
  ImGui::PopID();
}

void Airplane::updateImGuiRotationZ() {
  ImGui::PushID("ZRotation");
  if (ImGui::TreeNode("Z Rotation")) {

    float32 rot_speed = z_rotation_speed_;
    float32 rot_to_idle_speed = z_rotation_to_idle_speed_;
    float32 constraint_degrees = z_rotation_constraint_degrees;

    ImGui::SliderFloat("Max Degrees", &z_rotation_constraint_degrees, 10.0f, 70.0f);
    ImGui::SliderFloat("Rotation Speed", &z_rotation_speed_, 0.0001f, 0.01f, "%.4f");
    ImGui::SliderFloat("Back To Idle Speed", &z_rotation_to_idle_speed_, 0.0001f, 0.01f, "%.4f");

    if (z_rotation_speed_ != rot_speed ||
        z_rotation_to_idle_speed_ != rot_to_idle_speed ||
        constraint_degrees != z_rotation_constraint_degrees) {
      setupLerpQuaternionConstraints();
    }

    ImGui::TreePop();
  }
  ImGui::PopID();
}


}; /* W3D */