/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/material.h"
#include "core/core.h"
#include "core/window.h"

namespace SLX {

  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

CoreMaterial::CoreMaterial() {
    
}

CoreMaterial::~CoreMaterial() {
  if (vertex_shader_) { vertex_shader_->Release(); }
  if (pixel_shader_) { pixel_shader_->Release(); }
  if (input_layout_) { input_layout_->Release(); }
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

bool CoreMaterial::init() {

  ID3D10Blob* vertex_shader;
  ID3D10Blob* pixel_shader;
  ID3D10Blob* error;

  // Vertex Shader
  HRESULT result = D3DX11CompileFromFile("../data/shader.shader", 
                                          NULL, 
                                          NULL, 
                                          "VShader", 
                                          "vs_4_0", 
                                          0, 
                                          0, 
                                          0, 
                                          &vertex_shader, 
                                          &error, 
                                          0);

  if (result != S_OK) {
    if (error) {
      MessageBox(NULL, (char*)error->GetBufferPointer(), "Vertex Shader ERROR", MB_OK);
    }
    else {
      MessageBox(NULL, "Vertex Shader Path Incorrrect", "Vertex Shader ERROR", MB_OK);
    }
    return false;
  }

  if (error) { error->Release(); } // To clean vertex shader errors.

  // Pixel Shader
  HRESULT pixel_result = D3DX11CompileFromFile("../data/shader.shader", 
                                                NULL, 
                                                NULL, 
                                                "PShader", 
                                                "ps_4_0", 
                                                0, 
                                                0, 
                                                0, 
                                                &pixel_shader,
                                                &error, 
                                                0);

  if (pixel_result != S_OK) {
    if (error) {
      MessageBox(NULL, (char*)error->GetBufferPointer(), "Pixel Shader ERROR", MB_OK);
    }
    else {
      MessageBox(NULL, "Pixel Shader Path Incorrrect", "Pixel Shader ERROR", MB_OK);
    }
    return false;
  }


  // Layout
  D3D11_INPUT_ELEMENT_DESC layout_info[]{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
  };

  // Graphic Card Shader Creation.
  auto* device = Core::instance().d3d_.device();
  device->CreateVertexShader(vertex_shader->GetBufferPointer(), vertex_shader->GetBufferSize(), 0, &vertex_shader_);
  device->CreatePixelShader(pixel_shader->GetBufferPointer(), pixel_shader->GetBufferSize(), 0, &pixel_shader_);
  device->CreateInputLayout(layout_info, 4, vertex_shader->GetBufferPointer(), vertex_shader->GetBufferSize(), &input_layout_);

  if (error) { error->Release(); }

  return true;
}

}; /* SLX */
