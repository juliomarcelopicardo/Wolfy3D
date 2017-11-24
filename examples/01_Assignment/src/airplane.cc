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
  color_ = { 1.0f, 1.0f, 1.0f, 1.0f };
  prop_rotation_speed_ = 1.0f;
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
  y_rotation_speed_ = 0.001f;
  up_traslation_speed_ = 0.01f;
  is_plane_engine_active_ = false;
  max_forward_speed_ = 0.015f;
  forward_speed_ = 0.0f;
  traslation_velocity_ = { 0.0f, 0.0f, 0.0f };
  forward_acceleration_ = 0.00001f;
  turret_rotation_speed_ = 0.001f;
  gun_rotation_speed_ = 0.002f;
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
  if (is_SpaceBar_key_down_) {
    is_plane_engine_active_ = true;
  }

  updateRotations(delta_time);
  updateTranslations(delta_time);
  updateImGui();
}


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

/*******************************************************************************
***                              Initializations                             ***
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
  material_.set_color(1.0f, 1.0f, 1.0f);
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


/*******************************************************************************
***                         Transformation updates                           ***
*******************************************************************************/

void Airplane::updateRotations(const float32& delta_time) {
    // PROP 
    prop_.transform().rotate(0.0f, 0.0f, prop_rotation_speed_ * delta_time * forward_speed_);

    // TURRET
    turret_.transform().rotate(0.0f, turret_rotation_speed_ * delta_time, 0.0f);

    // GUN
    gun_.transform().set_euler_rotation((DirectX::XMScalarSin((float32)Time() * gun_rotation_speed_) * 0.20f - 0.20f), 0.0f, 0.0f);

  if (is_plane_engine_active_ && forward_speed_ == max_forward_speed_) {
    // PLANE
    updateRotationLerpingValues(delta_time);
    DirectX::XMVECTOR rot_z = DirectX::XMLoadFloat4(&z_quaternion_rotation_);
    DirectX::XMVECTOR rot_x = DirectX::XMLoadFloat4(&x_quaternion_rotation_);
    plane_.transform().set_quaternion_rotation(DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(rot_z, rot_x)));

    // PLANE ROOT
    if (z_rotation_alpha_ != 0.0f) {
      root_.transform().worldRotate(0.0f, -z_rotation_alpha_ * y_rotation_speed_ * delta_time, 0.0f);
    }
  }
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
  if (is_S_key_pressed_) {
    x_rotation_alpha_ -= x_rotation_speed_ * delta_time;
    if (x_rotation_alpha_ < -1.0f) { x_rotation_alpha_ = -1.0f; }
  }
  else if (is_W_key_pressed_) {
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

void Airplane::updateTranslations(const float32 & delta_time) {

  traslation_velocity_ = { 0.0f, 0.0f, 0.0f };

  if (is_plane_engine_active_) {

    if (forward_speed_ < max_forward_speed_) {
      forward_speed_ += delta_time * forward_acceleration_;
    }
    else {
      forward_speed_ = max_forward_speed_;
    }

    traslation_velocity_ = plane_root_.transform().world_forward_float3();
    traslation_velocity_.x *= forward_speed_ * delta_time;
    traslation_velocity_.y *= forward_speed_ * delta_time;
    traslation_velocity_.z *= forward_speed_ * delta_time;

    if (x_rotation_alpha_ != 0.0f) {
      traslation_velocity_.y += -x_rotation_alpha_ * up_traslation_speed_ * delta_time;
    }

    root_.transform().worldTraslate(traslation_velocity_);
  }
}


/*******************************************************************************
***                               Input Update                               ***
*******************************************************************************/

void Airplane::updateInput() {
  is_A_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_A);
  is_D_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_D);
  is_W_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_W);
  is_S_key_pressed_ = Input::IsKeyboardButtonPressed(Input::kKeyboardButton_S);
  is_SpaceBar_key_down_ = Input::IsKeyboardButtonDown(Input::kKeyboardButton_SpaceBar);
}

/*******************************************************************************
***                              ImGui Update                                ***
*******************************************************************************/

void Airplane::updateImGui() {
  ImGui::PushID(this);
  if (ImGui::TreeNode("AirPlane")) {
    
    ImGui::ColorEdit3(" Color", &color_.x);
    material_.set_color(color_);
    ImGui::SliderFloat("Max Forward Speed", &max_forward_speed_, 0.001f, 0.1f);
    ImGui::SliderFloat("Prop Max Rotation Speed", &prop_rotation_speed_, 0.01f, 2.0f, "%.3f");
    ImGui::SliderFloat("Y Max Rotation Speed", &y_rotation_speed_, 0.001f, 0.1f, "%.4f");
    ImGui::SliderFloat("Y Max Traslation Speed", &up_traslation_speed_, 0.001f, 0.1f, "%.4f");
    ImGui::SliderFloat("Turret Rotation Speed", &turret_rotation_speed_, 0.001f, 0.1f, "%.4f");
    ImGui::SliderFloat("Gun Rotation Speed", &gun_rotation_speed_, 0.0001f, 0.01f, "%.4f");
    updateImGuiRotationX();
    updateImGuiRotationZ();

    ImGui::TreePop();
  }
  ImGui::PopID();
}

void Airplane::updateImGuiRotationX() {

    float32 rot_speed = x_rotation_speed_;
    float32 rot_to_idle_speed = x_rotation_to_idle_speed_;
    float32 constraint_degrees = x_rotation_constraint_degrees;

    ImGui::SliderFloat("X Constraint Degrees", &x_rotation_constraint_degrees, 10.0f, 70.0f);
    ImGui::SliderFloat("X Max Rotation Speed", &x_rotation_speed_, 0.0001f, 0.01f, "%.4f");
    ImGui::SliderFloat("X Max Back To Idle Speed", &x_rotation_to_idle_speed_, 0.0001f, 0.01f, "%.4f");

    if (x_rotation_speed_ != rot_speed ||
        x_rotation_to_idle_speed_ != rot_to_idle_speed ||
        constraint_degrees != x_rotation_constraint_degrees) {
      setupLerpQuaternionConstraints();
    }

}

void Airplane::updateImGuiRotationZ() {

    float32 rot_speed = z_rotation_speed_;
    float32 rot_to_idle_speed = z_rotation_to_idle_speed_;
    float32 constraint_degrees = z_rotation_constraint_degrees;

    ImGui::SliderFloat("Z Constraint Degrees", &z_rotation_constraint_degrees, 10.0f, 70.0f);
    ImGui::SliderFloat("Z Max Rotation Speed", &z_rotation_speed_, 0.0001f, 0.01f, "%.4f");
    ImGui::SliderFloat("Z Max Back To Idle Speed", &z_rotation_to_idle_speed_, 0.0001f, 0.01f, "%.4f");

    if (z_rotation_speed_ != rot_speed ||
        z_rotation_to_idle_speed_ != rot_to_idle_speed ||
        constraint_degrees != z_rotation_constraint_degrees) {
      setupLerpQuaternionConstraints();
    }

}


}; /* W3D */