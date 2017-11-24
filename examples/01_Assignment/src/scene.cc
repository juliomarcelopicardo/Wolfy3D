/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "scene.h"

namespace W3D {

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Scene::Scene() {}

Scene::~Scene() {}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Scene::init() {
  plane_.init();
  terrain_.init();

  root_.transform().set_position(0.0f, 0.0f, 0.0f);
  root_.addChild(&plane_.root_);
  root_.addChild(&terrain_.root_);
}

void Scene::update(const float32 delta_time) {
  plane_.update(delta_time);

}

void Scene::render() {}

/*******************************************************************************
***                            Setters and Getters                           ***
*******************************************************************************/


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/


}; /* W3D */