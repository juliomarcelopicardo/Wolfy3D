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

  void init();
  void render();
  DirectX::XMMATRIX ortho_matrix();

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/
  Geometry geometry_;
  MaterialTextured material_;
  /// Name, file path.
  std::string name_;

/*******************************************************************************
***                           Private                                        ***
*******************************************************************************/

 private:

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  /// Orthographic matrix.
  DirectX::XMFLOAT4X4 ortho_matrix_;

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/



}; /* SuperSprite */

}; /* W3D */

#endif
