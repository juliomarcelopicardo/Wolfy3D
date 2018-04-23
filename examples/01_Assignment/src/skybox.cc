/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "skybox.h"
#include "imgui/imgui.h"

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

SkyBox::SkyBox() {}

SkyBox::~SkyBox() {}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void SkyBox::init() {
  initTransforms();
  initTextures();
  initGeometries();
  initMaterials();
  initRenderComponents();
}

void SkyBox::update(const float32& delta_time) {

}



/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void SkyBox::initGeometries() {
  geometry_.initSkyBoxCube({ 1000.0f, 1000.0f, 1000.0f });
}

void SkyBox::initTextures() {
  texture_.initFromFile("../data/textures/skybox.jpg");
}

void SkyBox::initTransforms() {
  root_.transform().set_position(100.0f, 100.0f, 100.0f);
}

void SkyBox::initRenderComponents() {
  root_.addComponent(W3D::kComponentType_Render, &material_, &geometry_);
}

void SkyBox::initMaterials() {
  material_.set_texture(&texture_);
}



}; /* W3D */