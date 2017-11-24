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

Scene::Scene() {
  camera_mode_ = kCameraMode_Plane3rdPerson;
}

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
  root_.addChild(&landing_track_);
  landing_track_.addChild(&landing_track_camera_);
  for (uint32 i = 0; i < plane_.num_bullets_; ++i) {
    plane_.bullet_[i].init();
    root_.addChild(&plane_.bullet_[i].root_);
  }

  landing_track_.transform().set_position(319.0f, 2.5f, 500.0f);
  landing_track_camera_.transform().set_position(0.0f, 7.0f, 15.0f);
}

void Scene::update(const float32 delta_time) {
  plane_.update(delta_time);
  landing_track_.transform().rotate(0.0f, delta_time * 0.0005f, 0.0f);
  updateCameraMode();
}

void Scene::render() {}

void Scene::updateCameraMode() {
  auto& camera = Core::instance().cam_;

  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Tab)) {
    switchCameraMode();
  }

  switch (camera_mode_) {
    case kCameraMode_Plane3rdPerson: {
      camera.set_position(plane_.back_camera_.transform().world_position_float3());
      camera.set_target(plane_.plane_.transform().world_position_float3());
    } break;
    case kCameraMode_LandingTrack: {
      camera.set_position(landing_track_camera_.transform().world_position_float3());
      camera.set_target(landing_track_.transform().world_position_float3());
    } break;
    case kCameraMode_PlaneGun: {
      camera.set_position(plane_.gun_camera_.transform().world_position_float3());
      camera.set_target(plane_.turret_.transform().world_position_float3());
    } break;
  };

}

void Scene::switchCameraMode() {
  auto& camera = Core::instance().cam_;
  switch (camera_mode_) {
    case kCameraMode_Plane3rdPerson: {
      camera_mode_ = kCameraMode_LandingTrack;
    } break;
    case kCameraMode_LandingTrack: {
      camera_mode_ = kCameraMode_PlaneGun;
    } break;
    case kCameraMode_PlaneGun: {
      camera_mode_ = kCameraMode_Plane3rdPerson;
    } break;
  };
}

/*******************************************************************************
***                            Setters and Getters                           ***
*******************************************************************************/


/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/


}; /* W3D */