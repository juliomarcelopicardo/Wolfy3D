/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/geo.h"
#include "Wolfy3D/geometry.h"
#include "core/core.h"
#include <list>
#include <chrono>
#include <thread>

namespace W3D {


/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Geometry::Geometry() {
  id_ = 0;
}

Geometry::~Geometry() {}

Geometry::Geometry(const Geometry& copy) {
  id_ = copy.id_;
}

Geometry& Geometry::operator=(const Geometry& copy) {
  id_ = copy.id_;
  return *this;
}

/*******************************************************************************
***                           Setters & Getters                              ***
*******************************************************************************/

///--------------------------------------------------------------------------
/// @fn   GeometryID id();
///
/// @brief  Geometry id getter.
/// @returns  Geometry id.
///--------------------------------------------------------------------------
GeometryID Geometry::id() {
  return id_;
}



void Geometry::initCube(const DirectX::XMFLOAT3 size, const DirectX::XMFLOAT4 color) {

  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  for(uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_Cube) {
      if (size.x == factory[i]->info_.cube.size.x &&
          size.y == factory[i]->info_.cube.size.y &&
          size.z == factory[i]->info_.cube.size.z) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initCube(size, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

void Geometry::initSkyBoxCube(const DirectX::XMFLOAT3 size, const DirectX::XMFLOAT4 color) {
  
  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  for (uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_Skybox) {
      if (size.x == factory[i]->info_.skybox.size.x &&
          size.y == factory[i]->info_.skybox.size.y &&
          size.z == factory[i]->info_.skybox.size.z) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initSkyBoxCube(size, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

void Geometry::initTerrain(const char * height_map_filename, const DirectX::XMFLOAT3 grid_size, const DirectX::XMFLOAT4 color) {

  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  std::string filename = height_map_filename;
  for (uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_Terrain) {
      if (grid_size.x == factory[i]->info_.terrain.size.x &&
          grid_size.y == factory[i]->info_.terrain.size.y &&
          grid_size.z == factory[i]->info_.terrain.size.z &&
          filename == factory[i]->name_) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initTerrain(height_map_filename, grid_size, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

void Geometry::initQuad(const DirectX::XMFLOAT2 size, const DirectX::XMFLOAT4 color) {

  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  for (uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_Quad) {
      if (size.x == factory[i]->info_.quad.size.x &&
         size.y == factory[i]->info_.quad.size.y) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initQuad(size, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

void Geometry::initTriangle(const DirectX::XMFLOAT2 size, const DirectX::XMFLOAT4 color) {

  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  for (uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_Triangle) {
      if (size.x == factory[i]->info_.triangle.size.x &&
          size.y == factory[i]->info_.triangle.size.y) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initTriangle(size, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

void Geometry::initExtruded(const uint32 num_polygon_vertex, 
                            const float32 base_radius, 
                            const float32 top_radius, 
                            const float32 height, 
                            const DirectX::XMFLOAT4 color) {

  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  for (uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_Extruded) {
      if (base_radius == factory[i]->info_.extruded.base_radius &&
          num_polygon_vertex == factory[i]->info_.extruded.num_polygon_vertex &&
          top_radius == factory[i]->info_.extruded.top_radius &&
          height == factory[i]->info_.extruded.height) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initExtruded(num_polygon_vertex, base_radius, top_radius, height, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

void Geometry::initPyramid(const uint32 num_base_vertex, 
                           const float32 base_radius, 
                           const float32 height, 
                           const DirectX::XMFLOAT4 color) {

  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  for (uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_Pyramid) {
      if (base_radius == factory[i]->info_.pyramid.base_radius &&
          num_base_vertex == factory[i]->info_.pyramid.num_polygon_vertex &&
          height == factory[i]->info_.pyramid.height) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initPyramid(num_base_vertex, base_radius, height, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

void Geometry::initFromFile(const char* filename, const DirectX::XMFLOAT4 color) {

  auto& factory = Core::instance().geometry_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  std::string name = filename;
  for (uint32 i = 0; i < length; i++) {
    if (factory[i]->type_ == Geo::kType_ExternalFile) {
      if (name == factory[i]->name_) {
        id_ = i;
        return;
      }
    }
  }

  /* If it doesnt exist in the factory, we will generate a new geometry. */
  Geo* geo = new Geo();
  geo->initFromFile(filename, color);
  factory.push_back(geo);
  id_ = length;
  geo = nullptr;
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/



}; /* W3D */
