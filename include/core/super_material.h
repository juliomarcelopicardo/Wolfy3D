/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__ 1

#include "Wolfy3D.h"
#include "D3DX11.h"
#include "DirectXMath.h"
#include <vector>

namespace W3D {

enum class MaterialType {
  kMaterialType_Diffuse = 0,
  kMaterialType_OneTexture = 1,
  kMaterialType_Normals = 2,
  kMaterialType_Assesment = 3,
};

struct Matrices {
  DirectX::XMFLOAT4X4 model;
  DirectX::XMFLOAT4X4 view;
  DirectX::XMFLOAT4X4 projection;
};

struct MaterialSettings {
  Matrices matrices;
  MaterialType type;
  uint32 num_textures;
  float32 time;
  // ESTO ES PORQUE LOS CONSTANT BUFFER TIENEN QUE IR EN BLOQUES DE 16Bytes
  float32 padding;
  //float32 padding2;
};

class SuperMaterial {

 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  SuperMaterial();

  /// Default class destructor.
  ~SuperMaterial();

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
  /// Matrices buffer
  ID3D11Buffer* matrix_buffer_;

  MaterialSettings settings_;

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
  
  ///--------------------------------------------------------------------------
  /// @fn   bool createMatrixBuffer();
  ///
  /// @brief  Creates the matrix buffer.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool createMatrixBuffer();


}; /* CoreMaterial */

}; /* W3D */

#endif
