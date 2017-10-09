/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "core/components/transform.h"

namespace SLX {

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  TransformComponent::TransformComponent() : Component() {
    type_ = ComponentType::Transform;
    position_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    rotation_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    scale_ = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
  }

  TransformComponent::~TransformComponent() {

  }

  void TransformComponent::init() {

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


  void TransformComponent::set_position(const float32 x, const float32 y, const float32 z) {
    position_ = DirectX::XMFLOAT3(x, y, z);
  }

  DirectX::XMVECTOR TransformComponent::rotation() const {
    return DirectX::XMLoadFloat3(&rotation_);
  }

  void TransformComponent::set_rotation(const float32 x, const float32 y, const float32 z) {
    rotation_ = DirectX::XMFLOAT3(x, y, z);
  }

  DirectX::XMVECTOR TransformComponent::scale() const {
    return DirectX::XMLoadFloat3(&scale_);
  }

  void TransformComponent::set_scale(const float32 x, const float32 y, const float32 z) {
    scale_ = DirectX::XMFLOAT3(x, y, z);
  }

  DirectX::XMMATRIX TransformComponent::local_matrix() {
    calculateLocalMatrix();
    return DirectX::XMLoadFloat4x4(&local_matrix_);
  }

  DirectX::XMMATRIX TransformComponent::global_matrix() const {
    return DirectX::XMLoadFloat4x4(&global_matrix_);
  }

  DirectX::XMMATRIX TransformComponent::local_model_matrix() const {
    return DirectX::XMLoadFloat4x4(&local_model_matrix_);
  }

  DirectX::XMMATRIX TransformComponent::model_matrix() {
    calculateLocalMatrix();
    return DirectX::XMLoadFloat4x4(&model_matrix_);
  }

  DirectX::XMMATRIX TransformComponent::normal_model_matrix() const {
    return DirectX::XMLoadFloat4x4(&normal_model_matrix_);
  }

  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/

  void TransformComponent::calculateLocalMatrix() {
    DirectX::XMMATRIX mRotation, mTranslation, mScalation, mPitchYawRoll;

    DirectX::XMFLOAT3 xf_axis = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);
    DirectX::XMFLOAT3 yf_axis = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
    DirectX::XMFLOAT3 zf_axis = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);

    DirectX::XMVECTOR x_axis = DirectX::XMLoadFloat3(&xf_axis);
    DirectX::XMVECTOR y_axis = DirectX::XMLoadFloat3(&yf_axis);;
    DirectX::XMVECTOR z_axis = DirectX::XMLoadFloat3(&zf_axis);;

    mRotation = DirectX::XMMatrixRotationAxis(x_axis,
                                              DirectX::XMConvertToRadians(rotation_.x));

    mRotation = DirectX::XMMatrixRotationAxis(y_axis,
                                              DirectX::XMConvertToRadians(rotation_.y));

    mRotation = DirectX::XMMatrixRotationAxis(z_axis,
                                              DirectX::XMConvertToRadians(rotation_.z));


    mTranslation = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);;
    mScalation = DirectX::XMMatrixScaling(scale_.x, scale_.y, scale_.z);

    DirectX::XMMATRIX result = (mScalation * mRotation * mTranslation);
    DirectX::XMStoreFloat4x4(&local_matrix_, result);

    DirectX::XMMATRIX transposed = DirectX::XMMatrixTranspose(result);
    DirectX::XMStoreFloat4x4(&model_matrix_, transposed);
  }

}; /* SLX */
