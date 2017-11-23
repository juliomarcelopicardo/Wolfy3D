/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/math.h"


namespace W3D {
namespace Math {

#pragma region EXTRACT_EULER_ROTATION_FROM_MODEL_MATRIX

DirectX::XMFLOAT3 GetEulerRotationFromModelMatrix(DirectX::XMFLOAT4X4 m) {
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

#pragma endregion


#pragma region QUATERNION_LERP


DirectX::XMVECTOR QuaternionLerpVector(DirectX::XMFLOAT4 origin, 
                                       DirectX::XMFLOAT4 destiny, 
                                       float32 alpha) {

  DirectX::XMVECTOR orig = DirectX::XMLoadFloat4(&origin);
  DirectX::XMVECTOR dest = DirectX::XMLoadFloat4(&destiny);

  return DirectX::XMQuaternionNormalize(DirectX::XMQuaternionSlerp(orig, dest, alpha));
}

DirectX::XMVECTOR QuaternionLerpVector(DirectX::XMVECTOR origin,
                                       DirectX::XMVECTOR destiny,
                                       float32 alpha) {

  return DirectX::XMQuaternionNormalize(DirectX::XMQuaternionSlerp(origin, destiny, alpha));
}

DirectX::XMFLOAT4 QuaternionLerpFloat4(DirectX::XMFLOAT4 origin,
                                       DirectX::XMFLOAT4 destiny,
                                       float32 alpha) {

  DirectX::XMVECTOR orig = DirectX::XMLoadFloat4(&origin);
  DirectX::XMVECTOR dest = DirectX::XMLoadFloat4(&destiny);
  DirectX::XMFLOAT4 result;
  DirectX::XMStoreFloat4(&result, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionSlerp(orig, dest, alpha)));

  return result;
}

DirectX::XMFLOAT4 QuaternionLerpFloat4(DirectX::XMVECTOR origin,
                                       DirectX::XMVECTOR destiny,
                                       float32 alpha) {

  DirectX::XMFLOAT4 result;
  DirectX::XMStoreFloat4(&result, DirectX::XMQuaternionNormalize(DirectX::XMQuaternionSlerp(origin, destiny, alpha)));

  return result;
}

#pragma endregion

#pragma region LERP

DirectX::XMVECTOR LerpVector(DirectX::XMFLOAT4 origin,
                             DirectX::XMFLOAT4 destiny,
                             float32 alpha) {

  DirectX::XMFLOAT4 result;
  result = { origin.x + (destiny.x - origin.x) * alpha,
             origin.y + (destiny.y - origin.y) * alpha,
             origin.z + (destiny.z - origin.z) * alpha,
             origin.w + (destiny.w - origin.w) * alpha };

  return DirectX::XMLoadFloat4(&result);
}

DirectX::XMVECTOR LerpVector(DirectX::XMVECTOR origin,
                             DirectX::XMVECTOR destiny,
                             float32 alpha) {

  DirectX::XMFLOAT4 result, orig, dest;
  DirectX::XMStoreFloat4(&orig, origin);
  DirectX::XMStoreFloat4(&dest, destiny);

  result = { orig.x + (dest.x - orig.x) * alpha,
             orig.y + (dest.y - orig.y) * alpha,
             orig.z + (dest.z - orig.z) * alpha,
             orig.w + (dest.w - orig.w) * alpha };

  return DirectX::XMLoadFloat4(&result);
}

DirectX::XMFLOAT4 LerpFloat4(DirectX::XMFLOAT4 origin,
                             DirectX::XMFLOAT4 destiny,
                             float32 alpha) {

  DirectX::XMFLOAT4 result;
  result = { origin.x + (destiny.x - origin.x) * alpha,
             origin.y + (destiny.y - origin.y) * alpha,
             origin.z + (destiny.z - origin.z) * alpha,
             origin.w + (destiny.w - origin.w) * alpha };

  return result;
}

DirectX::XMFLOAT4 LerpFloat4(DirectX::XMVECTOR origin,
                             DirectX::XMVECTOR destiny,
                             float32 alpha) {

  DirectX::XMFLOAT4 result, orig, dest;
  DirectX::XMStoreFloat4(&orig, origin);
  DirectX::XMStoreFloat4(&dest, destiny);

  result = { orig.x + (dest.x - orig.x) * alpha,
             orig.y + (dest.y - orig.y) * alpha,
             orig.z + (dest.z - orig.z) * alpha,
             orig.w + (dest.w - orig.w) * alpha };

  return result;
}


#pragma endregion


}; /* Math */
}; /* W3D */
