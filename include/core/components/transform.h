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
#include "core/components/component.h"

namespace SLX {

class TransformComponent : public Component {

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

  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes the component.
  ///--------------------------------------------------------------------------
  void init();

  ///--------------------------------------------------------------------------
  /// @fn   void update();
  ///
  /// @brief  Updates the component.
  ///--------------------------------------------------------------------------
  void update();

  ///--------------------------------------------------------------------------
  /// @fn   void shutdown();
  ///
  /// @brief  Deallocates any memory and setup from this component.
  ///--------------------------------------------------------------------------
  void shutdown();

/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR position() const;
  ///
  /// @brief  Transform position getter.
  /// @return XMVECTOR containing X,Y,Z Position.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR position() const;

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR position_float3() const;
  ///
  /// @brief  Transform position getter.
  /// @return XMFLOAT3 containing X,Y,Z Position.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 position_float3() const;

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR worldPosition();
  ///
  /// @brief  Transform world position getter.
  /// @return XMVECTOR containing X,Y,Z World Position.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR worldPosition();

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

  ///--------------------------------------------------------------------------
  /// @fn   void localTraslate(const DirectX::XMVECTOR traslation);
  ///
  /// @brief  Traslate the object in its local transform.
  ///--------------------------------------------------------------------------
  void localTraslate(const DirectX::XMVECTOR traslation);

  ///--------------------------------------------------------------------------
  /// @fn   void localTraslate(const DirectX::XMFLOAT3 traslation);
  ///
  /// @brief  Traslate the object in its local transform.
  ///--------------------------------------------------------------------------
  void localTraslate(const DirectX::XMFLOAT3 traslation);

  ///--------------------------------------------------------------------------
  /// @fn   void localTraslate(float x, float y, float z);
  ///
  /// @brief  Traslate the object in its local transform.
  ///--------------------------------------------------------------------------
  void localTraslate(const float32 x, const float32 y, const float32 z);

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
  /// @fn   void rotate(float x, float y, float z);
  ///
  /// @brief  Add a rotation to the current one.
  ///--------------------------------------------------------------------------
  void rotate(const float32 x, const float32 y, const float32 z);

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

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR forward();
  ///
  /// @brief forward vector getter.
  /// @return forward vector.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR forward_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR forward_local_vector();
  ///
  /// @brief forward vector of local matrix getter.
  /// @return forward vector of local matrix.
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR forward_local_vector();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 forward();
  ///
  /// @brief forward vector getter.
  /// @return forward vector.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 forward_float3();

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMFLOAT3 forward_local_float3()
  ///
  /// @brief forward vector of the local matrix getter.
  /// @return forward vector of the local matrix.
  ///--------------------------------------------------------------------------
  DirectX::XMFLOAT3 forward_local_float3();

  /// Recalculates the local matrix.
  void calculateLocalModelMatrix();

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

 
  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/


};

}; /* SLX */

#endif
