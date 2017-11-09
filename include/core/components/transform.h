/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__ 1

#include <DirectXMath.h>
#include "SilverLynx/globals.h"

namespace SLX {

class TransformComponent {

public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  TransformComponent();

  /// Default class destructor.
  ~TransformComponent();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/
  
///--------------------------------------------------------------------------
  /// @fn   void set_owner(class Object* owner);
  ///
  /// @brief  Owner of this component setter
  /// @param  Object owner pointer of this component to be set.
  ///--------------------------------------------------------------------------
  void set_owner(class Object* owner);

#pragma region POSITION

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR position_vector() const;
  ///
  /// @brief  Transform position getter.
  /// @return XMVECTOR containing X,Y,Z Position.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR position_vector() const;

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR position_float3() const;
  ///
  /// @brief  Transform position getter.
  /// @return XMFLOAT3 containing X,Y,Z Position.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 position_float3() const;

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR world_position_vector();
  ///
  /// @brief  Transform world position getter.
  /// @return XMVECTOR containing X,Y,Z World Position.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR world_position_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR world_position_float3();
  ///
  /// @brief  Transform world position getter.
  /// @return XMVECTOR containing X,Y,Z World Position.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 world_position_float3();

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMVECTOR position);
  ///
  /// @brief  Transform position setter.
  ///--------------------------------------------------------------------------
  void set_position(const DirectX::XMVECTOR position);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(const DirectX::XMFLOAT3 position);
  ///
  /// @brief  Transform position setter.
  ///--------------------------------------------------------------------------
  void set_position(const DirectX::XMFLOAT3 position);

  ///--------------------------------------------------------------------------
  /// @fn   void set_position(float x, float y, float z);
  ///
  /// @brief  Transform position setter.
  ///--------------------------------------------------------------------------
  void set_position(const float32 x, const float32 y, const float32 z);

  ///--------------------------------------------------------------------------
  /// @fn   void set_world_position(const DirectX::XMVECTOR position);
  ///
  /// @brief  Transform world position setter.
  ///--------------------------------------------------------------------------
  void set_world_position(const DirectX::XMVECTOR position);

  ///--------------------------------------------------------------------------
  /// @fn   void set_world_position(const DirectX::XMFLOAT3 position);
  ///
  /// @brief  Transform world position setter.
  ///--------------------------------------------------------------------------
  void set_world_position(const DirectX::XMFLOAT3 position);

  ///--------------------------------------------------------------------------
  /// @fn   void set_world_position(float x, float y, float z);
  ///
  /// @brief  Transform world position setter.
  ///--------------------------------------------------------------------------
  void set_world_position(const float32 x, const float32 y, const float32 z);

#pragma endregion

#pragma region ROTATION

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR rotation() const;
  ///
  /// @brief  Transform rotation getter.
  /// @return XMVECTOR containing X,Y,Z Rotation.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR rotation_vector() const;

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 rotation() const;
  ///
  /// @brief  Transform rotation getter.
  /// @return XMFLOAT3 containing X,Y,Z Rotation.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 rotation_float3() const;

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR world_rotation();
  ///
  /// @brief  Transform world rotation getter.
  /// @return XMVECTOR containing X,Y,Z world Rotation.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR world_rotation_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 world_rotation();
  ///
  /// @brief  Transform world rotation getter.
  /// @return XMFLOAT3 containing X,Y,Z world Rotation.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 world_rotation_float3();

  ///--------------------------------------------------------------------------
  /// @fn   void set_rotation(float x, float y, float z);
  ///
  /// @brief  Transform rotation setter.
  ///--------------------------------------------------------------------------
  void set_rotation(const float32 x, const float32 y, const float32 z);

  ///--------------------------------------------------------------------------
  /// @fn   void set_rotation(const DirectX::XMFLOAT3 rotation);
  ///
  /// @brief  Transform rotation setter.
  ///--------------------------------------------------------------------------
  void set_rotation(const DirectX::XMFLOAT3 rotation);

