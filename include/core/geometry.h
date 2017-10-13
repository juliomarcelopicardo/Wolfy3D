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
#include "core/object.h"

namespace SLX {

class CoreMaterial; // Forward declaration, DELETE AFTER MAT PARAM IS REMOVED

/// Struct to save all the info of the vertices.
struct VertexData {
  DirectX::XMFLOAT3 position;
  DirectX::XMFLOAT3 normal;
  DirectX::XMFLOAT2 uv;
  DirectX::XMFLOAT4 color;
};

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
  /// @fn   bool init(const char* height_map_filename, const float max_height);
  ///
  /// @brief  Initializes the Geometry. Terrain.
  ///
  /// @param heigh_map_filename File which contains the height map for the terrain.
  /// @param grid_size Size of each cell of the grid.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool init(const char* height_map_filename, const float grid_size);

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  /// Verices info.
  std::vector<VertexData> vertex_data_;
  /// Vertices buffer.
  ID3D11Buffer* vertex_buffer_;

  /// Vertices indices.
  std::vector<uint32> vertex_index_;
  /// Indices buffer.
  ID3D11Buffer* vertex_index_buffer_;

  /// Matrices buffer
  ID3D11Buffer* matrix_buffer_;
  /// Topology = the way vertex are rendered (TriangleStrip, TriangleList, Point)
  D3D_PRIMITIVE_TOPOLOGY topology_;


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
