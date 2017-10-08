/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__ 1

#include "silverlynx.h"
#include "DirectXMath.h"
#include "D3D11.h"
#include <vector>

namespace SLX {

  class CoreMaterial;

class CoreGeometry {
  
 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  CoreGeometry();

  /// Default class destructor.
  ~CoreGeometry();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   bool init();
  ///
  /// @brief  Initializes the Geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool init();

  ///--------------------------------------------------------------------------
  /// @fn   render();
  ///
  /// @brief  renders the Geometry.
  ///--------------------------------------------------------------------------
  void render(const CoreMaterial* material, int32 test);

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  /// Verices info.
  std::vector<DirectX::XMFLOAT3> vertex_position_;
  /// Vertices buffer.
  ID3D11Buffer* vertex_buffer_;

  /// Vertices indices.
  std::vector<uint32> vertex_index_;
  /// Indices buffer.
  ID3D11Buffer* vertex_index_buffer_;

  /// Matrices buffer
  ID3D11Buffer* matrix_buffer_;

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



}; /* CoreGeometry */

}; /* SLX */

#endif
