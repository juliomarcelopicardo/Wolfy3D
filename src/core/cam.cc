/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/globals.h"
#include "core/entity.h"
#include "core/cam.h"
#include "core/core.h"
#include "core/input.h"
#include "core/entity.h"


namespace W3D {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
Cam::Cam() {
  position_ = { 0.0f, 0.0f, 10.0f };
  target_ = { 0.0f, 0.0f, 0.0f };
  movement_speed_ = 0.005f;
  rotation_speed_ = 0.005f;
  last_mouse_position_ = { 0.0f, 0.0f };
  is_navigation_enabled_ = true;
  setupPerspective(45.0f, 1024.0f / 978.0f, 0.1f, 1000.0f);
  setupView();
}

/// Default class destructor.
Cam::~Cam() {}


/*******************************************************************************
***                          Public setup methods                            ***
*******************************************************************************/

void Cam::setupPerspective(const float32 field_of_view,
                           const float32 aspect_ratio,
                           const float32 z_near,
                           const float32 z_far) {

  fovy_ = field_of_view;
  aspect_ = aspect_ratio;
  z_near_ = z_near;
  z_far_ = z_far;
  DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(field_of_view, aspect_ratio, z_near, z_far);
  DirectX::XMStoreFloat4x4(&projection_matrix_, projection);
}


void Cam::setupOrthographic(const float32 left, const float32 right, 
                            const float32 bottom, const float32 top, 
                            const float32 z_near, const float32 z_far) {
  
  fovy_ = DirectX::XMConvertToRadians(45.0f);
  aspect_ = (right - left) / (top - bottom);
  z_near_ = z_near;
  z_far_ = z_far;
  DirectX::XMMATRIX projection = DirectX::XMMatrixOrthographicOffCenterLH(left, right, bottom, top, z_near, z_far);
  DirectX::XMStoreFloat4x4(&projection_matrix_, projection);
}


void Cam::setupView() {
  DirectX::XMVECTOR position_vector = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target_vector = DirectX::XMLoadFloat3(&target_);
  DirectX::XMVECTOR inverse_dir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(position_vector, target_vector));
  DirectX::XMVECTOR up_vector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR right_vector = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up_vector, inverse_dir));
  up_vector = DirectX::XMVector3Cross(inverse_dir, right_vector);

  DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(position_vector, target_vector, up_vector);

  DirectX::XMStoreFloat4x4(&view_matrix_, view);
}

/*******************************************************************************
***                          Public methods                                  ***
*******************************************************************************/

void Cam::render(Entity* entity) {

  if (entity->render3D()) {
    entity->render3D()->render(&entity->transform());
  }
  uint32 num_children = entity->children_.size();
  for (uint32 i = 0; i < num_children; i++) {
    render(entity->children_[i]);
  }
}

/*******************************************************************************
***                            Setters & Getters                             ***
*******************************************************************************/

void Cam::set_position(const float32 x, const float32 y, const float32 z) {
  position_ = { x, y, z };
  setupView();
}

void Cam::set_position(const DirectX::XMVECTOR position) {
  DirectX::XMStoreFloat3(&position_, position);
  setupView();
}

void Cam::set_position(const DirectX::XMFLOAT3 position) {
  position_ = position;
  setupView();
}

void Cam::set_target(const float32 x, const float32 y, const float32 z) {
  target_ = { x, y, z };
  setupView();
}

void Cam::set_target(const DirectX::XMVECTOR target_vector) {
  DirectX::XMStoreFloat3(&target_, target_vector);
  setupView();
}

void Cam::set_target(const DirectX::XMFLOAT3 target_vector) {
  target_ = target_vector;
  setupView();
}

DirectX::XMVECTOR Cam::position_vector() {
  return DirectX::XMLoadFloat3(&position_);
}

DirectX::XMFLOAT3 Cam::position_float3() {
  return position_;
}

DirectX::XMVECTOR Cam::target_vector() {
  return DirectX::XMLoadFloat3(&target_);
}

DirectX::XMFLOAT3 Cam::target_float3() {
  return target_;
}

DirectX::XMVECTOR Cam::up_vector() {
  DirectX::XMVECTOR position_vector = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target_vector = DirectX::XMLoadFloat3(&target_);
  DirectX::XMVECTOR inverse_dir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(position_vector, target_vector));
  DirectX::XMVECTOR up_vector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  DirectX::XMVECTOR right_vector = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(inverse_dir, up_vector));
  up_vector = DirectX::XMVector3Cross(right_vector, inverse_dir);
  return up_vector;
}

DirectX::XMFLOAT3 Cam::up_float3() {
  DirectX::XMFLOAT3 up;
  DirectX::XMStoreFloat3(&up, up_vector());
  return up;
}

DirectX::XMVECTOR Cam::forward_vector() {
  DirectX::XMVECTOR position_vector = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target_vector = DirectX::XMLoadFloat3(&target_);
  return DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(target_vector, position_vector));
}

