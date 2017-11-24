/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/texture.h"
#include "Wolfy3D/material.h"
#include "core/super_material.h"
#include "core/core.h"
#include <chrono>
#include <thread>

namespace W3D {


/*******************************************************************************
***                      MATERIAL INTERFACE BASE CLASS                       ***
*******************************************************************************/

Material::Material() {}

Material::~Material() {}

/*******************************************************************************
***                      MATERIAL TEXTURED SUB CLASS                       ***
*******************************************************************************/

MaterialTextured::MaterialTextured() : Material() {
  texture_ = nullptr;
}

MaterialTextured::~MaterialTextured() {
  texture_ = nullptr;
}

void MaterialTextured::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.settings_.type = MaterialType::kMaterialType_OneTexture;
  super_mat.settings_.num_textures = 1;
  
  if (texture_ && texture_->texture_handle_) {
    texture_->use();
  }
  else {
    Core::instance().error_texture_.use();
  }
}

void MaterialTextured::set_texture(Texture* texture) {
  if (texture) {
    texture_ = texture;
  }
}

/*******************************************************************************
***                        MATERIAL DIFFUSE SUB CLASS                        ***
*******************************************************************************/

MaterialDiffuse::MaterialDiffuse() : Material() {}

MaterialDiffuse::~MaterialDiffuse() {}

void MaterialDiffuse::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.settings_.type = MaterialType::kMaterialType_Diffuse;
  super_mat.settings_.num_textures = 0;
}

/*******************************************************************************
***                        MATERIAL NORMALS SUB CLASS                        ***
*******************************************************************************/

MaterialNormals::MaterialNormals() : Material() {}

MaterialNormals::~MaterialNormals() {}

void MaterialNormals::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.settings_.type = MaterialType::kMaterialType_Normals;
  super_mat.settings_.num_textures = 0;
}


/*******************************************************************************
***                        MATERIAL TERRAIN SUB CLASS                        ***
*******************************************************************************/

MaterialTerrain::MaterialTerrain() : Material() {}

MaterialTerrain::~MaterialTerrain() {}

void MaterialTerrain::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.settings_.type = MaterialType::kMaterialType_Terrain;
  super_mat.settings_.num_textures = 4;

  texture_materialmap_->use(1, false);
  texture_grass_->use(2);
  texture_moss_->use(3);
  texture_asphalt_->use(4);
}


}; /* W3D */
