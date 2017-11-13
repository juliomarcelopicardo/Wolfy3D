/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/texture.h"
#include "core/d3d.h"
#include "core/core.h"
#include "D3D11.h"

namespace SLX {

  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

CoreTexture::CoreTexture() {
  texture_handle_ = nullptr;
}

CoreTexture::~CoreTexture() {
  if (texture_handle_) {
    texture_handle_->Release();
    texture_handle_ = nullptr;
  }
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

bool CoreTexture::load(const char* texture_path) {

  HRESULT result;

  result = D3DX11CreateShaderResourceViewFromFile(Core::instance().d3d_.device(), 
                                                  texture_path, 
                                                  NULL, 
                                                  NULL, 
                                                  &texture_handle_, 
                                                  NULL);

  if (FAILED(result)) {
    MessageBox(NULL, "Error loading texture", "ERROR", MB_OK);
    return false;
  }

  return true;
}

void CoreTexture::use(const uint32 texture_slot) {
  if (texture_handle_) {
    Core::instance().d3d_.deviceContext()->PSSetShaderResources(texture_slot, 1, &texture_handle_);
  }
  else {
    MessageBox(NULL, "Error using texture", "ERROR", MB_OK);
  }

}



}; /* SLX */
