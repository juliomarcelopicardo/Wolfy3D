/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "aeroplane.h"
#include "Wolfy3D/globals.h"
#include "imgui/imgui.h"

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Aeroplane::Aeroplane() {
  rotation_speed_ = 0.025f;
  forward_speed_ = 0.25f;
  bullet_speed_ = 0.6f;
  acceleration_ = 0.0f;
  bullets_.empty();
  engine_enabled_ = false;
}

Aeroplane::~Aeroplane() {
  for (std::vector<Bullet>::iterator it = bullets_.begin(); it != bullets_.end(); it++) {
    if (it->obj) delete it->obj;
  }
  bullets_.clear();
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Aeroplane::init(W3D::Entity* scene) {
	// Init geometry resources
	geo_plane_.initFromFile("./../data/geometries/plane/plane.x");
	geo_prop_.initFromFile("./../data/geometries/plane/prop.x");
	geo_turret_.initFromFile("./../data/geometries/plane/turret.x");
	geo_gun_.initFromFile("./../data/geometries/plane/gun.x");

	// Initialize Aeroplane components
  root_node_.transform().set_position(319.0f, -7.5f, 500.0f);
  root_node_.transform().rotate(0.0f, DirectX::XMConvertToRadians(105.0f), 0.0f);
  root_node_.addChild(&camera_node_);
  camera_node_.transform().set_position(0.0f, 4.15f, -15.0f);
  root_node_.addChild(&plane_root_);

  landing_node_.transform().set_position(root_node_.transform().position_float3());
  scene->addChild(&landing_node_);
  camera_landing_node_.transform().set_position(0.0f, 30.0f, -30.0f);
  landing_node_.addChild(&camera_landing_node_);

	plane_.addComponent(W3D::ComponentType::Render3D, &mat_, &geo_plane_);
	plane_root_.addChild(&plane_);

  prop_.addComponent(W3D::ComponentType::Render3D, &mat_, &geo_prop_);
  prop_.transform().set_position(0.0f, 0.0f, 1.9f);
  plane_.addChild(&prop_);

  turret_.addComponent(W3D::ComponentType::Render3D, &mat_, &geo_turret_);
  turret_.transform().set_position(0.0f, 1.05f, -1.3f);
  plane_.addChild(&turret_);

  gun_.addComponent(W3D::ComponentType::Render3D, &mat_, &geo_gun_);
  gun_.transform().set_position(0.0f, 0.5f, 0.0f);
  turret_.addChild(&gun_);

  camera_gun_node_.transform().set_position(0.0f, 5.0f, -15.0f);
  gun_.addChild(&camera_gun_node_);

  gun_node_.transform().set_position(0.0f, 0.0f, 2.0f);
  gun_node_.transform().set_scale(0.02f, 0.02f, 0.02f);
  gun_.addChild(&gun_node_);

  //////////////////////////////////
  // Bullet Initialization

  geo_bullet_.initFromFile("./../data/geometries/plane/bullet.x");

  bullets_.resize(kNumberOfBullets);
  
  W3D::int32 loops = bullets_.size();
  for (W3D::int32 i = 0; i < loops; i++) {
    bullets_[i].obj = new W3D::Entity();
    bullets_[i].obj->addComponent(W3D::ComponentType::Render3D, &mat_, &geo_bullet_);
    bullets_[i].obj->transform().set_position(-1000.0f, 0.0f, 0.0f);
    bullets_[i].obj->transform().set_scale(0.02f, 0.02f, 0.2f);
    bullets_[i].shot = false;
    scene->addChild(bullets_[i].obj);
  }
}

void Aeroplane::shoot() {
  
  // Shoot the next bullet in the magazine
  // If it reaches the maximum start shooting from 
  // The begining again
  
  if (current_bullet_ == bullets_.size()) {
    current_bullet_ = 0;
  }

  bullets_[current_bullet_].dir = gun_.transform().world_forward_vector();
  bullets_[current_bullet_].obj->transform().set_world_position(gun_node_.transform().world_position_vector());
  bullets_[current_bullet_].obj->transform().set_rotation(gun_.transform().world_rotation_float3());
  

  bullets_[current_bullet_].shot = true;
  current_bullet_++;
}

void Aeroplane::update() {
  DirectX::XMFLOAT3 forward;

  for (size_t i = 0; i < bullets_.size(); i++) {
    if (bullets_[i].shot) {
      DirectX::XMStoreFloat3(&forward, DirectX::XMVectorScale(bullets_[i].dir, bullet_speed_));
      bullets_[i].obj->transform().worldTraslate(forward.x, forward.y, forward.z);
    }
  }

  landing_node_.transform().set_rotation(0.0f, (W3D::float32)W3D::Time() * 0.001f, 0.0f);
  turret_.transform().set_rotation(0.0f, (W3D::float32)W3D::Time() * 0.001f, 0.0f);
  gun_.transform().set_rotation(sin((W3D::float32)W3D::Time() * 0.001f) * 0.25f + 0.25f, 0.0f, 0.0f);

  if (engine_enabled_) {
    prop().transform().set_rotation(0.0f, 0.0f, (W3D::float32)W3D::Time() * 0.01f * acceleration_);
    if (acceleration_ < 1.00f) {
      acceleration_ += (W3D::float32)W3D::Time() * 0.0000005f;
    }
  }
  else {
    if (acceleration_ > 0.0f) {
      acceleration_ -= (W3D::float32)W3D::Time() * 0.00000005f;
    }
  }
}

void Aeroplane::move_pitch(W3D::float32 pitch_limit_degrees, bool facing_upwards) {
  
  // Plane can't move up or down if the engine isn't fully started
  if (acceleration_ >= 0.50f) {
    if (facing_upwards) {
      if (plane_root_.transform().rotation_float3().x > DirectX::XMConvertToRadians(pitch_limit_degrees)) {
        plane_root_.transform().rotate(-rotation_speed_, 0.0f, 0.0f);
      }
    }
    else {
      if (plane_root_.transform().rotation_float3().x < DirectX::XMConvertToRadians(pitch_limit_degrees)) {
        plane_root_.transform().rotate(rotation_speed_, 0.0f, 0.0f);
      }
    }
  }
}

void Aeroplane::move_roll_yaw(W3D::float32 roll_limit_degrees, bool facing_leftwards, bool enable_yaw) {
  if (facing_leftwards) {
    if (plane_root_.transform().rotation_float3().z < DirectX::XMConvertToRadians(roll_limit_degrees)) {
      plane_root_.transform().rotate(0.0f, 0.0f, rotation_speed_);
    }
    if (enable_yaw) {
      move_yaw(true);
    }
  }
  else {
    if (plane_root_.transform().rotation_float3().z > DirectX::XMConvertToRadians(roll_limit_degrees)) {
      plane_root_.transform().rotate(0.0f, 0.0f, -rotation_speed_);
    }
    if (enable_yaw) {
      move_yaw(false);
    }
  }
}

void Aeroplane::move_forward() {
  if (engine_enabled_) {
    DirectX::XMFLOAT3 forward;
    DirectX::XMStoreFloat3(&forward, DirectX::XMVectorScale(plane_root_.transform().world_forward_vector(), forward_speed_ * acceleration_));
    root_node_.transform().traslate(forward.x, forward.y, forward.z);
  }
}

void Aeroplane::toggleCameraMode() {
  switch (camera_mode_) {
  case Aeroplane::CameraMode::Tail:
    camera_mode_ = CameraMode::Gun;
    break;
  case Aeroplane::CameraMode::Gun:
    camera_mode_ = CameraMode::AroundLanding;
    break;
  case Aeroplane::CameraMode::AroundLanding:
    camera_mode_ = CameraMode::Tail;
    break;
  }
}

void Aeroplane::update_camera_view(W3D::Cam* cam) {

  DirectX::XMFLOAT3 temp;
  W3D::Entity* camera_node;

  switch (camera_mode_) {
  case Aeroplane::CameraMode::Tail:
    camera_node = &camera_node_;
    break;
  case Aeroplane::CameraMode::Gun:
    camera_node = &camera_gun_node_;
    break;
  case Aeroplane::CameraMode::AroundLanding:
    camera_node = &camera_landing_node_;
    break;
  }

  DirectX::XMStoreFloat3(&temp, camera_node->transform().world_position_vector());
  cam->set_position(temp.x, temp.y, temp.z);

  if (camera_mode_ == Aeroplane::CameraMode::AroundLanding) {
    DirectX::XMStoreFloat3(&temp, landing_node_.transform().world_position_vector());
  }
  else {
    DirectX::XMStoreFloat3(&temp, root().transform().world_position_vector());
  }

  cam->set_target(temp.x, temp.y, temp.z);
}

void Aeroplane::imgui_debug() {
  ImGui::PushID(&root_node_);

  if (ImGui::TreeNode("Aeroplane")) {

    ImGui::Text("Engine Status: ");
    ImGui::SameLine();
    if (engine_enabled_) {
      ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Enabled");
    }
    else {
      ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Disabled");
      if (!engine_enabled_) {
        ImGui::SameLine();
        if (ImGui::Button("Turn On")) {
          engine_enabled_ = true;
        }
      }
    }

    ImGui::Text("Engine Loaded: %0.0f", acceleration_ * 100.0f);
    ImGui::Text("To move the airplane pitch engine must be atleast 50");
    ImGui::Text("Pitch Movement: ");
    ImGui::SameLine();
    if (acceleration_ <= 0.5f) {
      ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Locked");
    }
    else {
      ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Unlocked");
    }

    ImGui::Spacing();
    ImGui::Separator();

    ImGui::SetNextTreeNodeOpen(true);
    if (ImGui::TreeNode("Root")) {
      ImGui::PushID(&root_node_.transform().position_float3());
      W3D::float32 position[3];
      position[0] = root_node_.transform().position_float3().x;
      position[1] = root_node_.transform().position_float3().y;
      position[2] = root_node_.transform().position_float3().z;
      if (ImGui::DragFloat3("Position", position, 0.5f)) {
        root_node_.transform().set_position(position[0], position[1], position[2]);
      }

      W3D::float32 rotation[3];
      rotation[0] = root_node_.transform().world_rotation_float3().x;
      rotation[1] = root_node_.transform().world_rotation_float3().y;
      rotation[2] = root_node_.transform().world_rotation_float3().z;
      if (ImGui::DragFloat3("Rotation", rotation, 0.01f)) {
        root_node_.transform().set_world_rotation(rotation[0], rotation[1], rotation[2]);
      }
      ImGui::PopID();
      ImGui::TreePop();
    }

    if (ImGui::TreeNode("Tail Camera")) {
      ImGui::PushID(&camera_node_.transform().position_float3());
      W3D::float32 position[3];
      position[0] = camera_node_.transform().position_float3().x;
      position[1] = camera_node_.transform().position_float3().y;
      position[2] = camera_node_.transform().position_float3().z;
      if (ImGui::DragFloat3("Position", position, 0.5f)) {
        camera_node_.transform().set_position(position[0], position[1], position[2]);
      }

      W3D::float32 rotation[3];
      rotation[0] = camera_node_.transform().world_rotation_float3().x;
      rotation[1] = camera_node_.transform().world_rotation_float3().y;
      rotation[2] = camera_node_.transform().world_rotation_float3().z;
      if (ImGui::DragFloat3("Rotation", rotation, 0.01f)) {
        camera_node_.transform().set_world_rotation(rotation[0], rotation[1], rotation[2]);
      }
      ImGui::PopID();
      ImGui::TreePop();
    }

    if (ImGui::TreeNode("Gun Camera")) {
      ImGui::PushID(&camera_gun_node_.transform().position_float3());
      W3D::float32 position[3];
      position[0] = camera_gun_node_.transform().position_float3().x;
      position[1] = camera_gun_node_.transform().position_float3().y;
      position[2] = camera_gun_node_.transform().position_float3().z;
      if (ImGui::DragFloat3("Position", position, 0.5f)) {
        camera_gun_node_.transform().set_position(position[0], position[1], position[2]);
      }

      W3D::float32 rotation[3];
      rotation[0] = camera_gun_node_.transform().world_rotation_float3().x;
      rotation[1] = camera_gun_node_.transform().world_rotation_float3().y;
      rotation[2] = camera_gun_node_.transform().world_rotation_float3().z;
      if (ImGui::DragFloat3("Rotation", rotation, 0.01f)) {
        camera_gun_node_.transform().set_world_rotation(rotation[0], rotation[1], rotation[2]);
      }
      ImGui::PopID();
      ImGui::TreePop();
    }

    if (ImGui::TreeNode("Landing Camera")) {
      ImGui::PushID(&camera_landing_node_.transform().position_float3());
      W3D::float32 position[3];
      position[0] = camera_landing_node_.transform().position_float3().x;
      position[1] = camera_landing_node_.transform().position_float3().y;
      position[2] = camera_landing_node_.transform().position_float3().z;
      if (ImGui::DragFloat3("Position", position, 0.5f)) {
        camera_landing_node_.transform().set_position(position[0], position[1], position[2]);
      }

      W3D::float32 rotation[3];
      rotation[0] = camera_landing_node_.transform().world_rotation_float3().x;
      rotation[1] = camera_landing_node_.transform().world_rotation_float3().y;
      rotation[2] = camera_landing_node_.transform().world_rotation_float3().z;
      if (ImGui::DragFloat3("Rotation", rotation, 0.01f)) {
        camera_landing_node_.transform().set_world_rotation(rotation[0], rotation[1], rotation[2]);
      }
      ImGui::PopID();
      ImGui::TreePop();
    }
    ImGui::TreePop();
  }
  ImGui::PopID();
}

/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

void Aeroplane::set_speed(W3D::float32 forward_speed, W3D::float32 rotation_speed_radians) {
  forward_speed_ = forward_speed;
  rotation_speed_ = rotation_speed_radians;
}

W3D::Entity& Aeroplane::root() {
  return root_node_;
}

W3D::Entity& Aeroplane::prop() {
  return prop_;
}

W3D::Entity& Aeroplane::turret() {
  return turret_;
}

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Aeroplane::move_yaw(bool facing_leftwards) {
  if (facing_leftwards) {
    root_node_.transform().rotate(0.0f, -rotation_speed_, 0.0f);
  }
  else {
    root_node_.transform().rotate(0.0f, rotation_speed_, 0.0f);
  }
}
