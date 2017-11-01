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
  /// @fn   bool initCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
  ///                     const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Size of the cube.
  /// @param  color Color of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
                const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   bool initTerrain(const char* height_map_filename, const float max_height);
  ///
  /// @brief  Initializes the Geometry. Terrain.
  ///
  /// @param heigh_map_filename File which contains the height map for the terrain.
  /// @param grid_size Size of the whole terrain, Y will be the max height.
  /// @param  color Color RGBA of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initTerrain(const char* height_map_filename, 
                   const DirectX::XMFLOAT3 grid_size = { 10.0f, 2.0f, 10.0f },
                   const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   bool initQuad(const float32 width, const float32 height)
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Width and height of the geometry.
  /// @param  color Color RGBA of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initQuad(const DirectX::XMFLOAT2 size = { 1.0f, 1.0f },
                const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   bool initTriangle(const float32 width, const float32 height)
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Width and height of the geometry.
  /// @param  color Color RGBA of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initTriangle(const DirectX::XMFLOAT2 size = { 1.0f, 1.0f },
                    const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   bool initExtruded(const uint32 num_polygon_vertex, 
  ///                         const DirectX::XMFLOAT3 size,
  ///                         const DirectX::XMFLOAT4 color);
  ///
  /// @brief  Initializes the Geometry.
  /// @param  num_polygon_vertex num vertices of the base polygon.
  /// @param  base_radius Radius of the polygon base.
  /// @param  top_radius Radius of the top polygon.
  /// @param  height Height or extrusion.
  /// @param  color Color RGBA of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initExtruded(const uint32 num_polygon_vertex,
                    const float32 base_radius,
                    const float32 top_radius,
                    const float32 height,
                    const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   bool initFromFile(const char* filename, 
  ///                         const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f })
  ///
  /// @brief  Initializes the Geometry.
  /// @param  filename Filename with the info of the geometry.
  /// @param  color Color of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initFromFile(const char* filename, 
                    const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

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


  /// Topology = the way vertex are rendered (TriangleStrip, TriangleList, Point)
  D3D_PRIMITIVE_TOPOLOGY topology_;


/*******************************************************************************
***                           Private                                        ***
*******************************************************************************/

 private:

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/
   int32 num_vertices_;
   int32 num_indices_;

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/
   
  ///--------------------------------------------------------------------------
  /// @fn   bool createVertexBuffer();
  ///
  /// @brief  Creates the vertex buffer.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
   bool createVertexBuffer();
   ///--------------------------------------------------------------------------
   /// @fn   bool createIndexBuffer();
   ///
   /// @brief  Creates the index buffer.
   /// @return true if successfully initialized, false otherwise.
   ///--------------------------------------------------------------------------
   bool createIndexBuffer();

   ///--------------------------------------------------------------------------
   /// @fn   bool parseTerrainImage();
   ///
   /// @brief  Parses the terrain image and saves its info into a vector.
   /// @param  terrain_size Size of the whole geometry. Y will be the max height.
   /// @param  filename terrain heightmap file.
   /// @param  vertices_output Vector where we will save the vertices.
   /// @param  grid_rows_cols_output Info of the num of rows and cols.
   /// @return true if successfully initialized, false otherwise.
   ///--------------------------------------------------------------------------
   bool parseTerrainImage(const DirectX::XMFLOAT3 terrain_size,
                          const char* filename,
                          std::vector<DirectX::XMFLOAT3>& vertices_output,
                          DirectX::XMINT2& grid_rows_cols_output);


}; /* CoreGeometry */

}; /* SLX */

#endif