DirectX::XMFLOAT3 Cam::forward_float3() {
  DirectX::XMFLOAT3 fwd;
  DirectX::XMStoreFloat3(&fwd, forward_vector());
  return fwd;
}

DirectX::XMVECTOR Cam::right_vector() {
  DirectX::XMVECTOR position_vector = DirectX::XMLoadFloat3(&position_);
  DirectX::XMVECTOR target_vector = DirectX::XMLoadFloat3(&target_);
  DirectX::XMVECTOR inverse_dir = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(position_vector, target_vector));
  DirectX::XMVECTOR up_vector = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
  return DirectX::XMVector3Normalize(DirectX::XMVector3Cross(inverse_dir, up_vector));
}

DirectX::XMFLOAT3 Cam::right_float3() {
  DirectX::XMFLOAT3 right;
  DirectX::XMStoreFloat3(&right, right_vector());
  return right;
}

DirectX::XMMATRIX Cam::projection_matrix() {
  return DirectX::XMLoadFloat4x4(&projection_matrix_);
}

DirectX::XMFLOAT4X4 Cam::projection_float4x4() {
  return projection_matrix_;
}

DirectX::XMMATRIX Cam::view_matrix() {
  return DirectX::XMLoadFloat4x4(&view_matrix_);
}

DirectX::XMFLOAT4X4 Cam::view_float4x4() {
  return view_matrix_;
}

void Cam::update() {
  if (is_navigation_enabled_) {
    if (translate()) {
      setupView();
    }
    if (rotate()) {
      setupView();
    }
  }

}

bool Cam::translate() {
  auto& input = Core::instance().input_;

  if (input.isMouseButtonPressed(Input::kMouseButton_Right)) {
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_A)) {
      DirectX::XMVECTOR scaled_right = DirectX::XMVectorScale(right_vector(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position_), scaled_right));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&target_), scaled_right));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_D)) {
      DirectX::XMFLOAT3 r,f,u;
      DirectX::XMStoreFloat3(&r, right_vector());
      DirectX::XMStoreFloat3(&u, up_vector());
      DirectX::XMStoreFloat3(&f, forward_vector());
      DirectX::XMVECTOR scaled_right = DirectX::XMVectorScale(right_vector(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position_), scaled_right));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&target_), scaled_right));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_W)) {
      DirectX::XMVECTOR scaled_fwd = DirectX::XMVectorScale(forward_vector(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position_), scaled_fwd));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&target_), scaled_fwd));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_S)) {
      DirectX::XMVECTOR scaled_fwd = DirectX::XMVectorScale(forward_vector(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position_), scaled_fwd));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&target_), scaled_fwd));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_Q)) {
      DirectX::XMVECTOR scaled_up = DirectX::XMVectorScale(up_vector(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&position_), scaled_up));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&target_), scaled_up));
      return true;
    }
    if (input.isKeyboardButtonPressed(Input::kKeyboardButton_E)) {
      DirectX::XMVECTOR scaled_up = DirectX::XMVectorScale(up_vector(), movement_speed_);
      DirectX::XMStoreFloat3(&position_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&position_), scaled_up));
      DirectX::XMStoreFloat3(&target_, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&target_), scaled_up));
      return true;
    }
  }
  return false;
}

bool Cam::rotate() {
  
  auto& input = Core::instance().input_;
  DirectX::XMFLOAT2 diff = { 0.0f, 0.0f };

  if (input.isMouseButtonPressed(Input::kMouseButton_Right)) {

    if (last_mouse_position_.x == diff.x && last_mouse_position_.y == diff.y) {
      last_mouse_position_ = input.mouse_position_;
    }
    else {
      // Calculamos la diferencia entre la ultima posicion y la actual.
      diff = { input.mouse_position_.x - last_mouse_position_.x, 
               input.mouse_position_.y - last_mouse_position_.y };
      
      DirectX::XMMATRIX rot_mat_horizontal = DirectX::XMMatrixRotationAxis(up_vector(), diff.x * rotation_speed_);
      DirectX::XMMATRIX rot_mat_vertical = DirectX::XMMatrixRotationAxis(right_vector(), diff.y * rotation_speed_);
      DirectX::XMMATRIX rot_result = DirectX::XMMatrixMultiply(rot_mat_horizontal, rot_mat_vertical);
      DirectX::XMFLOAT3 dir;
      DirectX::XMStoreFloat3(&dir, DirectX::XMVector4Transform(forward_vector(), rot_result));
      target_ = { position_.x + dir.x, position_.y + dir.y, position_.z + dir.z };

      // actualizamos la ultima posicion del raton.
      last_mouse_position_ = { Input::MousePosX(), Input::MousePosY() };
      return true;
    }
  }
  if (input.isMouseButtonUp(Input::kMouseButton_Right)) {
    last_mouse_position_ = { 0.0f, 0.0f };
  }
  

  return false;
}

}; /* W3D */
