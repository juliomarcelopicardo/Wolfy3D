/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/globals.h"
#include "core/texture.h"
#include "core/directx.h"
#include "core/core.h"
#include "D3D11.h"

namespace W3D {

  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Texture::Texture() {
  texture_handle_ = nullptr;
  sampler_state_ = nullptr;
  name_ = "";
}

Texture::~Texture() {
  if (texture_handle_) {
    texture_handle_->Release();
    texture_handle_ = nullptr;
  }
  if (sampler_state_) {
    sampler_state_->Release();
    sampler_state_ = nullptr;
  }
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

bool Texture::initFromFile(const char* texture_path) {

  HRESULT result;

  result = D3DX11CreateShaderResourceViewFromFile(Core::instance().d3d_.device(), 
                                                  texture_path, 
                                                  NULL, 
                                                  NULL, 
                                                  &texture_handle_, 
                                                  NULL);

  auto& core = Core::instance();
  if (FAILED(result)) {
    MessageBox(NULL, "Error loading texture", "ERROR", MB_OK);
    uint32 id = core.error_texture_.id();
    return false;
  }

  D3D11_SAMPLER_DESC sampler_description;
  sampler_description.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampler_description.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampler_description.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampler_description.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampler_description.MipLODBias = 0.0f;
  sampler_description.MaxAnisotropy = 1;
  sampler_description.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
  sampler_description.BorderColor[0] = 0;
  sampler_description.BorderColor[1] = 0;
  sampler_description.BorderColor[2] = 0;
  sampler_description.BorderColor[3] = 0;
  sampler_description.MinLOD = 0;
  sampler_description.MaxLOD = D3D11_FLOAT32_MAX;

  // Create the texture sampler state.
  result = core.d3d_.device()->CreateSamplerState(&sampler_description, &sampler_state_);
  
  if (FAILED(result)) {
    MessageBox(NULL, "Error sampling texture", "ERROR", MB_OK);
    uint32 id = core.error_texture_.id();
    return false;
  }

  name_ = texture_path;
  return true;
}

void Texture::use(const uint32 texture_slot, const bool pixel_shader_access) {
  if (texture_handle_) {
    auto* dev_context = Core::instance().d3d_.deviceContext();
    if (pixel_shader_access) {
      dev_context->PSSetShaderResources(texture_slot, 1, &texture_handle_);
      dev_context->PSSetSamplers(0, 1, &sampler_state_);
    }
    else {
      dev_context->VSSetShaderResources(texture_slot, 1, &texture_handle_);
      dev_context->VSSetSamplers(0, 1, &sampler_state_);
    }
  }
  else {
    MessageBox(NULL, "Error using texture", "ERROR", MB_OK);
  }

}



}; /* W3D */