  ///--------------------------------------------------------------------------
  /// @fn   void set_rotation(const DirectX::XMVECTOR rotation);
  ///
  /// @brief  Transform rotation setter.
  ///--------------------------------------------------------------------------
  void set_rotation(const DirectX::XMVECTOR rotation);

  ///--------------------------------------------------------------------------
  /// @fn   void set_world_rotation(float x, float y, float z);
  ///
  /// @brief  Transform rotation setter.
  ///--------------------------------------------------------------------------
  void set_world_rotation(const float32 x, const float32 y, const float32 z);

  ///--------------------------------------------------------------------------
  /// @fn   void set_world_rotation(const DirectX::XMFLOAT3 rotation);
  ///
  /// @brief  Transform rotation setter.
  ///--------------------------------------------------------------------------
  void set_world_rotation(const DirectX::XMFLOAT3 rotation);

  ///--------------------------------------------------------------------------
  /// @fn   void set_world_rotation(const DirectX::XMVECTOR rotation);
  ///
  /// @brief  Transform rotation setter.
  ///--------------------------------------------------------------------------
  void set_world_rotation(const DirectX::XMVECTOR rotation);

#pragma endregion

#pragma region SCALE

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR scale() const;
  ///
  /// @brief  Transform scale getter.
  /// @return XMFLOAT3 containing X,Y,Z Scale.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR scale_vector() const;

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 scale() const;
  ///
  /// @brief  Transform scale getter.
  /// @return XMFLOAT3 containing X,Y,Z Scale.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 scale_float3() const;

  ///--------------------------------------------------------------------------
  /// @fn   void set_scale(float x, float y, float z);
  ///
  /// @brief  Transform scale setter.
  ///--------------------------------------------------------------------------
  void set_scale(const float32 x, const float32 y, const float32 z);

  ///--------------------------------------------------------------------------
  /// @fn   void set_scale(DirectX::XMVECTOR scale);
  ///
  /// @brief  Transform scale setter.
  ///--------------------------------------------------------------------------
  void set_scale(const DirectX::XMVECTOR scale);

  ///--------------------------------------------------------------------------
  /// @fn   void set_scale(DirectX::XMFLOAT3 scale);
  ///
  /// @brief  Transform scale setter.
  ///--------------------------------------------------------------------------
  void set_scale(const DirectX::XMFLOAT3 scale);

  ///--------------------------------------------------------------------------
  /// @fn   void set_scale(float x, float y, float z);
  ///
  /// @brief  Transform scale setter.
  ///--------------------------------------------------------------------------
  void set_scale(const float32 uniform_scale);

#pragma endregion


#pragma region TRANSLATE

  ///--------------------------------------------------------------------------
  /// @fn   void localTraslate(const DirectX::XMVECTOR traslation);
  ///
  /// @brief  Traslate the object in its local transform.
  ///--------------------------------------------------------------------------
  void traslate(const DirectX::XMVECTOR traslation);

  ///--------------------------------------------------------------------------
  /// @fn   void localTraslate(const DirectX::XMFLOAT3 traslation);
  ///
  /// @brief  Traslate the object in its local transform.
  ///--------------------------------------------------------------------------
  void traslate(const DirectX::XMFLOAT3 traslation);

  ///--------------------------------------------------------------------------
  /// @fn   void localTraslate(float x, float y, float z);
  ///
  /// @brief  Traslate the object in its local transform.
  ///--------------------------------------------------------------------------
  void traslate(const float32 x, const float32 y, const float32 z);

  ///--------------------------------------------------------------------------
  /// @fn   void traslate(const DirectX::XMVECTOR traslation);
  ///
  /// @brief  Traslate the object in its world transform.
  ///--------------------------------------------------------------------------
  void worldTraslate(const DirectX::XMVECTOR traslation);

  ///--------------------------------------------------------------------------
  /// @fn   void traslate(const DirectX::XMFLOAT3 traslation);
  ///
  /// @brief  Traslate the object in its world transform.
  ///--------------------------------------------------------------------------
  void worldTraslate(const DirectX::XMFLOAT3 traslation);

