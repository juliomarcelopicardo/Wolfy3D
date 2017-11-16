/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

 
#include <string>
#include "Wolfy3D.h"
#include "core/geo.h"
#include "core/super_material.h"
#include "core/core.h"
#include "core/entity.h"
#include "core/texture.h"
#include "imgui/imgui.h"
#include "core/camera.h"
#include "aeroplane.h"

namespace W3D {

// Aeroplane we are going to control
Aeroplane g_plane;
Entity root;

void AirplaneInput() {
  // Movement on forward is automatic
  g_plane.move_forward();

  if (Input::IsMouseButtonUp(W3D::Input::kMouseButton_Left)) {
    g_plane.shoot();
  }

  ///////////////////////////////////////////////
  // Move Airplane on X axis

  if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_W)) {
    g_plane.move_pitch(60.0f, false);
  }
  else if (!Input::IsKeyboardButtonPressed(Input::kKeyboardButton_S)) {
    g_plane.move_pitch(0.0f, true);
  }

  if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_S)) {
    g_plane.move_pitch(-60.0f, true);
  }
  else if (!Input::IsKeyboardButtonPressed(Input::kKeyboardButton_W)) {
    g_plane.move_pitch(0.0f, false);
  }

  ///////////////////////////////////////////////
  // Move Airplane on YZ axis

  if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_A)) {
    g_plane.move_roll_yaw(20.0f, true, true);
  }
  else if (!Input::IsKeyboardButtonPressed(Input::kKeyboardButton_D)) {
    g_plane.move_roll_yaw(0.0f, false, false);
  }

  if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_D)) {
    g_plane.move_roll_yaw(-20.0f, false, true);
  }
  else if (!Input::IsKeyboardButtonPressed(Input::kKeyboardButton_A)) {
    g_plane.move_roll_yaw(0.0f, true, false);
  }
}

int32 main() {
  
  Window::Init(1024, 978);

  Geo geo, geo2;
  Geo geo_terrain;
  Texture texture[4];
  texture[0].load("./../data/materialmap.dds");
  texture[1].load("./../data/grass.dds");
  texture[2].load("./../data/moss.dds");
  texture[3].load("./../data/asphalt.dds");
  MaterialAssesment mat;
  mat.texture_materialmap_ = &texture[0];
  mat.texture_grass_ = &texture[1];
  mat.texture_moss_ = &texture[2];
  mat.texture_asphalt_ = &texture[3];
  geo_terrain.initTerrain("./../data/Heightmap.bmp", { 1000.0f, 50.0f, 1000.0f });


  Entity terrain;

  g_plane.init(&root);

  terrain.addComponent(ComponentType::Render3D, &mat, &geo_terrain);
  terrain.transform().set_position(-50.0f, -10.0f, -30.0f);
  root.addChild(&terrain);

  root.addChild(&g_plane.root());

  auto& cam = Core::instance().cam_;
  cam.set_position(0.0f, 4.5f, -15.0f);
  cam.setupPerspective(DirectX::XMConvertToRadians(45.0f), 1024.0f / 978.0f, 0.1f, 1000.0f);

  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened() && 
         !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {

	uint64 start = Time();
    DirectX::XMFLOAT3 temp;

    DirectX::XMStoreFloat3(&temp, g_plane.camera_node().transform().world_position_vector());
    cam.set_position(temp.x, temp.y, temp.z);

    DirectX::XMStoreFloat3(&temp, g_plane.root().transform().world_position_vector());
    cam.set_target(temp.x, temp.y, temp.z);

    ///////////////////////////////////////////
    // Input for our Aeroplane
    AirplaneInput();
    
    g_plane.update();


    cam.render(&root);
    g_plane.prop().transform().set_rotation(0.0f, 0.0f, (float32)Time() * 0.01f);
    g_plane.turret().transform().set_rotation(0.0f, (float32)Time() * 0.001f, 0.0f);

	  ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	  ImGui::ShowTestWindow(0);

    Window::EndFrame();
	Sleep(start + 16 - Time());
  }

  Window::Close();

  return 0;
}

}; /* W3D */
