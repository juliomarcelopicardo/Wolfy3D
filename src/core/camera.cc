/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/camera.h"

namespace SLX {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  CoreCamera::CoreCamera() {}

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

}; /* SLX */
