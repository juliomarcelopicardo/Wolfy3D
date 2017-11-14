/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 1

#include "Wolfy3D.h"
#include "D3DX11.h"

namespace W3D {

class CoreTexture {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  CoreTexture();

  /// Default class destructor.
  ~CoreTexture();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   bool load(const char* texture_path);
  ///
  /// @brief  Loads a texture froma a file.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool load(const char* texture_path);

  ///--------------------------------------------------------------------------
  /// @fn   use(const uint32 texture_slot);
  ///
  /// @brief  Use the existing texture.
  /// @param texture_slot sets the slot number of the texture in the shader.
  /// @param pixel_shader_access Texture to be accesed in vertex or pixel shader.
  ///--------------------------------------------------------------------------
  void use(const uint32 texture_slot = 0, const bool pixel_shader_access = true);

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/
  /// Texture handle.
  ID3D11ShaderResourceView* texture_handle_;

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



}; /* CoreTexture */

}; /* W3D */

#endif
