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

class TransformComponent : Component {

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
    /// @fn   void set_position(float x, float y, float z);
    ///
    /// @brief  Transform position setter.
    ///--------------------------------------------------------------------------
    void set_position(const float32 x, const float32 y, const float32 z);

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMVECTOR rotation() const;
    ///
    /// @brief  Transform rotation getter.
    /// @return XMVECTOR containing X,Y,Z Rotation.
    ///--------------------------------------------------------------------------
    DirectX::XMVECTOR rotation() const;

    ///--------------------------------------------------------------------------
    /// @fn   void set_rotation(float x, float y, float z);
    ///
    /// @brief  Transform rotation setter.
    ///--------------------------------------------------------------------------
    void set_rotation(const float32 x, const float32 y, const float32 z);

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMVECTOR scale() const;
    ///
    /// @brief  Transform scale getter.
    /// @return XMFLOAT3 containing X,Y,Z Scale.
    ///--------------------------------------------------------------------------
    DirectX::XMVECTOR scale() const;

    ///--------------------------------------------------------------------------
    /// @fn   void set_scale(float x, float y, float z);
    ///
    /// @brief  Transform scale setter.
    ///--------------------------------------------------------------------------
    void set_scale(const float32 x, const float32 y, const float32 z);

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMMATRIX local_matrix().
    ///
    /// @brief  Recalculates the local matrix and returns it.
    /// @return XMMATRIX containing Local Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMMATRIX local_matrix();

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMMATRIX global_matrix() const.
    ///
    /// @brief  Transform GlobalMatrix getter.
    /// @return XMMATRIX containing Global Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMMATRIX global_matrix() const;

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMMATRIX local_model_matrix() const.
    ///
    /// @brief Transform LocalModelMatrix getter.
    /// @return XMMATRIX containing LocalModel Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMMATRIX local_model_matrix() const;

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMMATRIX model_matrix() const.
    ///
    /// @brief Transform ModelMatrix getter.
    /// @return XMMATRIX containing Model Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMMATRIX model_matrix();

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMMATRIX model_matrix() const.
    ///
    /// @brief Transform NormalModelMatrix getter.
    /// @return XMFLOAT4X4 containing Normal Model Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMMATRIX normal_model_matrix() const;

    /*******************************************************************************
    ***                           Private                                        ***
    *******************************************************************************/

    /*******************************************************************************
    ***                       Private Attributes                                 ***
    *******************************************************************************/

  private:
    /// Transform Position.
    DirectX::XMFLOAT3 position_;
    /// Transform Rotation.
    DirectX::XMFLOAT3 rotation_;
    /// Transform Scale.
    DirectX::XMFLOAT3 scale_;
    /// Local Transfomation Matrix.
    DirectX::XMFLOAT4X4 local_matrix_;
    /// Global Transformation Matrix.
    DirectX::XMFLOAT4X4 global_matrix_;
    /// Local Model Transformation Matrix.
    DirectX::XMFLOAT4X4 local_model_matrix_;
    /// Global Model Transformation Matrix.
    DirectX::XMFLOAT4X4 model_matrix_;
    /// Normal Model Transformation Matrix.
    DirectX::XMFLOAT4X4 normal_model_matrix_;

    /*******************************************************************************
    ***                              Private methods                             ***
    *******************************************************************************/

    /// Recalculates the local matrix.
    void calculateLocalMatrix();

  };

}; /* SLX */

#endif
