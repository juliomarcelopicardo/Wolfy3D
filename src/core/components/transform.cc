/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/components/transform.h"
#include "core/entity.h"

namespace W3D {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

TransformComponent::TransformComponent() {
  position_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
  quaternion_ = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f); // Identity
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

void TransformComponent::set_owner(W3D::Entity* owner) {
  owner_ = owner;
}

#pragma region POSITION

DirectX::XMVECTOR TransformComponent::position_vector() const  {
  return DirectX::XMLoadFloat3(&position_);
}

DirectX::XMFLOAT3 TransformComponent::position_float3() const {
  return position_;
}

DirectX::XMFLOAT4 TransformComponent::position_float4() const {
  return { position_.x, position_.y, position_.z, 1.0f };
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

void TransformComponent::set_position(const DirectX::XMVECTOR position_vector) {
  DirectX::XMStoreFloat3(&position_, position_vector);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_position(const DirectX::XMFLOAT3 position_vector) {
  position_ = position_vector;
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_position(const float32 x, const float32 y, const float32 z) {
  position_ = DirectX::XMFLOAT3(x, y, z);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_world_position(const DirectX::XMVECTOR position_vector) {
  DirectX::XMFLOAT3 pos;
  DirectX::XMStoreFloat3(&pos, position_vector);
  set_position(pos.x - parent_model_matrix_.m[0][3],
               pos.y - parent_model_matrix_.m[1][3],
               pos.z - parent_model_matrix_.m[2][3]);
}

void TransformComponent::set_world_position(const DirectX::XMFLOAT3 position_vector) {
  set_position(position_vector.x - parent_model_matrix_.m[0][3],
               position_vector.y - parent_model_matrix_.m[1][3],
               position_vector.z - parent_model_matrix_.m[2][3]);
}

void TransformComponent::set_world_position(const float32 x, const float32 y, const float32 z) {
  set_position(x - parent_model_matrix_.m[0][3], 
               y - parent_model_matrix_.m[1][3], 
               z - parent_model_matrix_.m[2][3]);
}

#pragma endregion

#pragma region ROTATION

DirectX::XMVECTOR TransformComponent::euler_rotation_vector() {
  return DirectX::XMLoadFloat3(&euler_rotation_float3());
}

DirectX::XMVECTOR TransformComponent::quaternion_rotation_vector() {
  return DirectX::XMLoadFloat4(&quaternion_);
}

DirectX::XMFLOAT3 TransformComponent::euler_rotation_float3() {
  DirectX::XMFLOAT4X4 m;
  DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixTranspose(local_model_matrix()));
  return getEulerAnglesFromModelMatrix(m);
}

DirectX::XMFLOAT4 TransformComponent::quaternion_rotation_float4() {
  return quaternion_;
}

DirectX::XMVECTOR TransformComponent::euler_world_rotation_vector() {

  DirectX::XMFLOAT4X4 m;

  DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixTranspose(global_model_matrix()));
  
  return DirectX::XMLoadFloat3(&getEulerAnglesFromModelMatrix(m));
}

DirectX::XMVECTOR TransformComponent::quaternion_world_rotation_vector() {
  DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationMatrix(global_model_matrix());
  return DirectX::XMQuaternionNormalize(quat);
}

DirectX::XMFLOAT3 TransformComponent::euler_world_rotation_float3() {
  DirectX::XMFLOAT4X4 m;

  DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixTranspose(global_model_matrix()));

  return getEulerAnglesFromModelMatrix(m);
}

DirectX::XMFLOAT4 TransformComponent::quaternion_world_rotation_float4() {
  DirectX::XMVECTOR temp, quat;
  DirectX::XMMatrixDecompose(&temp, &quat, &temp, global_model_matrix());
  DirectX::XMFLOAT4 quaternions;
  DirectX::XMStoreFloat4(&quaternions, DirectX::XMQuaternionNormalize(quat));
  return quaternions;
}

void TransformComponent::set_euler_rotation(const float32 x, const float32 y, const float32 z) {
  DirectX::XMVECTOR quat_x, quat_y, quat_z, temp;
  quat_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), x);
  quat_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), y);
  quat_z = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), z);
  temp = DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(quat_z, quat_x));
  temp = DirectX::XMQuaternionNormalize(DirectX::XMQuaternionMultiply(temp, quat_y));
  DirectX::XMStoreFloat4(&quaternion_, temp);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_euler_rotation(const DirectX::XMFLOAT3 rotation) {
  set_euler_rotation(rotation.x, rotation.y, rotation.z);
}

