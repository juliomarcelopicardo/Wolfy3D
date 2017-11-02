/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

 
#include <string>
#include "silverlynx.h"
#include "core/geometry.h"
#include "core/material.h"
#include "core/core.h"
#include "core/object.h"
#include "core/texture.h"
#include "imgui/imgui.h"
#include "core/camera.h"
#include "aeroplane.h"

namespace SLX {
int32 main() {
  
  Window::Init(1024, 978);

  CoreGeometry geo, geo2;
  CoreGeometry geo_terrain;
  CoreMaterial mat;
  CoreTexture texture;

  Aeroplane plane;
  plane.init();

  geo_terrain.initTerrain("./../data/Heightmap.bmp", { 100.0f, 10.0f, 100.0f });
  mat.init();
  texture.load("./../data/texture.png");

  Object terrain, root;

  root.addComponent(ComponentType::Transform);
  root.init();

  terrain.addComponent(ComponentType::Transform);
  terrain.addComponent(ComponentType::Render3D);
  terrain.render3D_->setup(&mat, &geo_terrain);
  terrain.render3D_->init();
  terrain.init();
  terrain.transform_->set_position(-50.0f, -10.0f, -30.0f);
  root.addChild(&terrain);

  root.addChild(&plane.plane_root_);

  auto& cam = Core::instance().cam_;
  cam.set_position(0.0f, 4.5f, -15.0f);

  float speed = 0.1f;
  float rotation_speed = 0.0001f;

  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened() && 
         !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {

    DirectX::XMFLOAT3 temp;

    DirectX::XMStoreFloat3(&temp, plane.camera_node_.transform_->worldPosition());
    cam.set_position(temp.x, temp.y, temp.z);

    DirectX::XMStoreFloat3(&temp, plane.plane_root_.transform_->worldPosition());
    cam.set_target(temp.x, temp.y, temp.z);


    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_W)) {
      DirectX::XMFLOAT3 forward;
      DirectX::XMStoreFloat3(&forward, DirectX::XMVectorScale(plane.plane_root_.transform_->forward(), speed));
      plane.plane_root_.transform_->traslate(forward.x, forward.y, forward.z);
    }
    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_S)) {
      DirectX::XMFLOAT3 forward;
      DirectX::XMStoreFloat3(&forward, DirectX::XMVectorScale(plane.plane_root_.transform_->forward(), speed));
      plane.plane_root_.transform_->traslate(-forward.x, -forward.y, -forward.z);
    }
    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_A)) {
      plane.plane_root_.transform_->rotate(0.0f, -rotation_speed, 0.0f);
    }
    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_D)) {
      plane.plane_root_.transform_->rotate(0.0f, rotation_speed, 0.0f);
    }
    

    texture.use();
    cam.render(&root);
    plane.prop_.transform_->set_rotation(0.0f, 0.0f, (float32)Time() * 0.01f);
    plane.turret_.transform_->set_rotation(0.0f, (float32)Time() * 0.001f, 0.0f);

	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::ShowTestWindow(0);

    Window::EndFrame();
  }

  Window::Close();

  return 0;
}

}; /* SLX */
