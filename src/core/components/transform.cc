/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
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

  TransformComponent::TransformComponent() : Component() {
    type_ = ComponentType::Transform;
    position_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    rotation_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    scale_ = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    DirectX::XMStoreFloat4x4(&local_model_matrix_, DirectX::XMMatrixIdentity());
    parent_model_matrix_ = local_model_matrix_;
  }

  TransformComponent::~TransformComponent() {

  }

  void TransformComponent::init() {
    calculateLocalModelMatrix();
  }

  void TransformComponent::update() {

  }

  void TransformComponent::shutdown() {

  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  DirectX::XMVECTOR TransformComponent::position() const  {
    return DirectX::XMLoadFloat3(&position_);
  }

  DirectX::XMFLOAT3 TransformComponent::position_float3() const {
    return position_;
  }

  DirectX::XMVECTOR TransformComponent::worldPosition() {
    DirectX::XMFLOAT4X4 matrix;
    DirectX::XMStoreFloat4x4(&matrix, global_model_matrix());
    DirectX::XMFLOAT3 world_position = { matrix.m[0][3], matrix.m[1][3], matrix.m[2][3] };
    return DirectX::XMLoadFloat3(&world_position);
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

  DirectX::XMVECTOR TransformComponent::rotation_vector() const {
    return DirectX::XMLoadFloat3(&rotation_);
  }

  DirectX::XMFLOAT3 TransformComponent::rotation_float3() const {
    return rotation_;
  }

  void TransformComponent::set_rotation(const float32 x, const float32 y, const float32 z) {
    rotation_ = DirectX::XMFLOAT3(x, y, z);
    owner_->updateLocalModelAndChildrenMatrices();
  }

  void TransformComponent::set_rotation(const DirectX::XMFLOAT3 rotation) {
    rotation_ = rotation;
    owner_->updateLocalModelAndChildrenMatrices();
  }

  void TransformComponent::rotate(const float32 x, const float32 y, const float32 z) {
    set_rotation(rotation_.x + x, rotation_.y + y, rotation_.z + z);
  }

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

  DirectX::XMMATRIX TransformComponent::local_model_matrix() {
    return DirectX::XMLoadFloat4x4(&local_model_matrix_);
  }

  DirectX::XMMATRIX TransformComponent::global_model_matrix() {
    
    return DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&parent_model_matrix_),
                                     local_model_matrix());
  }

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

  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/


  void TransformComponent::calculateLocalModelMatrix() {
    DirectX::XMMATRIX rotation, traslation, scale;

    rotation = DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z);
    traslation = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
    scale = DirectX::XMMatrixScaling(scale_.x, scale_.y, scale_.z);

    DirectX::XMStoreFloat4x4(&local_model_matrix_, DirectX::XMMatrixTranspose(scale * rotation * traslation));
  }

}; /* SLX */
