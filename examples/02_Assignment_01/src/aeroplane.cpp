//*********************************************************************************************
// File:			Aeroplane.cpp
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "aeroplane.h"
#include "SilverLynx/globals.h"

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Aeroplane::Aeroplane() {

  rotation_speed_ = 0.0025f;
  forward_speed_ = 0.01f;
  bullets_.empty();

}

Aeroplane::~Aeroplane() {

}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Aeroplane::init(void) {
	// Init geometry resources
	geo_plane_.initFromFile("./../data/geometries/plane/plane.x");
	geo_prop_.initFromFile("./../data/geometries/plane/prop.x");
	geo_turret_.initFromFile("./../data/geometries/plane/turret.x");
	geo_gun_.initFromFile("./../data/geometries/plane/gun.x");

  mat_.init();

	// Initialize Aeroplane components
	plane_root_.addComponent(SLX::ComponentType::Transform);
	plane_root_.init();
	
	camera_node_.addComponent(SLX::ComponentType::Transform);
	camera_node_.init();
	camera_node_.transform_->set_position(0.0f, 4.5f, -15.0f);
	plane_root_.addChild(&camera_node_);

	plane_.addComponent(SLX::ComponentType::Transform);
	plane_.addComponent(SLX::ComponentType::Render3D);
	plane_.render3D_->setup(&mat_, &geo_plane_);
	plane_.render3D_->init();
	plane_.init();
	plane_root_.addChild(&plane_);

	prop_.addComponent(SLX::ComponentType::Transform);
	prop_.addComponent(SLX::ComponentType::Render3D);
	prop_.render3D_->setup(&mat_, &geo_prop_);
	prop_.render3D_->init();
	prop_.init();
	prop_.transform_->set_position(0.0f, 0.0f, 1.9f);
	plane_.addChild(&prop_);

  turret_.addComponent(SLX::ComponentType::Transform);
  turret_.addComponent(SLX::ComponentType::Render3D);
  turret_.render3D_->setup(&mat_, &geo_turret_);
  turret_.render3D_->init();
  turret_.init();
  turret_.transform_->set_position(0.0f, 1.05f, -1.3f);
  plane_.addChild(&turret_);

  gun_.addComponent(SLX::ComponentType::Transform);
  gun_.addComponent(SLX::ComponentType::Render3D);
  gun_.render3D_->setup(&mat_, &geo_gun_);
  gun_.render3D_->init();
  gun_.init();
  gun_.transform_->set_position(0.0f, 0.5f, 0.0f);
  turret_.addChild(&gun_);
}

void Aeroplane::move_pitch(SLX::float32 pitch_limit_degrees, bool facing_upwards) {

  if (facing_upwards) {
    if (plane_root_.transform_->rotation_float3().x > DirectX::XMConvertToRadians(pitch_limit_degrees)) {
      plane_root_.transform_->rotate(-rotation_speed_, 0.0f, 0.0f);
    }
  }
  else {
    if (plane_root_.transform_->rotation_float3().x < DirectX::XMConvertToRadians(pitch_limit_degrees)) {
      plane_root_.transform_->rotate(rotation_speed_, 0.0f, 0.0f);
    }
  }
}

void Aeroplane::move_roll_yaw(SLX::float32 roll_limit_degrees, bool facing_leftwards, bool enable_yaw) {
  if (facing_leftwards) {
    if (plane_root_.transform_->rotation_float3().z < DirectX::XMConvertToRadians(roll_limit_degrees)) {
      plane_root_.transform_->rotate(0.0f, 0.0f, rotation_speed_);
    }
    if (enable_yaw) {
      move_yaw(true);
    }
  }
  else {
    if (plane_root_.transform_->rotation_float3().z > DirectX::XMConvertToRadians(roll_limit_degrees)) {
      plane_root_.transform_->rotate(0.0f, 0.0f, -rotation_speed_);
    }
    if (enable_yaw) {
      move_yaw(false);
    }
  }
}

void Aeroplane::move_forward() {
  DirectX::XMFLOAT3 forward;
  DirectX::XMStoreFloat3(&forward, DirectX::XMVectorScale(plane_root_.transform_->forward_vector(), forward_speed_));
  plane_root_.transform_->traslate(forward.x, forward.y, forward.z);
}

/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

void Aeroplane::set_speed(SLX::float32 forward_speed, SLX::float32 rotation_speed_radians) {
  forward_speed_ = forward_speed;
  rotation_speed_ = rotation_speed_radians;
}

SLX::Object& Aeroplane::root() {
  return plane_root_;
}

SLX::Object& Aeroplane::camera_node() {
  return camera_node_;
}

SLX::Object& Aeroplane::prop() {
  return prop_;
}

SLX::Object& Aeroplane::turret() {
  return turret_;
}

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Aeroplane::move_yaw(bool facing_leftwards) {
  if (facing_leftwards) {
    plane_root_.transform_->rotate(0.0f, -rotation_speed_, 0.0f);
  }
  else {
    plane_root_.transform_->rotate(0.0f, rotation_speed_, 0.0f);
  }
}
