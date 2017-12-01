/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

 
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>
#include <sstream>
#include "Wolfy3D.h"
#include "core/geo.h"
#include "core/super_material.h"
#include "core/core.h"
#include "core/entity.h"
#include "core/texture.h"
#include "imgui/imgui.h"
#include "core/cam.h"
#include "tinyxml2\tinyxml2.h"


#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

namespace W3D {
  
void ImGuiGenerateNodeStats(Entity* entity) {

  DirectX::XMFLOAT3 temp;

  ImGui::PushID(entity);

  // Position
  temp = entity->transform().position_float3();
  ImGui::DragFloat3(" Position", &temp.x);

  // rotation
  temp = entity->transform().euler_rotation_float3();
  temp.x = DirectX::XMConvertToDegrees(temp.x);
  temp.y = DirectX::XMConvertToDegrees(temp.y);
  temp.z = DirectX::XMConvertToDegrees(temp.z);
  ImGui::DragFloat3(" Rotation", &temp.x, 0.05f);
  //entity->transform().set_rotation(temp);


  ImGui::PopID();
}

/// @brief ImGui scene's root children stats.
void ImGuiGenerateRootTreeStats(Entity* root_entity) {

  if (ImGui::TreeNode(root_entity->name_.c_str())) {
    ImGuiGenerateNodeStats(root_entity);
    uint32 size = root_entity->children_.size();
    for (uint32 i = 0; i < size; i++) {
      ImGuiGenerateRootTreeStats(root_entity->children_[i]);
    }
    ImGui::TreePop();
  }

}




int32 main() {
  
  Window::Init(1200, 978);

  MaterialDiffuse mat;

  Entity cube1, cube2, cube3;
  cube2.transform().set_position(2.0f, 0.0f, 0.0f);
  cube3.transform().set_position(-2.0f, 1.0f, 0.0f);

  Geometry geo1, geo2, geo3;
  geo1.initCube();
  geo2.initCube({ 2.0f, 2.0, 2.0f });
  geo3.initCube();

  cube1.addComponent(kComponentType_Render, &mat, &geo1);
  cube2.addComponent(kComponentType_Render, &mat, &geo2);
  cube3.addComponent(kComponentType_Render, &mat, &geo3);

  cube1.addChild(&cube2);

  cube1.addChild(&cube3);
  while (Window::StartFrame(1.0f) && Window::IsOpened() &&
        !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {
    static float32 last_time_updated = (float32)std::timeGetTime();
    float32 tick = Time();
    float32 delta = tick - last_time_updated;


    if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_SpaceBar)) {
     
    }

   
    Core::instance().cam_.render(&cube1);

    float32 a= delta * 0.001f;
    ImGui::Text("%.4f", a);
    ImGui::Text("Wolfy3D speed: %.3f ms/frame (%.1f FPS)",
      1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    Window::EndFrame();

    last_time_updated = tick;
  }

  Window::Close();

  return 0;
}


}; /* W3D */
