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

namespace SLX {
int32 main() {
  
  Window::Init(1024, 978);

  CoreGeometry geo, geo2;
  CoreGeometry geo_plane, geo_prop, geo_turret, geo_gun, geo_terrain;
  CoreMaterial mat;
  CoreTexture texture;

  //geo.initQuad();
  //geo.initCube();
  //geo.initPyramid(50 ,1, 3);
  //geo.initFromFile("./../data/geometries/plane/plane.x");
  //geo.initExtruded(100, 2.0f, 1.0f, 4.0f);
  //geo.initTerrain("./../data/Heightmap.bmp", { 10, 2, 10 });
  //geo2.initTriangle({ 3.0f, 3.0f });
  geo_plane.initFromFile("./../data/geometries/plane/plane.x");
  geo_prop.initFromFile("./../data/geometries/plane/prop.x");
  geo_gun.initFromFile("./../data/geometries/plane/gun.x");
  geo_turret.initFromFile("./../data/geometries/plane/turret.x");
  geo_terrain.initTerrain("./../data/Heightmap.bmp", { 100.0f, 10.0f, 100.0f });
  mat.init();
  texture.load("./../data/texture.png");

  Object plane_root, plane, prop, turret, gun, cam_node, terrain, root;

  root.addComponent(ComponentType::Transform);
  root.init();

  terrain.addComponent(ComponentType::Transform);
  terrain.addComponent(ComponentType::Render3D);
  terrain.render3D_->setup(&mat, &geo_terrain);
  terrain.render3D_->init();
  terrain.init();
  terrain.transform_->set_position(-50.0f, -10.0f, -30.0f);
  root.addChild(&terrain);

  plane_root.addComponent(ComponentType::Transform);
  plane_root.init();
  root.addChild(&plane_root);

  cam_node.addComponent(ComponentType::Transform);
  cam_node.init();
  cam_node.transform_->set_position(0.0f, 4.5f, -15.0f);
  plane_root.addChild(&cam_node);

  plane.addComponent(ComponentType::Transform);
  plane.addComponent(ComponentType::Render3D);
  plane.render3D_->setup(&mat, &geo_plane);
  plane.render3D_->init();
  plane.init();
  plane_root.addChild(&plane);

  prop.addComponent(ComponentType::Transform);
  prop.addComponent(ComponentType::Render3D);
  prop.render3D_->setup(&mat, &geo_prop);
  prop.render3D_->init();
  prop.init();
  prop.transform_->set_position(0.0f, 0.0f, 1.9f);
  plane.addChild(&prop);

  turret.addComponent(ComponentType::Transform);
  turret.addComponent(ComponentType::Render3D);
  turret.render3D_->setup(&mat, &geo_turret);
  turret.render3D_->init();
  turret.init();
  turret.transform_->set_position(0.0f, 1.05f, -1.3f);
  plane.addChild(&turret);

  gun.addComponent(ComponentType::Transform);
  gun.addComponent(ComponentType::Render3D);
  gun.render3D_->setup(&mat, &geo_gun);
  gun.render3D_->init();
  gun.init();
  gun.transform_->set_position(0.0f, 0.5f, 0.0f);
  turret.addChild(&gun);
  //a.addChild(&b);
  //b.addChild(&c);

  //plane_root.transform_->set_rotation(0.0f, DirectX::XM_PI, 0.0f);
  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());
  auto& cam = Core::instance().cam_;
  cam.set_position(0.0f, 4.5f, -15.0f);

  float speed = 0.1f;
  float rotation_speed = 0.0001f;

  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened() && 
         !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {

    DirectX::XMFLOAT3 temp;
    DirectX::XMStoreFloat3(&temp, cam_node.transform_->worldPosition());
    cam.set_position(temp.x, temp.y, temp.z);
    DirectX::XMStoreFloat3(&temp, plane_root.transform_->worldPosition());
    cam.set_target(temp.x, temp.y, temp.z);
    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_W)) {
      DirectX::XMFLOAT3 forward;
      DirectX::XMStoreFloat3(&forward, DirectX::XMVectorScale(plane_root.transform_->forward_vector(), speed));
      plane_root.transform_->traslate(forward.x, forward.y, forward.z);
    }
    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_S)) {
      DirectX::XMFLOAT3 forward;
      DirectX::XMStoreFloat3(&forward, DirectX::XMVectorScale(plane_root.transform_->forward_vector(), speed));
      plane_root.transform_->traslate(-forward.x, -forward.y, -forward.z);
    }
    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_A)) {
      plane_root.transform_->rotate(0.0f, -rotation_speed, 0.0f);
    }
    if (Input::IsKeyboardButtonPressed(Input::kKeyboardButton_D)) {
      plane_root.transform_->rotate(0.0f, rotation_speed, 0.0f);
    }
    

    texture.use();
    cam.render(&root);
    prop.transform_->set_rotation(0.0f, 0.0f, (float32)Time() * 0.01f);
    turret.transform_->set_rotation(0.0f, (float32)Time() * 0.001f, 0.0f);

	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::ShowTestWindow(0);

    Window::EndFrame();
  }

  Window::Close();

  // Al usar un winmain, nos vemos obligados a usar una aplicacion de tipo win32 que no
  // tiene ventana de consola de comandos, asi que con esta funcion sera como hacer 
  // un printf pero los mensajes apareceran en la ventana OUTPUT del VISUAL PREMOH.
  OutputDebugString(textico);
  return 0;
}

}; /* SLX */
