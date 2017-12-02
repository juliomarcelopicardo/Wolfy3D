/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __WOLFY3D_SPRITE_H__
#define __WOLFY3D_SPRITE_H__ 1

#include "Wolfy3D/globals.h"
#include "Wolfy3D/texture2D.h"
#include <DirectXMath.h>

namespace W3D {

/// Sprite class.
class Sprite {

public:

/// It only affects to the position.
enum PivotPoint {
  kPivotPoint_Center = 0,
  kPivotPoint_UpLeft,
  kPivotPoint_Up,
  kPivotPoint_UpRight,
  kPivotPoint_Right,
  kPivotPoint_Downight,
  kPivotPoint_Down,
  kPivotPoint_DownLeft,
  kPivotPoint_Left,
};

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/
  /// Default class constructor.
  Sprite();
  /// Default class destructor.
  ~Sprite();
  /// Assignment operator.
  Sprite& operator=(const Sprite& other);
  /// Default copy constructor.
  Sprite(const Sprite& other);


/*******************************************************************************
***                              Public Methods                              ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   render();
  ///
  /// @brief Renderizes the base sprite.
  ///--------------------------------------------------------------------------
  void render();

/*******************************************************************************
***                              Public Setters                              ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   set_texture2D(Texture* texture);
  ///
  /// @brief texture setter.
  /// @param texture texture to set.
  ///--------------------------------------------------------------------------
  void set_texture(Texture2D* texture);

  ///--------------------------------------------------------------------------
  /// @fn   set_texture(const DirectX::XMFLOAT2 texture);
  ///
  /// @brief Position setter.
  /// @param position Position to set.
  ///--------------------------------------------------------------------------
  void set_position(const DirectX::XMFLOAT2 position);
  ///--------------------------------------------------------------------------
  /// @fn   set_rotation(const float rotation);
  ///
  /// @brief Rotation setter.
  /// @param rotation Radians to set.
  ///--------------------------------------------------------------------------
  void set_rotation(const float rotation);
  ///--------------------------------------------------------------------------
  /// @fn   set_size(const DirectX::XMFLOAT2 size);
  ///
  /// @brief Sprite Size setter.
  /// @param size Size to set.
  ///--------------------------------------------------------------------------
  void set_size(const DirectX::XMFLOAT2 size);
  ///--------------------------------------------------------------------------
  /// @fn   set_pivot(const PivotPoint pivot);
  ///
  /// @brief Sprite pivot setter.
  /// @param pivot Pivot to set.
  ///--------------------------------------------------------------------------
  void set_pivot(const PivotPoint pivot);


/*******************************************************************************
***                              Public Getters                              ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   Texture2D* texture();
  ///
  /// @brief Sprite texture getter.
  /// @return texture of the sprite.
  ///--------------------------------------------------------------------------
  Texture2D* texture();
  ///--------------------------------------------------------------------------
  /// @fn   const DirectX::XMFLOAT2 size();
  ///
  /// @brief Sprite size getter.
  /// @return size of the sprite.
  ///--------------------------------------------------------------------------
  const DirectX::XMFLOAT2 size();
  ///--------------------------------------------------------------------------
  /// @fn   const float color();
  ///
  /// @brief Sprite rotation getter.
  /// @return rotation of the sprite in radians.
  ///--------------------------------------------------------------------------
  const float rotation();
  ///--------------------------------------------------------------------------
  /// @fn   const DirectX::XMFLOAT2 position();
  ///
  /// @brief Text position getter.
  /// @return position of the sprite in the window.
  ///--------------------------------------------------------------------------
  const DirectX::XMFLOAT2 position();
  ///--------------------------------------------------------------------------
  /// @fn   const PivotPoint pivot();
  ///
  /// @brief Pivot id getter.
  /// @return Pivot or origin point of the sprite.
  ///--------------------------------------------------------------------------
  const PivotPoint pivot();

/*******************************************************************************
***                            Private Attributes                            ***
*******************************************************************************/

private:

  /// Position.
  DirectX::XMFLOAT2 position_;
  /// Size.
  DirectX::XMFLOAT2 size_;
  /// Rotation in radians.
  float rotation_;
  /// Texture to render.
  Texture2D* texture_;
  /// Pivot or origin of the position.
  PivotPoint pivot_;




}; /* Sprite */

}; /* W3D */

#endif
