/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/geo.h"
#include "Wolfy3D/geometry.h"
#include "core/core.h"

namespace W3D {


/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Texture2D::Texture2D() {
  id_ = 0;
}

Texture2D::~Texture2D() {}

Texture2D::Texture2D(const Texture2D& copy) {
  id_ = copy.id_;
}

Texture2D& Texture2D::operator=(const Texture2D& copy) {
  id_ = copy.id_;
  return *this;
}

/*******************************************************************************
***                           Setters & Getters                              ***
*******************************************************************************/

ID Texture2D::id() {
  return id_;
}


/*******************************************************************************
***                             Initializers                                 ***
*******************************************************************************/

void Texture2D::initFromFile(const char* filename) {

  auto& factory = Core::instance().texture_factory_;

  /* check if exists in the factory. */
  uint32 length = factory.size();
  std::string name = filename;
  for (uint32 i = 0; i < length; i++) {
    if (name == factory[i]->name_) {
      id_ = i;
      return;
    }
  }

  /* If it doesnt exist in the factory, we will generate a new texture. */
  Texture* texture = new Texture();
  if (texture->initFromFile(filename)) {
    factory.push_back(texture);
    id_ = length;
  }
  else {
    delete texture;
    id_ = Core::instance().error_texture_.id();
  }
  texture = nullptr;
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/



}; /* W3D */
