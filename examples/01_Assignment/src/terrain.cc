/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "terrain.h"
#include "imgui/imgui.h"

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Terrain::Terrain() {}

Terrain::~Terrain() {}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Terrain::init() {
  initTransforms();
  initTextures();
  initGeometries();
  initMaterials();
  initRenderComponents();
}

void Terrain::update(const float32& delta_time) {

}



/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Terrain::initGeometries() {
  geo_terrain_.initTerrain("../data/textures/terrain/Heightmap.bmp", { 1000.0f, 70.0f, 1000.0f });
}

void Terrain::initTextures() {
  map_.initFromFile("../data/textures/terrain/materialmap.dds");
  grass_.initFromFile("../data/textures/terrain/grass.dds");
  moss_.initFromFile("../data/textures/terrain/moss.dds");
  asphalt_.initFromFile("../data/textures/terrain/asphalt.dds");
}

void Terrain::initTransforms() {
  root_.transform().set_position(-50.0f, 0.0f, -30.0f);
}

void Terrain::initRenderComponents() {
  root_.addComponent(W3D::kComponentType_Render, &material_, &geo_terrain_);
}

void Terrain::initMaterials() {
  material_.texture_materialmap_ = &map_;
  material_.texture_grass_ = &grass_;
  material_.texture_moss_ = &moss_;
  material_.texture_asphalt_ = &asphalt_;
}



}; /* W3D */