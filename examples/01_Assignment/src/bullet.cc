/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "bullet.h"
#include "imgui/imgui.h"

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Bullet::Bullet() {
  is_active_ = false;
  projectile_speed_ = 0.04f;
}

Bullet::~Bullet() {}

Bullet::Bullet(const Bullet & copy) {
  projectile_speed_ = copy.projectile_speed_;
  projectile_velocity_ = copy.projectile_velocity_;
}

Bullet Bullet::operator=(const Bullet & copy) {
  projectile_speed_ = copy.projectile_speed_;
  projectile_velocity_ = copy.projectile_velocity_;
  return (*this);
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Bullet::init() {
  initHierarchy();
  initTransforms();
  initGeometries();
  initMaterials();
  initRenderComponents();
}

void Bullet::update(const float32& delta_time) {
  if (is_active_) {
    root_.transform().traslate(projectile_velocity_.x * delta_time,
                               projectile_velocity_.y * delta_time,
                               projectile_velocity_.z * delta_time);
  }
}



/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Bullet::initHierarchy() {
  root_.addChild(&bullet_);
}

void Bullet::initGeometries() {
  geometry_.initPyramid(15, 0.1f, 1.0f);
}

void Bullet::initTransforms() {
  root_.transform().set_position(0.0f, 0.0f, 0.0f);
  bullet_.transform().set_position(0.0f, 0.0f, 0.0f);
  bullet_.transform().rotate(DirectX::XMConvertToRadians(90.0f), 0.0f, 0.0f);
}

void Bullet::initRenderComponents() {
  bullet_.addComponent(W3D::kComponentType_Render, &material_, &geometry_);
}

void Bullet::initMaterials() {
  material_.set_color(1.0f, 0.0f, 0.0f, 1.0f);
}



}; /* W3D */