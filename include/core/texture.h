/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __TEXTURE_H__
#define __TEXTURE_H__ 1

#include "silverlynx.h"
#include "D3DX11.h"

namespace SLX {

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
  /// @fn   use(const uint32 texture_channel);
  ///
  /// @brief  Use the existing texture.
  /// @param texture_channel sets the channel number of the texture in the shader.
  ///--------------------------------------------------------------------------
  void use(const uint32 texture_channel = 1);

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

}; /* SLX */

#endif