/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/camera.h"
#include "core/core.h"
#include "core/input.h"

namespace SLX {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
CoreCamera::CoreCamera() {
  position_ = { 0.0f, 0.0f, 10.0f };
  target_ = { 0.0f, 0.0f, 0.0f };
  movement_speed_ = 0.001f;
  rotation_speed_ = 0.001f;
  last_mouse_position_ = { 0.0f, 0.0f };
  is_navigation_enabled_ = true;
  setupPerspective(DirectX::XMConvertToRadians(45.0f), 1024.0f / 978.0f, 0.1f, 100.0f);
  setupView();
}

/// Default class destructor.
CoreCamera::~CoreCamera() {}


/*******************************************************************************
***                          Public setup methods                            ***
*******************************************************************************/

void CoreCamera::setupPerspective(const float field_of_view,
                                  const float aspect_ratio,
                                  const float z_near,
                                  const float z_far) {

  DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(field_of_view, aspect_ratio, z_near, z_far);
  DirectX::XMStoreFloat4x4(&projection_matrix_, projection);
}


void CoreCamera::setupOrthographic(const float left, const float right, 
                                    const float bottom, const float top, 
                                    const float z_near, const float z_far) {
  
  DirectX::XMMATRIX projection = DirectX::XMMatrixOrthographicOffCenterLH(left, right, bottom, top, z_near, z_far);
  DirectX::XMStoreFloat4x4(&projection_matrix_, projection);
}


void CoreCamera::setupView() {
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&target_);
  DirectX::XMVECTOR inverse_dir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(position, target));
  DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up, inverse_dir));
  up = DirectX::XMVector3Cross(inverse_dir, right);

  DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(position, target, up);

  DirectX::XMStoreFloat4x4(&view_matrix_, view);
}

/*******************************************************************************
***                          Public methods                                  ***
*******************************************************************************/

void CoreCamera::render(Object* obj) {

  if (obj->render3D_) {
    obj->render3D_->render(obj->transform());
  }
  uint32 num_children = obj->children_.size();
  for (uint32 i = 0; i < num_children; i++) {
    render(obj->children_[i]);
  }
}

/*******************************************************************************
***                            Setters & Getters                             ***
*******************************************************************************/

void CoreCamera::set_position(const float x, const float y, const float z) {
  position_ = { x, y, z };
  setupView();
}

void CoreCamera::set_target(const float x, const float y, const float z) {
  target_ = { x, y, z };
  setupView();
}

DirectX::XMVECTOR CoreCamera::position() {
  return DirectX::XMLoadFloat3(&position_);
}

DirectX::XMVECTOR CoreCamera::target() {
  return DirectX::XMLoadFloat3(&target_);
}

DirectX::XMVECTOR CoreCamera::up() {
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&target_);
  DirectX::XMVECTOR inverse_dir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(position, target));
  DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(inverse_dir, up));
  up = DirectX::XMVector3Cross(right, inverse_dir);
  return up;
}

DirectX::XMVECTOR CoreCamera::forward() {
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&target_);
  return DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(target, position));
}

DirectX::XMVECTOR CoreCamera::right() {
  DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target = DirectX::XMLoadFloat3(&target_);
  DirectX::XMVECTOR inverse_dir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(position, target));
  DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  return DirectX::XMVector3Normalize(DirectX::XMVector3Cross(inverse_dir, up));
}

DirectX::XMMATRIX CoreCamera::projectionMatrix() {
  return DirectX::XMLoadFloat4x4(&projection_matrix_);
}

DirectX::XMMATRIX CoreCamera::viewMatrix() {
  return DirectX::XMLoadFloat4x4(&view_matrix_);
}

void CoreCamera::update() {
  if (is_navigation_enabled_) {
    if (translate()) {
      setupView();
    }
    if (rotate()) {
      setupView();
    }
  }

}

bool CoreCamera::translate() {
  auto& input = Core::instance().input_;

  if (input.isMouseButtonPressed(Input::kMouseButton_Right)) {
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_A)) {
      DirectX::XMVECTOR scaled_right = DirectX::XMVectorScale(right(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position_), scaled_right));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&target_), scaled_right));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_D)) {
      DirectX::XMFLOAT3 r,f,u;
      DirectX::XMStoreFloat3(&r, right());
      DirectX::XMStoreFloat3(&u, up());
      DirectX::XMStoreFloat3(&f, forward());
      DirectX::XMVECTOR scaled_right = DirectX::XMVectorScale(right(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position_), scaled_right));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&target_), scaled_right));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_W)) {
      DirectX::XMVECTOR scaled_fwd = DirectX::XMVectorScale(forward(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position_), scaled_fwd));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&target_), scaled_fwd));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_S)) {
      DirectX::XMVECTOR scaled_fwd = DirectX::XMVectorScale(forward(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position_), scaled_fwd));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&target_), scaled_fwd));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_Q)) {
      DirectX::XMVECTOR scaled_up = DirectX::XMVectorScale(up(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position_), scaled_up));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&target_), scaled_up));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_E)) {
      DirectX::XMVECTOR scaled_up = DirectX::XMVectorScale(up(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position_), scaled_up));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&target_), scaled_up));
      return true;
    }
  }
  return false;
}

bool CoreCamera::rotate() {
  /*
  auto& input = Core::instance().input_;
  DirectX::XMFLOAT2 diff = { 0.0f, 0.0f };

  if (input.isMouseButtonPressed(Input::kMouseButton_Right)) {

    if (last_mouse_position_.x == diff.x && last_mouse_position_.y == diff.y) {
      last_mouse_position_ = input.mouse_position_;
    }
    else {
      // ROTATION AROUND LOCAL Y AXIS (UP VECTOR)
      // Calculamos la diferencia entre la ultima posicion y la actual.
      diff = { input.mouse_position_.x - last_mouse_position_.x, 
               input.mouse_position_.y - last_mouse_position_.y };
      glm::vec3 fw = forward();
      // Rotamos el vector forward alrededor del up.
      
      DirectX::XMVECTOR dir = DirectX::XMvectorrotate(forward(), diff.x * -rotation_speed_, up());
      // El nuevo target lo calculamos usando la proporcion de magnitud que tenia el previo.
      if (fw.x != 0.0f) {
        target_ = position_ + dir * ((target_.x - position_.x) / fw.x);
      }
      else if (fw.y != 0.0f) {
        target_ = position_ + dir * ((target_.y - position_.y) / fw.y);
      }
      else {
        target_ = position_ + dir * ((target_.z - position_.z) / fw.z);
      }

      // ROTATION AROUND LOCAL X AXIS (RIGHT VECTOR)
      fw = forward();
      dir = glm::rotate(fw, diff.y * -rotation_speed_, right());
      if (fw.x != 0.0f) {
        target_ = position_ + dir * ((target_.x - position_.x) / fw.x);
      }
      else if (fw.y != 0.0f) {
        target_ = position_ + dir * ((target_.y - position_.y) / fw.y);
      }
      else {
        target_ = position_ + dir * ((target_.z - position_.z) / fw.z);
      }

      // actualizamos la ultima posicion del raton.
      last_mouse_position_ = { MousePosX(), MousePosY() };
      return true;
    }
  }
  if (input.isMouseButtonUp(Input::kMouseButton_Right)) {
    last_mouse_position_ = { 0.0f, 0.0f };
  }
  */

  return false;
}

}; /* SLX */