void TransformComponent::set_quaternion_rotation(const DirectX::XMFLOAT4 quaternion) {
  quaternion_ = quaternion;
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_euler_rotation(const DirectX::XMVECTOR rotation) {
  DirectX::XMFLOAT3 euler;
  DirectX::XMStoreFloat3(&euler, rotation);
  set_euler_rotation(euler);
}

void TransformComponent::set_quaternion_rotation(const DirectX::XMVECTOR quaternion) {
  DirectX::XMStoreFloat4(&quaternion_, quaternion);
  owner_->updateLocalModelAndChildrenMatrices();
}

void TransformComponent::set_euler_world_rotation(const float32 x, const float32 y, const float32 z) {
  if (owner_->parent_) {
    DirectX::XMFLOAT3 rot = owner_->parent_->transform().euler_world_rotation_float3();
    set_euler_rotation(x - rot.x, y - rot.y, z - rot.z);
  }
  else {
    set_euler_rotation(x, y, z);
  }
}

void TransformComponent::set_euler_world_rotation(const DirectX::XMFLOAT3 rotation) {
  set_euler_world_rotation(rotation.x, rotation.y, rotation.z);
}

void TransformComponent::set_quaternion_world_rotation(const DirectX::XMFLOAT4 rotation) {
  // TODO
  MessageBox(NULL, "SET QUATERNION WORLD ROTATION NOT IMPLEMENTED YET", "ERROR", MB_OK);
}

void TransformComponent::set_euler_world_rotation(const DirectX::XMVECTOR rotation) {
  DirectX::XMFLOAT3 rot;
  DirectX::XMStoreFloat3(&rot, rotation);
  set_euler_world_rotation(rot);
}

void TransformComponent::set_quaternion_world_rotation(const DirectX::XMVECTOR quaternion) {
  // TODO 
  MessageBox(NULL, "SET QUATERNION WORLD ROTATION NOT IMPLEMENTED YET", "ERROR", MB_OK);
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

void TransformComponent::traslate(const DirectX::XMVECTOR traslation) {
  DirectX::XMFLOAT3 offset;
  DirectX::XMStoreFloat3(&offset, traslation);
  set_position(offset);
}

void TransformComponent::traslate(const DirectX::XMFLOAT3 traslation) {
  set_position(position_.x + traslation.x, 
                position_.y + traslation.y, 
                position_.z + traslation.z);
}

void TransformComponent::traslate(const float32 x, const float32 y, const float32 z) {
  set_position(position_.x + x, position_.y + y, position_.z + z);
}

void TransformComponent::worldTraslate(const DirectX::XMVECTOR traslation) {
  set_world_position(DirectX::XMVectorAdd(world_position_vector(),traslation));
}

void TransformComponent::worldTraslate(const DirectX::XMFLOAT3 traslation) {
  DirectX::XMFLOAT3 position_vector;
  DirectX::XMStoreFloat3(&position_vector, world_position_vector());
  set_world_position(position_vector.x + traslation.x,
                      position_vector.y + traslation.y,
                      position_vector.z + traslation.z);
}

void TransformComponent::worldTraslate(const float32 x, const float32 y, const float32 z) {
  DirectX::XMFLOAT3 position_vector;
  DirectX::XMStoreFloat3(&position_vector, world_position_vector());
  set_world_position(position_vector.x + x, position_vector.y + y, position_vector.z + z);
}

#pragma endregion

#pragma region ROTATE

void TransformComponent::rotate(const float32 x, const float32 y, const float32 z) {
  DirectX::XMFLOAT3 euler = euler_rotation_float3();
  set_euler_rotation(euler.x + x, euler.y + y, euler.z + z);
}

void TransformComponent::rotate(const DirectX::XMFLOAT3 rotation) {
  set_euler_rotation(rotation.x + rotation.x, rotation.y + rotation.y, rotation.z + rotation.z);
}

void TransformComponent::worldRotate(const float32 x, const float32 y, const float32 z) {
  DirectX::XMFLOAT3 rotation;
  DirectX::XMStoreFloat3(&rotation, euler_world_rotation_vector());
  set_euler_world_rotation(rotation.x + x, rotation.y + y, rotation.z + z);
}

void TransformComponent::worldRotate(const DirectX::XMVECTOR rotation) {
  DirectX::XMFLOAT3 rot;
  DirectX::XMStoreFloat3(&rot, rotation);
  worldRotate(rot);
}

void TransformComponent::worldRotate(const DirectX::XMFLOAT3 rotation) {
  worldRotate(rotation.x, rotation.y, rotation.z);
}

void TransformComponent::rotate(const DirectX::XMVECTOR rotation) {
  DirectX::XMFLOAT3 rot, local_rot;
  DirectX::XMStoreFloat3(&rot, rotation);
  local_rot = euler_rotation_float3();
  set_euler_rotation(rot.x + local_rot.x, rot.y + local_rot.y, rot.z + local_rot.z);
}

#pragma endregion


#pragma region FORWARD

DirectX::XMVECTOR TransformComponent::world_forward_vector() {
  return DirectX::XMVector4Normalize(DirectX::XMVector4Transform({ 0.0f, 0.0f, 1.0f, 0.0f }, DirectX::XMMatrixTranspose(global_model_matrix())));
}

DirectX::XMVECTOR TransformComponent::forward_vector() {
  calculateLocalModelMatrix();
  return DirectX::XMVector4Normalize(DirectX::XMVector4Transform({ 0.0f, 0.0f, 1.0f, 0.0f }, DirectX::XMMatrixTranspose(local_model_matrix())));
}

DirectX::XMFLOAT3 TransformComponent::world_forward_float3() {
  DirectX::XMFLOAT3 fwd_float3;
  DirectX::XMStoreFloat3(&fwd_float3, DirectX::XMVector4Normalize(DirectX::XMVector4Transform({ 0.0f, 0.0f, 1.0f, 0.0f }, 
                                                                  DirectX::XMMatrixTranspose(global_model_matrix()))));
  return fwd_float3;
}

DirectX::XMFLOAT3 TransformComponent::forward_float3() {
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

  DirectX::XMMATRIX result;
  DirectX::XMVECTOR origin;
  origin = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	
  result = DirectX::XMMatrixTransformation(origin,
	                                         DirectX::XMQuaternionIdentity(),
											                     DirectX::XMLoadFloat3(&scale_),
											                     origin,
											                     DirectX::XMQuaternionNormalize(DirectX::XMLoadFloat4(&quaternion_)),
											                     DirectX::XMLoadFloat3(&position_));
  DirectX::XMStoreFloat4x4(&local_model_matrix_, DirectX::XMMatrixTranspose(result));
}

#pragma endregion




DirectX::XMFLOAT3 TransformComponent::getEulerAnglesFromModelMatrix(DirectX::XMFLOAT4X4 m) {
  DirectX::XMFLOAT3 euler;

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


}; /* W3D */
