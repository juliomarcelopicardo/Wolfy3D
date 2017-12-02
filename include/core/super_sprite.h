/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __SUPER_SPRITE_H__
#define __SUPER_SPRITE_H__ 1

#include "Wolfy3D.h"
#include "D3DX11.h"
#include <string>

namespace W3D {

class SuperSprite {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  SuperSprite();

  /// Default class destructor.
  ~SuperSprite();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes the SuperSprite.
  ///--------------------------------------------------------------------------
  void init();

  ///--------------------------------------------------------------------------
  /// @fn   void render();
  ///
  /// @brief  Renders the SuperSprite.
  ///--------------------------------------------------------------------------
  void render();

  ///--------------------------------------------------------------------------
  /// @fn   void calculateOrthographicMatrix();
  ///
  /// @brief  Calculates the orthographic matrix based on the window size.
  ///--------------------------------------------------------------------------
  void calculateOrthographicMatrix();

/*******************************************************************************
***                           Setters & Getters                              ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMMATRIX ortho_matrix();
  ///
  /// @brief  Orthographic matrix getter.
  /// @returns the orthographic matrix used for rendering the sprites.
  ///--------------------------------------------------------------------------
  DirectX::XMMATRIX ortho_matrix();
  
 private:

/*******************************************************************************
***                            Private Attributes                            ***
*******************************************************************************/

  /// Material used to render the sprites.
  MaterialTextured material_;
  /// Orthographic matrix.
  DirectX::XMFLOAT4X4 ortho_matrix_;

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/



}; /* SuperSprite */

}; /* W3D */

#endif
