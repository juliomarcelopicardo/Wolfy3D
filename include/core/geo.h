/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__ 1

#include "Wolfy3D.h"
#include "DirectXMath.h"
#include "D3D11.h"
#include <vector>

namespace W3D {

class Geo {
  
 public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  Geo();

  /// Default class destructor.
  ~Geo();

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
  /// @fn   bool initSkyBoxCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
  ///                           const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Size of the cube.
  /// @param  color Color of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initSkyBoxCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
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
  ///                         const float32 base_radius,
  ///                         const float32 top_radius,
  ///                         const float32 height,
  ///                         const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
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
  /// @fn   bool initPyramid(const uint32 num_base_vertex,
  ///                        const float32 base_radius,
  ///                        const float32 height,
  ///                        const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
  ///
  /// @brief  Initializes the Geometry.
  /// @param  num_base_vertex num vertices of the base polygon.
  /// @param  base_radius Radius of the polygon base.
  /// @param  height Height or Pyramid.
  /// @param  color Color RGBA of the geometry.
  /// @return true if successfully initialized, false otherwise.
  ///--------------------------------------------------------------------------
  bool initPyramid(const uint32 num_base_vertex,
                   const float32 base_radius,
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

/// Struct to save all the info of the vertices.
  struct VertexData {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
    DirectX::XMFLOAT4 color;
  };

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
***                              Factory Info                                ***
*******************************************************************************/

  /// Geometry types.
  enum Type {
    kType_None = 0,
    kType_Triangle,
    kType_Cube,
    kType_Quad,
    kType_Skybox,
    kType_Terrain,
    kType_Extruded,
    kType_Pyramid,
    kType_ExternalFile,
  };

  struct Vec3 { float32 x, y, z; };
  struct Vec4 { float32 x, y, z, w; };
  struct Vec2 { float32 x, y, z; };

  struct CubeInfo { Vec3 size; };
  struct TriangleInfo { Vec2 size; };
  struct QuadInfo { Vec2 size; };
  struct SkyboxInfo { Vec3 size; };
  struct TerrainInfo { Vec3 size; };
  struct PyramidInfo { uint32 num_polygon_vertex; float32 base_radius; float32 height; };
  struct ExtrudedInfo { uint32 num_polygon_vertex; float32 base_radius; float32 top_radius; float32 height; };
  struct File {};
  
  union FactoryInfo {
    CubeInfo cube;
    TriangleInfo triangle;
    QuadInfo quad;
    SkyboxInfo skybox;
    TerrainInfo terrain;
    PyramidInfo pyramid;
    ExtrudedInfo extruded;
    File file;
  };

  /// Filename path.
  std::string name_;
  /// Geometry type.
  Type type_;
  /// Factory Geometry info. Will be used to now if a geometry already exists in the factory.
  FactoryInfo info_;


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


}; /* Geo */

}; /* W3D */

#endif
