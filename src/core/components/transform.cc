﻿/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "core/components/transform.h"
#include "core/object.h"

namespace SLX {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

TransformComponent::TransformComponent() {
  position_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
  rotation_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
  scale_ = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
  DirectX::XMStoreFloat4x4(&local_model_matrix_, DirectX::XMMatrixIdentity());
  parent_model_matrix_ = local_model_matrix_;
  owner_ = nullptr;

  calculateLocalModelMatrix();
}

TransformComponent::~TransformComponent() {
  owner_ = nullptr;
}

/*******************************************************************************
***                                 Methods                                  ***
*******************************************************************************/

void TransformComponent::set_owner(SLX::Object* owner) {
  owner_ = owner;
}

#pragma region POSITION

DirectX::XMVECTOR TransformComponent::position_vector() const  {
  return DirectX::XMLoadFloat3(&position_);
}

DirectX::XMFLOAT3 TransformComponent::position_float3() const {
  return position_;
}

DirectX::XMVECTOR TransformComponent::world_position_vector() {
  return DirectX::XMLoadFloat3(&world_position_float3());
}

DirectX::XMFLOAT3 TransformComponent::world_position_float3() {
  DirectX::XMFLOAT4X4 matrix;
  DirectX::XMStoreFloat4x4(&matrix, global_model_matrix());
  DirectX::XMFLOAT3 world_position = { matrix.m[0][3], matrix.m[1][3], matrix.m[2][3] };
  return world_position;
}

void TransformComponent::set_position(const DirectX::XMVECTOR position) {
  DirectX::XMStoreFloat3(&position_, position);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_position(const DirectX::XMFLOAT3 position) {
  position_ = position;
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_position(const float32 x, const float32 y, const float32 z) {
  position_ = DirectX::XMFLOAT3(x, y, z);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_world_position(const DirectX::XMVECTOR position) {
  DirectX::XMFLOAT3 pos;
  DirectX::XMStoreFloat3(&pos, position);
  set_position(pos.x - parent_model_matrix_.m[0][3],
               pos.y - parent_model_matrix_.m[1][3],
               pos.z - parent_model_matrix_.m[2][3]);
}

void TransformComponent::set_world_position(const DirectX::XMFLOAT3 position) {
  set_position(position.x - parent_model_matrix_.m[0][3],
               position.y - parent_model_matrix_.m[1][3],
               position.z - parent_model_matrix_.m[2][3]);
}

void TransformComponent::set_world_position(const float32 x, const float32 y, const float32 z) {
  set_position(x - parent_model_matrix_.m[0][3], 
               y - parent_model_matrix_.m[1][3], 
               z - parent_model_matrix_.m[2][3]);
}

#pragma endregion

#pragma region ROTATION

DirectX::XMVECTOR TransformComponent::rotation_vector() const {
  return DirectX::XMLoadFloat3(&rotation_);
}

DirectX::XMFLOAT3 TransformComponent::rotation_float3() const {
  return rotation_;
}

DirectX::XMVECTOR TransformComponent::world_rotation_vector() {

  DirectX::XMFLOAT4X4 m;
  DirectX::XMFLOAT3 euler;

  DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixTranspose(global_model_matrix()));
  float sp = -m._32;
  if (sp <= -1.0f) {
    euler.x = -1.570796f;
  }
  else if (sp >= 1.0f) {
    euler.x = 1.570796f;
  }
  else {
    euler.x = asin(sp);
  }
  if (fabs(sp) > 0.9999f) {
    euler.z = 0.0f;
    euler.y = atan2(-m._13, m._11);
  }
  else {
    euler.y = atan2(m._31, m._33);
    euler.z = atan2(m._12, m._22);
  }
  return DirectX::XMLoadFloat3(&euler);
}

DirectX::XMFLOAT3 TransformComponent::world_rotation_float3() {
  DirectX::XMFLOAT4X4 m;
  DirectX::XMFLOAT3 euler;

  DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixTranspose(global_model_matrix()));
  float sp = -m._32;
  if (sp <= -1.0f) {
    euler.x = -1.570796f;
  }
  else if (sp >= 1.0f) {
    euler.x = 1.570796f;
  }
  else {
    euler.x = asin(sp);
  }
  if (fabs(sp) > 0.9999f) {
    euler.z = 0.0f;
    euler.y = atan2(-m._13, m._11);
  }
  else {
    euler.y = atan2(m._31, m._33);
    euler.z = atan2(m._12, m._22);
  }
  return euler;
}

void TransformComponent::set_rotation(const float32 x, const float32 y, const float32 z) {
  rotation_ = DirectX::XMFLOAT3(x, y, z);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_rotation(const DirectX::XMFLOAT3 rotation) {
  rotation_ = rotation;
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_rotation(const DirectX::XMVECTOR rotation) {
  DirectX::XMStoreFloat3(&rotation_, rotation);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_world_rotation(const float32 x, const float32 y, const float32 z) {
  if (owner_->parent_) {
    DirectX::XMFLOAT3 rot = owner_->parent_->transform().world_rotation_float3();
    set_rotation(x - rot.x, y - rot.y, z - rot.z);
  }
  else {
    set_rotation(x, y, z);
  }
}

void TransformComponent::set_world_rotation(const DirectX::XMFLOAT3 rotation) {
  set_world_rotation(rotation.x, rotation.y, rotation.z);
}

void TransformComponent::set_world_rotation(const DirectX::XMVECTOR rotation) {
  DirectX::XMFLOAT3 rot;
  DirectX::XMStoreFloat3(&rot, rotation);
  set_world_position(rot);
}

#pragma endregion

#pragma region SCALE

DirectX::XMVECTOR TransformComponent::scale_vector() const {
  return DirectX::XMLoadFloat3(&scale_);
}

DirectX::XMFLOAT3 TransformComponent::scale_float3() const {
  return scale_;
}

void TransformComponent::set_scale(const float32 x, const float32 y, const float32 z) {
  scale_ = DirectX::XMFLOAT3(x, y, z);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_scale(const DirectX::XMVECTOR scale) {
  DirectX::XMStoreFloat3(&scale_, scale);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_scale(const DirectX::XMFLOAT3 scale) {
  scale_ = scale;
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_scale(const float32 uniform_scale) {
  scale_ = { uniform_scale, uniform_scale, uniform_scale };
  owner_->updateLocalModelAndChildrenMatrices();
}

#pragma endregion


#pragma region TRANSLATE

void TransformComponent::localTraslate(const DirectX::XMVECTOR traslation) {
  DirectX::XMFLOAT3 offset;
  DirectX::XMStoreFloat3(&offset, traslation);
  set_position(offset);
}

void TransformComponent::localTraslate(const DirectX::XMFLOAT3 traslation) {
  set_position(position_.x + traslation.x, 
                position_.y + traslation.y, 
                position_.z + traslation.z);
}

void TransformComponent::localTraslate(const float32 x, const float32 y, const float32 z) {
  set_position(position_.x + x, position_.y + y, position_.z + z);
}

void TransformComponent::worldTraslate(const DirectX::XMVECTOR traslation) {
  set_world_position(DirectX::XMVectorAdd(world_position_vector(),traslation));
}

void TransformComponent::worldTraslate(const DirectX::XMFLOAT3 traslation) {
  DirectX::XMFLOAT3 position;
  DirectX::XMStoreFloat3(&position, world_position_vector());
  set_world_position(position.x + traslation.x,
                      position.y + traslation.y,
                      position.z + traslation.z);
}

void TransformComponent::worldTraslate(const float32 x, const float32 y, const float32 z) {
  DirectX::XMFLOAT3 position;
  DirectX::XMStoreFloat3(&position, world_position_vector());
  set_world_position(position.x + x, position.y + y, position.z + z);
}

#pragma endregion

#pragma region ROTATE

void TransformComponent::rotate(const float32 x, const float32 y, const float32 z) {
  set_rotation(rotation_.x + x, rotation_.y + y, rotation_.z + z);
}

#pragma endregion


#pragma region FORWARD

DirectX::XMVECTOR TransformComponent::forward_vector() {
  return DirectX::XMVector4Normalize(DirectX::XMVector4Transform({ 0.0f, 0.0f, 1.0f, 0.0f }, DirectX::XMMatrixTranspose(global_model_matrix())));
}

DirectX::XMVECTOR TransformComponent::forward_local_vector() {
  calculateLocalModelMatrix();
  return DirectX::XMVector4Normalize(DirectX::XMVector4Transform({ 0.0f, 0.0f, 1.0f, 0.0f }, DirectX::XMMatrixTranspose(local_model_matrix())));
}

DirectX::XMFLOAT3 TransformComponent::forward_float3() {
  DirectX::XMFLOAT3 fwd_float3;
  DirectX::XMStoreFloat3(&fwd_float3, DirectX::XMVector4Normalize(DirectX::XMVector4Transform({ 0.0f, 0.0f, 1.0f, 0.0f }, 
                                                                  DirectX::XMMatrixTranspose(global_model_matrix()))));
  return fwd_float3;
}

DirectX::XMFLOAT3 TransformComponent::forward_local_float3() {
  DirectX::XMFLOAT3 fwd_float3;
  DirectX::XMStoreFloat3(&fwd_float3, DirectX::XMVector4Normalize(DirectX::XMVector4Transform({ 0.0f, 0.0f, 1.0f, 0.0f },
    DirectX::XMMatrixTranspose(local_model_matrix()))));
  return fwd_float3;
}

#pragma endregion

#pragma region MATRICES

DirectX::XMMATRIX TransformComponent::local_model_matrix() {
  return DirectX::XMLoadFloat4x4(&local_model_matrix_);
}

DirectX::XMMATRIX TransformComponent::global_model_matrix() {
    
  return DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&parent_model_matrix_),
                                    local_model_matrix());
}

void TransformComponent::calculateLocalModelMatrix() {

DirectX::XMMATRIX ret;
DirectX::XMVECTOR origin;
origin = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

DirectX::XMVECTOR quat_x, quat_y, quat_z;
quat_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rotation_.x);
quat_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), rotation_.y);
quat_z = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), rotation_.z);
	
ret = DirectX::XMMatrixTransformation(origin,
	                                    DirectX::XMQuaternionIdentity(),
											                DirectX::XMLoadFloat3(&scale_),
											                origin,
											                DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(DirectX::XMQuaternionMultiply(quat_z, quat_x), quat_y)),
											                DirectX::XMLoadFloat3(&position_));
DirectX::XMStoreFloat4x4(&local_model_matrix_, DirectX::XMMatrixTranspose(ret));
}

#pragma endregion

}; /* SLX */