  ///--------------------------------------------------------------------------
  /// @fn   void traslate(float x, float y, float z);
  ///
  /// @brief  Traslate the object in its world transform.
  ///--------------------------------------------------------------------------
  void worldTraslate(const float32 x, const float32 y, const float32 z);

#pragma endregion

#pragma region ROTATE

  ///--------------------------------------------------------------------------
  /// @fn   void rotate(float x, float y, float z);
  ///
  /// @brief  Add a rotation to the current one.
  ///--------------------------------------------------------------------------
  void rotate(const float32 x, const float32 y, const float32 z);

  ///--------------------------------------------------------------------------
  /// @fn   void rotate(const DirectX::XMVECTOR rotation);
  ///
  /// @brief  Add a rotation to the current one.
  ///--------------------------------------------------------------------------
  void rotate(const DirectX::XMVECTOR rotation);

  ///--------------------------------------------------------------------------
  /// @fn   void rotate(const DirectX::XMFLOAT3 rotation);
  ///
  /// @brief  Add a rotation to the current one.
  ///--------------------------------------------------------------------------
  void rotate(const DirectX::XMFLOAT3 rotation);

  ///--------------------------------------------------------------------------
  /// @fn   void worldRotate(float x, float y, float z);
  ///
  /// @brief  Add a global rotation to the current one.
  ///--------------------------------------------------------------------------
  void worldRotate(const float32 x, const float32 y, const float32 z);

  ///--------------------------------------------------------------------------
  /// @fn   void worldRotate(const DirectX::XMVECTOR rotation);
  ///
  /// @brief  Add a global rotation to the current one.
  ///--------------------------------------------------------------------------
  void worldRotate(const DirectX::XMVECTOR rotation);

  ///--------------------------------------------------------------------------
  /// @fn   void worldRotate(const DirectX::XMFLOAT3 rotation);
  ///
  /// @brief  Add a global rotation to the current one.
  ///--------------------------------------------------------------------------
  void worldRotate(const DirectX::XMFLOAT3 rotation);

#pragma endregion

  
#pragma region FORWARD
  
  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR world_forward_vector();
  ///
  /// @brief World object forward vector getter.
  /// @return World forward vector.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR world_forward_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR forward_vector();
  ///
  /// @brief forward vector of local matrix getter.
  /// @return forward vector of local matrix.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR forward_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 world_forward_float3();
  ///
  /// @brief World forward vector getter.
  /// @return World forward vector.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 world_forward_float3();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 forward_float3()
  ///
  /// @brief forward vector of the local matrix getter.
  /// @return forward vector of the local matrix.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 forward_float3();

#pragma endregion
  
#pragma region MATRICES
  
  /// Recalculates the local matrix.
  void calculateLocalModelMatrix();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMMATRIX local_model_matrix() const.
  ///
  /// @brief Transform LocalModelMatrix getter. (TRANSPOSED)
  /// @return XMMATRIX containing LocalModel Transformation Matrix.
  ///--------------------------------------------------------------------------
  DirectX::XMMATRIX local_model_matrix();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMMATRIX global_model_matrix() const.
  ///
  /// @brief Transform GlobalModelMatrix getter. (TRANSPOSED)
  /// @return XMMATRIX containing GlobalModel Transformation Matrix.
  ///--------------------------------------------------------------------------
  DirectX::XMMATRIX global_model_matrix();

#pragma endregion


  /// Local Model Transformation Matrix.
  DirectX::XMFLOAT4X4 local_model_matrix_;
  /// Parent Model Transformation Matrix.
  DirectX::XMFLOAT4X4 parent_model_matrix_;
  

private:

  /*******************************************************************************
  ***                       Private Attributes                                 ***
  *******************************************************************************/
  /// Transform Position.
  DirectX::XMFLOAT3 position_;
  /// Transform Rotation.
  DirectX::XMFLOAT3 rotation_;
  /// Transform Scale.
  DirectX::XMFLOAT3 scale_;
  /// Object who possess the component.
  class Object* owner_;
 
  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/


};

}; /* SLX */

#endif
