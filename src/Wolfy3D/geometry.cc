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
  id = 0;
}

Geometry::~Geometry() {}

Geometry::Geometry(const Geometry& copy) {
  id = copy.id;
}

Geometry& Geometry::operator=(const Geometry& copy) {
  id = copy.id;
  return *this;
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
        id = i;
        return;
      }
    }
  }

  Geo* geo = new Geo();
  geo->initCube(size);
  factory.push_back(geo);
  id = length;
  geo = nullptr;
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/



}; /* W3D */
