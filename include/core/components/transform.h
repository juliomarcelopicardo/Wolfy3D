/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__ 1

#include "silverlynx.h"
#include "D3DX11.h"
#include <DirectXMath.h>
#include <vector>

namespace SLX {


  struct TransformComponent {

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
    /// @fn   DirectX::XMFLOAT3& position() const;
    ///
    /// @brief  Transform position getter.
    /// @return vec3 containing X,Y,Z Position.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT3 position() const;

    ///--------------------------------------------------------------------------
    /// @fn   void set_position(float x, float y, float z);
    ///
    /// @brief  Transform position setter.
    ///--------------------------------------------------------------------------
    void set_position(float x, float y, float z);

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMFLOAT3& rotation() const;
    ///
    /// @brief  Transform rotation getter.
    /// @return XMFLOAT3 containing X,Y,Z Rotation.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT3 rotation() const;

    ///--------------------------------------------------------------------------
    /// @fn   void set_rotation(float x, float y, float z);
    ///
    /// @brief  Transform rotation setter.
    ///--------------------------------------------------------------------------
    void set_rotation(float x, float y, float z);

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMFLOAT3 scale() const;
    ///
    /// @brief  Transform scale getter.
    /// @return XMFLOAT3 containing X,Y,Z Scale.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT3 scale() const;

    ///--------------------------------------------------------------------------
    /// @fn   void set_scale(float x, float y, float z);
    ///
    /// @brief  Transform scale setter.
    ///--------------------------------------------------------------------------
    void set_scale(float x, float y, float z);

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMFLOAT4X4 local_matrix().
    ///
    /// @brief  Recalculates the local matrix and returns it.
    /// @return XMFLOAT4X4 containing Local Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT4X4 local_matrix();

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMFLOAT4X4 global_matrix() const.
    ///
    /// @brief  Transform GlobalMatrix getter.
    /// @return XMFLOAT4X4 containing Global Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT4X4 global_matrix() const;

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMFLOAT4X4 local_model_matrix() const.
    ///
    /// @brief Transform LocalModelMatrix getter.
    /// @return XMFLOAT4X4 containing LocalModel Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT4X4 local_model_matrix() const;

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMFLOAT4X4 model_matrix() const.
    ///
    /// @brief Transform ModelMatrix getter.
    /// @return XMFLOAT4X4 containing Model Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT4X4 model_matrix() const;

    ///--------------------------------------------------------------------------
    /// @fn   DirectX::XMFLOAT4X4 model_matrix() const.
    ///
    /// @brief Transform NormalModelMatrix getter.
    /// @return XMFLOAT4X4 containing Normal Model Transformation Matrix.
    ///--------------------------------------------------------------------------
    DirectX::XMFLOAT4X4 normal_model_matrix() const;

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
