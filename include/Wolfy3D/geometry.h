/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __WOLFY3D_GEOMETRY_H__
#define __WOLFY3D_GEOMETRY_H__ 1

#include "Wolfy3D/globals.h"
#include <DirectXMath.h>

namespace W3D {

// Geometry class.
class Geometry {

 public:


/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Geometry();
  /// Default class destructor
  ~Geometry();
  /// copy constructor.
  Geometry(const Geometry& copy);
  /// operator of assignment.
  Geometry& operator=(const Geometry& copy);

/*******************************************************************************
***                           Setters & Getters                              ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   ID id();
  ///
  /// @brief  Geometry id getter.
  /// @returns  Geometry id.
  ///--------------------------------------------------------------------------
  ID id();

/*******************************************************************************
***                              Initializers                                ***
*******************************************************************************/


  ///--------------------------------------------------------------------------
  /// @fn   void initCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
  ///                     const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Size of the cube.
  /// @param  color Color of the geometr
  ///--------------------------------------------------------------------------
  void initCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
                const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   void initSkyBoxCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
  ///                           const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Size of the cube.
  /// @param  color Color of the geometry.
  ///--------------------------------------------------------------------------
  void initSkyBoxCube(const DirectX::XMFLOAT3 size = { 1.0f, 1.0f, 1.0f },
                      const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   void initTerrain(const char* height_map_filename, const float max_height);
  ///
  /// @brief  Initializes the Geometry. Terrain.
  ///
  /// @param heigh_map_filename File which contains the height map for the terrain.
  /// @param grid_size Size of the whole terrain, Y will be the max height.
  /// @param  color Color RGBA of the geometry.
  ///--------------------------------------------------------------------------
  void initTerrain(const char* height_map_filename,
                   const DirectX::XMFLOAT3 grid_size = { 10.0f, 2.0f, 10.0f },
                   const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   void initQuad(const float32 width, const float32 height)
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Width and height of the geometry.
  /// @param  color Color RGBA of the geometry.
  ///--------------------------------------------------------------------------
  void initQuad(const DirectX::XMFLOAT2 size = { 1.0f, 1.0f },
                const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   void initTriangle(const float32 width, const float32 height)
  ///
  /// @brief  Initializes the Geometry.
  /// @param  size Width and height of the geometry.
  /// @param  color Color RGBA of the geometry.
  ///--------------------------------------------------------------------------
  void initTriangle(const DirectX::XMFLOAT2 size = { 1.0f, 1.0f },
                    const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   void initExtruded(const uint32 num_polygon_vertex,
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
  ///--------------------------------------------------------------------------
  void initExtruded(const uint32 num_polygon_vertex,
                    const float32 base_radius,
                    const float32 top_radius,
                    const float32 height,
                    const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   void initPyramid(const uint32 num_base_vertex,
  ///                        const float32 base_radius,
  ///                        const float32 height,
  ///                        const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
  ///
  /// @brief  Initializes the Geometry.
  /// @param  num_base_vertex num vertices of the base polygon.
  /// @param  base_radius Radius of the polygon base.
  /// @param  height Height or Pyramid.
  /// @param  color Color RGBA of the geometry.
  ///--------------------------------------------------------------------------
  void initPyramid(const uint32 num_base_vertex,
                   const float32 base_radius,
                   const float32 height,
                   const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  ///--------------------------------------------------------------------------
  /// @fn   void initFromFile(const char* filename, 
  ///                         const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f })
  ///
  /// @brief  Initializes the Geometry.
  /// @param  filename Filename with the info of the geometry.
  /// @param  color Color of the geometry.
  ///--------------------------------------------------------------------------
  void initFromFile(const char* filename, 
                    const DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

  


/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/

private:


  /// Core Geo class id.
  ID id_;


}; /* Geometry */

}; /* W3D */

#endif
