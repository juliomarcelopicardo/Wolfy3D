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

  struct Robot {
    CoreGeometry geo_body;
    CoreGeometry geo_left_ankle;
    CoreGeometry geo_left_elbow;
    CoreGeometry geo_left_hip;
    CoreGeometry geo_left_knee;
    CoreGeometry geo_left_shoulder;
    CoreGeometry geo_left_wrist;
    CoreGeometry geo_right_ankle;
    CoreGeometry geo_right_elbow;
    CoreGeometry geo_right_hip;
    CoreGeometry geo_right_knee;
    CoreGeometry geo_right_shoulder;
    CoreGeometry geo_right_wrist;
    CoreGeometry geo_neck;
    CoreGeometry geo_pelvis_presley;
    Object root;
    Object body;
    Object left_ankle;
    Object left_elbow;
    Object left_hip;
    Object left_knee;
    Object left_shoulder;
    Object left_wrist;
    Object right_ankle;
    Object right_elbow;
    Object right_hip;
    Object right_knee;
    Object right_shoulder;
    Object right_wrist;
    Object neck;
    Object pelvis_presley;
  };

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
  //root.addChild(&plane_root);

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



  /*
   ROBOTTTTTTTTTTTT
  
  */
  Robot robot;
  robot.geo_body.initFromFile("./../data/geometries/robot/body.x");
  robot.geo_left_ankle.initFromFile("./../data/geometries/robot/left_ankle.x");
  robot.geo_left_elbow.initFromFile("./../data/geometries/robot/left_elbow.x");
  robot.geo_left_hip.initFromFile("./../data/geometries/robot/left_hip.x");
  robot.geo_left_knee.initFromFile("./../data/geometries/robot/left_knee.x");
  robot.geo_left_shoulder.initFromFile("./../data/geometries/robot/left_shoulder.x");
  robot.geo_left_wrist.initFromFile("./../data/geometries/robot/left_wrist.x");
  robot.geo_right_ankle.initFromFile("./../data/geometries/robot/right_ankle.x");
  robot.geo_right_elbow.initFromFile("./../data/geometries/robot/right_elbow.x");
  robot.geo_right_hip.initFromFile("./../data/geometries/robot/right_hip.x");
  robot.geo_right_knee.initFromFile("./../data/geometries/robot/right_knee.x");
  robot.geo_right_shoulder.initFromFile("./../data/geometries/robot/right_shoulder.x");
  robot.geo_right_wrist.initFromFile("./../data/geometries/robot/right_wrist.x");
  robot.geo_neck.initFromFile("./../data/geometries/robot/neck.x");
  robot.geo_pelvis_presley.initFromFile("./../data/geometries/robot/pelvis.x");


  robot.root.init();
  robot.root.addComponent(ComponentType::Transform);
  robot.root.init();
  root.addChild(&robot.root);
  robot.root.transform_->set_position(0.0f, 0.0f, 20.0f);

  robot.body.addComponent(ComponentType::Transform);
  robot.body.addComponent(ComponentType::Render3D);
  robot.body.render3D_->setup(&mat, &robot.geo_body);
  robot.body.render3D_->init();
  robot.body.init();
  robot.body.transform_->set_position(0.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.body);

  robot.left_ankle.addComponent(ComponentType::Transform);
  robot.left_ankle.addComponent(ComponentType::Render3D);
  robot.left_ankle.render3D_->setup(&mat, &robot.geo_left_ankle);
  robot.left_ankle.render3D_->init();
  robot.left_ankle.init();
  robot.left_ankle.transform_->set_position(5.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_ankle);

  robot.left_elbow.addComponent(ComponentType::Transform);
  robot.left_elbow.addComponent(ComponentType::Render3D);
  robot.left_elbow.render3D_->setup(&mat, &robot.geo_left_elbow);
  robot.left_elbow.render3D_->init();
  robot.left_elbow.init();
  robot.left_elbow.transform_->set_position(0.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_elbow);

  robot.left_hip.addComponent(ComponentType::Transform);
  robot.left_hip.addComponent(ComponentType::Render3D);
  robot.left_hip.render3D_->setup(&mat, &robot.geo_left_hip);
  robot.left_hip.render3D_->init();
  robot.left_hip.init();
  robot.left_hip.transform_->set_position(0.0f, 5.0f, 0.0f);
  robot.root.addChild(&robot.left_hip);

  robot.left_knee.addComponent(ComponentType::Transform);
  robot.left_knee.addComponent(ComponentType::Render3D);
  robot.left_knee.render3D_->setup(&mat, &robot.geo_left_knee);
  robot.left_knee.render3D_->init();
  robot.left_knee.init();
  robot.left_knee.transform_->set_position(-5.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_knee);

  robot.left_shoulder.addComponent(ComponentType::Transform);
  robot.left_shoulder.addComponent(ComponentType::Render3D);
  robot.left_shoulder.render3D_->setup(&mat, &robot.geo_left_shoulder);
  robot.left_shoulder.render3D_->init();
  robot.left_shoulder.init();
  robot.left_shoulder.transform_->set_position(10.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_shoulder);

  robot.left_wrist.addComponent(ComponentType::Transform);
  robot.left_wrist.addComponent(ComponentType::Render3D);
  robot.left_wrist.render3D_->setup(&mat, &robot.geo_left_wrist);
  robot.left_wrist.render3D_->init();
  robot.left_wrist.init();
  robot.left_wrist.transform_->set_position(-10.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_wrist);

  robot.right_ankle.addComponent(ComponentType::Transform);
  robot.right_ankle.addComponent(ComponentType::Render3D);
  robot.right_ankle.render3D_->setup(&mat, &robot.geo_right_ankle);
  robot.right_ankle.render3D_->init();
  robot.right_ankle.init();
  robot.right_ankle.transform_->set_position(0.0f, -5.0f, 0.0f);
  robot.root.addChild(&robot.right_ankle);

  robot.right_elbow.addComponent(ComponentType::Transform);
  robot.right_elbow.addComponent(ComponentType::Render3D);
  robot.right_elbow.render3D_->setup(&mat, &robot.geo_right_elbow);
  robot.right_elbow.render3D_->init();
  robot.right_elbow.init();
  robot.right_elbow.transform_->set_position(0.0f, -10.0f, 0.0f);
  robot.root.addChild(&robot.right_elbow);

  robot.right_hip.addComponent(ComponentType::Transform);
  robot.right_hip.addComponent(ComponentType::Render3D);
  robot.right_hip.render3D_->setup(&mat, &robot.geo_right_hip);
  robot.right_hip.render3D_->init();
  robot.right_hip.init();
  robot.right_hip.transform_->set_position(10.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.right_hip);

  robot.right_knee.addComponent(ComponentType::Transform);
  robot.right_knee.addComponent(ComponentType::Render3D);
  robot.right_knee.render3D_->setup(&mat, &robot.geo_right_knee);
  robot.right_knee.render3D_->init();
  robot.right_knee.init();
  robot.right_knee.transform_->set_position(10.0f, 5.0f, 0.0f);
  robot.root.addChild(&robot.right_knee);

  robot.right_shoulder.addComponent(ComponentType::Transform);
  robot.right_shoulder.addComponent(ComponentType::Render3D);
  robot.right_shoulder.render3D_->setup(&mat, &robot.geo_right_shoulder);
  robot.right_shoulder.render3D_->init();
  robot.right_shoulder.init();
  robot.right_shoulder.transform_->set_position(5.0f, 10.0f, 0.0f);
  robot.root.addChild(&robot.right_shoulder);

  robot.right_wrist.addComponent(ComponentType::Transform);
  robot.right_wrist.addComponent(ComponentType::Render3D);
  robot.right_wrist.render3D_->setup(&mat, &robot.geo_right_wrist);
  robot.right_wrist.render3D_->init();
  robot.right_wrist.init();
  robot.right_wrist.transform_->set_position(-5.0f, 10.0f, 0.0f);
  robot.root.addChild(&robot.right_wrist);

  robot.neck.addComponent(ComponentType::Transform);
  robot.neck.addComponent(ComponentType::Render3D);
  robot.neck.render3D_->setup(&mat, &robot.geo_neck);
  robot.neck.render3D_->init();
  robot.neck.init();
  robot.neck.transform_->set_position(-10.0f, -5.0f, 0.0f);
  robot.root.addChild(&robot.neck);

  robot.pelvis_presley.addComponent(ComponentType::Transform);
  robot.pelvis_presley.addComponent(ComponentType::Render3D);
  robot.pelvis_presley.render3D_->setup(&mat, &robot.geo_pelvis_presley);
  robot.pelvis_presley.render3D_->init();
  robot.pelvis_presley.init();
  robot.pelvis_presley.transform_->set_position(10.0f, -10.0f, 0.0f);
  robot.root.addChild(&robot.pelvis_presley);











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

    if (Input::IsMouseButtonDown(Input::kMouseButton_Left)) {
      DirectX::XMFLOAT3 position = { 1.0f, 0.0f, 0.0f };
      robot.neck.transform_->set_world_position(DirectX::XMLoadFloat3(&position));
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
