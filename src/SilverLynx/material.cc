/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/material.h"
#include "core/material.h"
#include "core/core.h"
#include <chrono>
#include <thread>

namespace SLX {


/*******************************************************************************
***                      MATERIAL INTERFACE BASE CLASS                       ***
*******************************************************************************/

Material::Material() {}

Material::~Material() {}

/*******************************************************************************
***                      MATERIAL TEXTURED SUB CLASS                       ***
*******************************************************************************/

MaterialTextured::MaterialTextured() : Material() {
  //texture_ = nullptr;
}

MaterialTextured::~MaterialTextured() {
  //texture_ = nullptr;
}

void MaterialTextured::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.params_.type = MaterialType::kMaterialType_OneTexture;
  super_mat.params_.num_textures = 1;
  super_mat.params_.texture_handle = Core::instance().error_texture_.texture_handle_;
  
  //if (texture_ && texture_->texture_handle_) {
  //  super_mat.params_.texture_handle = texture_->texture_handle_;
  //}
}

/*******************************************************************************
***                        MATERIAL DIFFUSE SUB CLASS                        ***
*******************************************************************************/

MaterialDiffuse::MaterialDiffuse() : Material() {}

MaterialDiffuse::~MaterialDiffuse() {}

void MaterialDiffuse::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.params_.type = MaterialType::kMaterialType_Diffuse;
  super_mat.params_.num_textures = 0;
  super_mat.params_.texture_handle = Core::instance().error_texture_.texture_handle_;
}

/*******************************************************************************
***                        MATERIAL NORMALS SUB CLASS                        ***
*******************************************************************************/

MaterialNormals::MaterialNormals() : Material() {}

MaterialNormals::~MaterialNormals() {}

void MaterialNormals::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.params_.type = MaterialType::kMaterialType_Normals;
  super_mat.params_.num_textures = 0;
  super_mat.params_.texture_handle = Core::instance().error_texture_.texture_handle_;
}


}; /* SLX */