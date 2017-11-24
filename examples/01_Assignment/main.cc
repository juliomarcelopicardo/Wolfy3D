/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

 
#include <string>
#include "Wolfy3D.h"
#include "scene.h"

namespace W3D {

/// Init application function.
void Init(Scene& scene) {

  Window::Init(1024, 978);


  scene.init();
}

/// Update and Render function.
void Update(Scene& scene, const float32 delta_time) {
  auto& camera = Core::instance().cam_;

  Window::StartFrame();
  
  scene.update(delta_time);

  camera.set_position(scene.plane_.back_camera_.transform().world_position_float3());
  camera.set_target(scene.plane_.plane_.transform().world_position_float3());
  //camera.update();
  camera.render(&scene.root_);

  Window::EndFrame();
}



/* MAIN FUNCTION */

int32 main() {
  
  Scene scene;

  Init(scene);

  // enter the main loop:
  while (Window::IsOpened() && !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {
    
    static uint64 last_time_updated = Time();
    uint64 tick = Time();
    uint64 delta_time = tick - last_time_updated;

    Update(scene, (float32)delta_time);

    last_time_updated = tick;
  }

  Window::Close();

  return 0;
}

}; /* W3D */
