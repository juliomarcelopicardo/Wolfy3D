/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __WOLFY3D_MATH_H__
#define __WOLFY3D_MATH_H__ 1

#include "Wolfy3D/globals.h"
#include <DirectXMath.h>

namespace W3D {
namespace Math {

#pragma region EULER_QUATERNION_CONVERSIONS

///--------------------------------------------------------------------------
/// @fn   DirectX::XMFLOAT4 ConvertEulerToQuaternionFloat4(DirectX::XMFLOAT3 euler_radians);
///
/// @brief Converts an euler rotation XYZ to quaternion.
/// @param euler_radians Rotation in euler radians.
/// @return Rotation in normalized quaternion.
///--------------------------------------------------------------------------
DirectX::XMFLOAT4 ConvertEulerToQuaternionFloat4(DirectX::XMFLOAT3 euler_radians);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMFLOAT4 ConvertEulerToQuaternionFloat4(DirectX::XMVECTOR euler_radians);
///
/// @brief Converts an euler rotation XYZ to quaternion.
/// @param euler_radians Rotation in euler radians.
/// @return Rotation in normalized quaternion.
///--------------------------------------------------------------------------
DirectX::XMFLOAT4 ConvertEulerToQuaternionFloat4(DirectX::XMVECTOR euler_radians);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMVECTOR ConvertEulerToQuaternionVector(DirectX::XMFLOAT3 euler_radians);
///
/// @brief Converts an euler rotation XYZ to quaternion.
/// @param euler_radians Rotation in euler radians.
/// @return Rotation in normalized quaternion.
///--------------------------------------------------------------------------
DirectX::XMVECTOR ConvertEulerToQuaternionVector(DirectX::XMFLOAT3 euler_radians);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMVECTOR ConvertEulerToQuaternionVector(DirectX::XMVECTOR euler_radians);
///
/// @brief Converts an euler rotation XYZ to quaternion.
/// @param euler_radians Rotation in euler radians.
/// @return Rotation in normalized quaternion.
///--------------------------------------------------------------------------
DirectX::XMVECTOR ConvertEulerToQuaternionVector(DirectX::XMVECTOR euler_radians);

#pragma endregion

#pragma region EXTRACT_EULER_ROTATION_FROM_MODEL_MATRIX

///--------------------------------------------------------------------------
/// @fn   DirectX::XMFLOAT3 GetEulerAnglesFromModelMatrix(DirectX::XMFLOAT4X4 m);
///
/// @brief Extract the euler angles rotation from a model matrix. In radians
/// @param trasposed_matrix Matrix where to extract the rotation (need to be trasposed before).
/// @return Rotation in XYZ axis (in Radians).
///--------------------------------------------------------------------------
DirectX::XMFLOAT3 GetEulerRotationFromModelMatrix(DirectX::XMFLOAT4X4 trasposed_matrix);

#pragma endregion

#pragma region QUATERNION_LERP

///--------------------------------------------------------------------------
/// @fn   DirectX::XMVECTOR QuaternionLerpVector(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);
///
/// @brief Quaternion interpolation (simple lerp).
/// @param origin Origin rotation of the interpolation.
/// @param destiny Destiny rotation of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return Quaternion lerp result.
///--------------------------------------------------------------------------
DirectX::XMVECTOR QuaternionLerpVector(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMVECTOR QuaternionLerpVector(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);
///
/// @brief Quaternion interpolation (simple lerp).
/// @param origin Origin rotation of the interpolation.
/// @param destiny Destiny rotation of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return Quaternion lerp result.
///--------------------------------------------------------------------------
DirectX::XMVECTOR QuaternionLerpVector(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMFLOAT4 QuaternionLerpFloat4(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);
///
/// @brief Quaternion interpolation (simple lerp).
/// @param origin Origin rotation of the interpolation.
/// @param destiny Destiny rotation of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return Quaternion lerp result.
///--------------------------------------------------------------------------
DirectX::XMFLOAT4 QuaternionLerpFloat4(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMFLOAT4 QuaternionLerpFloat4(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);
///
/// @brief Quaternion interpolation (simple lerp).
/// @param origin Origin rotation of the interpolation.
/// @param destiny Destiny rotation of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return Quaternion lerp result.
///--------------------------------------------------------------------------
DirectX::XMFLOAT4 QuaternionLerpFloat4(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);

#pragma endregion

#pragma region LERP

///--------------------------------------------------------------------------
/// @fn   DirectX::XMVECTOR LerpVector(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);
///
/// @brief  interpolation (simple lerp).
/// @param origin Origin of the interpolation.
/// @param destiny Destiny of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return  lerp result.
///--------------------------------------------------------------------------
DirectX::XMVECTOR LerpVector(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMVECTOR LerpVector(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);
///
/// @brief  interpolation (simple lerp).
/// @param origin Origin of the interpolation.
/// @param destiny Destiny of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return  lerp result.
///--------------------------------------------------------------------------
DirectX::XMVECTOR LerpVector(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMFLOAT4 LerpFloat4(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);
///
/// @brief  interpolation (simple lerp).
/// @param origin Origin of the interpolation.
/// @param destiny Destiny of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return  lerp result.
///--------------------------------------------------------------------------
DirectX::XMFLOAT4 LerpFloat4(DirectX::XMFLOAT4 origin, DirectX::XMFLOAT4 destiny, float32 alpha);

///--------------------------------------------------------------------------
/// @fn   DirectX::XMFLOAT4 LerpFloat4(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);
///
/// @brief  interpolation (simple lerp).
/// @param origin Origin of the interpolation.
/// @param destiny Destiny of the interpolation.
/// @param alpha Values between 0.0f and 1.0f where 0 is origin and 1 is destiny.
/// @return  lerp result.
///--------------------------------------------------------------------------
DirectX::XMFLOAT4 LerpFloat4(DirectX::XMVECTOR origin, DirectX::XMVECTOR destiny, float32 alpha);

#pragma endregion

}; /* Math */
}; /* W3D */

#endif
