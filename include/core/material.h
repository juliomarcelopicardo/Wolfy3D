/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__ 1

#include "silverlynx.h"
#include "D3DX11.h"
#include "D3dx9math.h"
#include <vector>

namespace SLX {

class CoreMaterial {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  CoreMaterial();

  /// Default class destructor.
  ~CoreMaterial();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   bool init();
  ///
  /// @brief  Initializes the Material.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool init();

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  /// Vertex Shader
  ID3D11VertexShader* vertex_shader_;
  /// Pixel/Fragment Shader
  ID3D11PixelShader* pixel_shader_;
  /// Input Layout
  ID3D11InputLayout* input_layout_;

/*******************************************************************************
***                           Private                                        ***
*******************************************************************************/

 private:

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/



}; /* CoreMaterial */

}; /* SLX */

#endif
