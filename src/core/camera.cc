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

namespace SLX {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  CoreCamera::CoreCamera() {
    position_ = { 0.0f, 5.0f, -10.0f };
    target_ = { 0.0f, 0.0f, 0.0f };
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

  DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position_),
                                                      DirectX::XMLoadFloat3(&target_),
                                                      up);

  DirectX::XMStoreFloat4x4(&view_matrix_, view);
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

DirectX::XMMATRIX CoreCamera::projectionMatrix() {
  return DirectX::XMLoadFloat4x4(&projection_matrix_);
}

DirectX::XMMATRIX CoreCamera::viewMatrix() {
  return DirectX::XMLoadFloat4x4(&view_matrix_);
}

}; /* SLX */
