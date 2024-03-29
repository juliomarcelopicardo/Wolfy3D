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

Material::Material() {
  is_light_sensitive_ = 1;
}

Material::~Material() {}

void Material::set_light_sensitivity(const bool is_light_sensitive) {
  if (is_light_sensitive) { is_light_sensitive_ = 1; }
  else { is_light_sensitive_ = 0; }
}

/*******************************************************************************
***                      MATERIAL TEXTURED SUB CLASS                       ***
*******************************************************************************/

MaterialTextured::MaterialTextured() : Material() {
  texture_ = nullptr;
  is_light_sensitive_ = 0;
}

MaterialTextured::~MaterialTextured() {
  texture_ = nullptr;
}

void MaterialTextured::setupSuperMaterial() {
  auto& core = Core::instance();
  auto& super_mat = core.super_material_;

  super_mat.settings_.type = MaterialType::kMaterialType_OneTexture;
  super_mat.settings_.num_textures = 1;
  super_mat.settings_.albedo_color = { 1.0f, 1.0f, 1.0f, 1.0f };
  super_mat.settings_.is_light_sensitive = is_light_sensitive_;
  
  if (texture_) {
    core.texture_factory_[texture_->id()]->use();
  }
  else {
    core.texture_factory_[core.error_texture_.id()]->use();
  }
}

void MaterialTextured::set_texture(Texture2D* texture) {
  if (texture) {
    texture_ = texture;
  }
}

/*******************************************************************************
***                        MATERIAL DIFFUSE SUB CLASS                        ***
*******************************************************************************/

MaterialDiffuse::MaterialDiffuse() : Material() {
  color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

MaterialDiffuse::~MaterialDiffuse() {}

void MaterialDiffuse::setupSuperMaterial() {
  auto& super_mat = Core::instance().super_material_;

  super_mat.settings_.type = MaterialType::kMaterialType_Diffuse;
  super_mat.settings_.num_textures = 0;
  super_mat.settings_.albedo_color = color;
  super_mat.settings_.is_light_sensitive = is_light_sensitive_;
}

void MaterialDiffuse::set_color(const DirectX::XMFLOAT4& rgba) {
  color = rgba;
}

void MaterialDiffuse::set_color(const float32 r, 
                                const float32 g, 
                                const float32 b, 
                                const float32 a) {
  color = { r, g, b, a };
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
  super_mat.settings_.albedo_color = { 1.0f, 1.0f, 1.0f, 1.0f };
  super_mat.settings_.is_light_sensitive = is_light_sensitive_;
}


/*******************************************************************************
***                        MATERIAL TERRAIN SUB CLASS                        ***
*******************************************************************************/

MaterialTerrain::MaterialTerrain() : Material() {}

MaterialTerrain::~MaterialTerrain() {}

void MaterialTerrain::setupSuperMaterial() {
  auto& core = Core::instance();
  auto& super_mat = core.super_material_;

  super_mat.settings_.type = MaterialType::kMaterialType_Terrain;
  super_mat.settings_.num_textures = 4;
  super_mat.settings_.albedo_color = { 1.0f, 1.0f, 1.0f, 1.0f };
  super_mat.settings_.is_light_sensitive = is_light_sensitive_;

  core.texture_factory_[texture_materialmap_->id()]->use(1, false);
  core.texture_factory_[texture_grass_->id()]->use(2);
  core.texture_factory_[texture_moss_->id()]->use(3);
  core.texture_factory_[texture_asphalt_->id()]->use(4);
}




}; /* W3D */
