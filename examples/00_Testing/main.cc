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
#include "core/cam.h"

namespace W3D {
  
int32 main() {
  
  Window::Init(1024, 978);

  Geo geo, geo2;
  Geo geo_plane, geo_prop, geo_turret, geo_gun, geo_terrain;
  MaterialDiffuse mat; 
  MaterialNormals mat_normals;
  MaterialTextured mat_texture;
  Texture texture, texture2;
  

  Texture assesment[4];
  assesment[0].load("./../data/textures/materialmap.dds");
  assesment[1].load("./../data/textures/grass.dds");
  assesment[2].load("./../data/textures/moss.dds");
  assesment[3].load("./../data/textures/asphalt.dds");
  MaterialAssesment matass;
  matass.texture_materialmap_ = &assesment[0];
  matass.texture_grass_ = &assesment[1];
  matass.texture_moss_ = &assesment[2];
  matass.texture_asphalt_ = &assesment[3];

  struct Robot {
    Geo geo_body;
    Geo geo_left_ankle;
    Geo geo_left_elbow;
    Geo geo_left_hip;
    Geo geo_left_knee;
    Geo geo_left_shoulder;
    Geo geo_left_wrist;
    Geo geo_right_ankle;
    Geo geo_right_elbow;
    Geo geo_right_hip;
    Geo geo_right_knee;
    Geo geo_right_shoulder;
    Geo geo_right_wrist;
    Geo geo_neck;
    Geo geo_pelvis_presley;
    Entity root;
    Entity body;
    Entity left_ankle;
    Entity left_elbow;
    Entity left_hip;
    Entity left_knee;
    Entity left_shoulder;
    Entity left_wrist;
    Entity right_ankle;
    Entity right_elbow;
    Entity right_hip;
    Entity right_knee;
    Entity right_shoulder;
    Entity right_wrist;
    Entity neck;
    Entity pelvis_presley;
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
  geo_terrain.initTerrain("./../data/textures/Heightmap.bmp", { 100.0f, 7.0f, 100.0f });

  texture.load("./../data/textures/texture.png");
  texture2.load("./../data/textures/turtle.png");
  mat_texture.set_texture(&texture);

  Entity plane_root, plane, prop, turret, gun, cam_node, terrain, root;

  
  terrain.addComponent(ComponentType::Render3D, &matass, &geo_terrain);
  terrain.transform().set_position(-50.0f, -10.0f, -30.0f);
  root.addChild(&terrain);
  //root.addChild(&plane_root);

  cam_node.transform().set_position(0.0f, 4.5f, -15.0f);
  plane_root.addChild(&cam_node);

  plane.addComponent(ComponentType::Render3D, &mat_texture, nullptr);
  plane.transform().set_scale(3.0f);
  plane_root.addChild(&plane);

  prop.addComponent(ComponentType::Render3D, &mat, &geo_prop);
  prop.transform().set_position(0.0f, 0.0f, 1.9f);
  //plane.addChild(&prop);

  turret.addComponent(ComponentType::Render3D, &mat, &geo_turret);
  turret.transform().set_position(0.0f, 1.05f, -1.3f);
  //plane.addChild(&turret);

  gun.addComponent(ComponentType::Render3D, &mat, &geo_gun);
  gun.transform().set_position(0.0f, 0.5f, 0.0f);
  //turret.addChild(&gun);

  
  
  
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



  //root.addChild(&robot.root);
  robot.root.transform().set_position(0.0f, 0.0f, 20.0f);

  robot.body.addComponent(ComponentType::Render3D, &mat, nullptr);
  robot.body.transform().set_position(0.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.body);

  robot.left_ankle.addComponent(ComponentType::Render3D, &mat, &robot.geo_left_ankle);
  robot.left_ankle.transform().set_position(5.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_ankle);

  robot.left_elbow.addComponent(ComponentType::Render3D, &mat, &robot.geo_left_elbow);
  robot.left_elbow.transform().set_position(0.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_elbow);

  robot.left_hip.addComponent(ComponentType::Render3D, &mat, &robot.geo_left_hip);
  robot.left_hip.transform().set_position(0.0f, 5.0f, 0.0f);
  robot.root.addChild(&robot.left_hip);

  robot.left_knee.addComponent(ComponentType::Render3D, &mat, &robot.geo_left_knee);
  robot.left_knee.transform().set_position(-5.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_knee);

  robot.left_shoulder.addComponent(ComponentType::Render3D, &mat, &robot.geo_left_shoulder);
  robot.left_shoulder.transform().set_position(10.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_shoulder);

  robot.left_wrist.addComponent(ComponentType::Render3D, &mat, &robot.geo_left_wrist);
  robot.left_wrist.transform().set_position(-10.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.left_wrist);

  robot.right_ankle.addComponent(ComponentType::Render3D, &mat, &robot.geo_right_ankle);
  robot.right_ankle.transform().set_position(0.0f, -5.0f, 0.0f);
  robot.root.addChild(&robot.right_ankle);

  robot.right_elbow.addComponent(ComponentType::Render3D, &mat, &robot.geo_right_elbow);
  robot.right_elbow.transform().set_position(0.0f, -10.0f, 0.0f);
  robot.root.addChild(&robot.right_elbow);

  robot.right_hip.addComponent(ComponentType::Render3D, &mat, &robot.geo_right_hip);
  robot.right_hip.transform().set_position(10.0f, 0.0f, 0.0f);
  robot.root.addChild(&robot.right_hip);

  robot.right_knee.addComponent(ComponentType::Render3D, &mat, &robot.geo_right_knee);
  robot.right_knee.transform().set_position(10.0f, 5.0f, 0.0f);
  robot.root.addChild(&robot.right_knee);

  robot.right_shoulder.addComponent(ComponentType::Render3D, &mat, &robot.geo_right_shoulder);
  robot.right_shoulder.transform().set_position(5.0f, 10.0f, 0.0f);
  robot.root.addChild(&robot.right_shoulder);

  robot.right_wrist.addComponent(ComponentType::Render3D, &mat, &robot.geo_right_wrist);
  robot.right_wrist.transform().set_position(-5.0f, 10.0f, 0.0f);
  robot.root.addChild(&robot.right_wrist);

  robot.neck.addComponent(ComponentType::Render3D, &mat, &robot.geo_neck);
  robot.neck.transform().set_position(-10.0f, -5.0f, 0.0f);
  robot.root.addChild(&robot.neck);

  robot.pelvis_presley.addComponent(ComponentType::Render3D, &mat, &robot.geo_pelvis_presley);
  robot.pelvis_presley.transform().set_position(10.0f, -10.0f, 0.0f);
  robot.root.addChild(&robot.pelvis_presley);


  //plane_root.transform().set_rotation(0.0f, DirectX::XM_PI, 0.0f);
  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());
  auto& cam = Core::instance().cam_;
  cam.is_navigation_enabled_ = true;
  cam.set_position(0.0f, 4.5f, -15.0f);

  float speed = 0.1f;
  float rotation_speed = 0.0001f;



  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened() && 
         !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {

    if (Input::IsMouseButtonDown(Input::kMouseButton_Left)) {
      DirectX::XMFLOAT3 position_vector = { 0.0f, 0.0f, 0.0f };
      robot.neck.transform().set_world_position(DirectX::XMLoadFloat3(&position_vector));
    }
    if (Input::IsMouseButtonDown(Input::kMouseButton_Middle)) {
      DirectX::XMFLOAT3 position_vector = { 1.0f, 0.0f, 0.0f };
      robot.neck.transform().worldTraslate(1.0f, 0.0f, 0.0f);
    }

    cam.render(&root);
    prop.transform().set_rotation(0.0f, 0.0f, (float32)Time() * 0.01f);
    turret.transform().set_rotation(0.0f, (float32)Time() * 0.001f, 0.0f);

	//ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	//ImGui::ShowTestWindow(0);

    Window::EndFrame();
  }

  Window::Close();

  // Al usar un winmain, nos vemos obligados a usar una aplicacion de tipo win32 que no
  // tiene ventana de consola de comandos, asi que con esta funcion sera como hacer 
  // un printf pero los mensajes apareceran en la ventana OUTPUT del VISUAL PREMOH.
  OutputDebugString(textico);
  return 0;
}


}; /* W3D */
