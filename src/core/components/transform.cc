/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/components/transform.h"
#include "core/core.h"

namespace SLX {

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  TransformComponent::TransformComponent() {
    position_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    rotation_ = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
    scale_ = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
  }

  TransformComponent::~TransformComponent() {
    
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  DirectX::XMFLOAT3 TransformComponent::position() const  {
    return position_;
  }


  void TransformComponent::set_position(float x, float y, float z) {
    position_ = DirectX::XMFLOAT3(x, y, z);
  }

  DirectX::XMFLOAT3 TransformComponent::rotation() const {
    return rotation_;
  }

  void TransformComponent::set_rotation(float x, float y, float z) {
    rotation_ = DirectX::XMFLOAT3(x, y, z);
  }

  DirectX::XMFLOAT3 TransformComponent::scale() const {
    return scale_;
  }

  void TransformComponent::set_scale(float x, float y, float z) {
    scale_ = DirectX::XMFLOAT3(x, y, z);
  }

  DirectX::XMFLOAT4X4 TransformComponent::local_matrix() {
    calculateLocalMatrix();
    return local_matrix_;
  }

  DirectX::XMFLOAT4X4 TransformComponent::global_matrix() const {
    return global_matrix_;
  }

  DirectX::XMFLOAT4X4 TransformComponent::local_model_matrix() const {
    return local_model_matrix_;
  }

  DirectX::XMFLOAT4X4 TransformComponent::model_matrix() const {
    return model_matrix_;
  }

  DirectX::XMFLOAT4X4 TransformComponent::normal_model_matrix() const {
    return normal_model_matrix_;
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

    DirectX::XMStoreFloat4x4(&local_matrix_, (mTranslation * mRotation * mScalation));
    DirectX::XMStoreFloat4x4(&local_model_matrix_, (mTranslation * mRotation * mPitchYawRoll *mScalation));
  }

}; /* SLX */
