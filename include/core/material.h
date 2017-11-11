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
#include "DirectXMath.h"
#include <vector>

namespace SLX {

enum class MaterialType {
  kMaterialType_Diffuse = 0,
  kMaterialType_OneTexture = 1,
  kMaterialType_Normals = 2, 
};

struct Matrices {
  DirectX::XMFLOAT4X4 model;
  DirectX::XMFLOAT4X4 view;
  DirectX::XMFLOAT4X4 projection;
};

struct CustomConstantBuffer {
  Matrices matrices;
  MaterialType type_;
  float32 current_time;
  // ESTO ES PORQUE LOS CONSTANT BUFFER TIENEN QUE IR EN BLOQUES DE 16Bytes
  float32 padding, padding2;
};

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
  /// Matrices buffer
  ID3D11Buffer* matrix_buffer_;

  CustomConstantBuffer custom_constant_buffer_;

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

}; /* SLX */

#endif
