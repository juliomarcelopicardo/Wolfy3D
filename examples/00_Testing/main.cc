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
  
DirectX::XMFLOAT3 tweening_func(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 destiny, float alpha) {
  float x_variation = (destiny.x - origin.x) * alpha;
  float y_variation = (destiny.y - origin.y) * alpha;
  float z_variation = (destiny.z - origin.z) * alpha;

  return{ origin.x + x_variation, origin.y + y_variation, origin.z + z_variation };
}

float tweening_func(float origin, float destiny, float alpha) {
  float variation = (destiny - origin) * alpha;
  return origin + variation;
}

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

    

    void init(Material& mat) {

      geo_body.initFromFile("./../data/geometries/robot/body.x");
      geo_left_ankle.initFromFile("./../data/geometries/robot/left_ankle.x");
      geo_left_elbow.initFromFile("./../data/geometries/robot/left_elbow.x");
      geo_left_hip.initFromFile("./../data/geometries/robot/left_hip.x");
      geo_left_knee.initFromFile("./../data/geometries/robot/left_knee.x");
      geo_left_shoulder.initFromFile("./../data/geometries/robot/left_shoulder.x");
      geo_left_wrist.initFromFile("./../data/geometries/robot/left_wrist.x");
      geo_right_ankle.initFromFile("./../data/geometries/robot/right_ankle.x");
      geo_right_elbow.initFromFile("./../data/geometries/robot/right_elbow.x");
      geo_right_hip.initFromFile("./../data/geometries/robot/right_hip.x");
      geo_right_knee.initFromFile("./../data/geometries/robot/right_knee.x");
      geo_right_shoulder.initFromFile("./../data/geometries/robot/right_shoulder.x");
      geo_right_wrist.initFromFile("./../data/geometries/robot/right_wrist.x");
      geo_neck.initFromFile("./../data/geometries/robot/neck.x");
      geo_pelvis_presley.initFromFile("./../data/geometries/robot/pelvis.x");

      root.transform().set_position(0.0f, 0.0f, 0.0f);

      pelvis_presley.addComponent(ComponentType::Render3D, &mat, &geo_pelvis_presley);
      pelvis_presley.transform().set_position(-0.0250011f, 1.5250000f, -0.0000005f);
      root.addChild(&pelvis_presley);

      body.addComponent(ComponentType::Render3D, &mat, &geo_body);
      body.transform().set_position(0.0500099f, 4.3749992f, 0.0000003f);
      pelvis_presley.addChild(&body);

      left_shoulder.addComponent(ComponentType::Render3D, &mat, &geo_left_shoulder);
      left_shoulder.transform().set_position(4.6000000f, 0.0000000f, -0.0009992f);
      body.addChild(&left_shoulder);

      left_elbow.addComponent(ComponentType::Render3D, &mat, &geo_left_elbow);
      left_elbow.transform().set_position(3.4250019f, -0.0499817f, -0.0004262f);
      left_shoulder.addChild(&left_elbow);

      left_wrist.addComponent(ComponentType::Render3D, &mat, &geo_left_wrist);
      left_wrist.transform().set_position(5.5250008f, -0.0999710f, 0.0003968f);
      left_elbow.addChild(&left_wrist);

      right_shoulder.addComponent(ComponentType::Render3D, &mat, &geo_right_shoulder);
      right_shoulder.transform().set_position(-4.4500023f, 0.0500000f, -0.0000021f);
      body.addChild(&right_shoulder);

      right_elbow.addComponent(ComponentType::Render3D, &mat, &geo_right_elbow);
      right_elbow.transform().set_position(-3.3999996f, 0.0250229f, -0.0000194f);
      right_shoulder.addChild(&right_elbow);

      right_wrist.addComponent(ComponentType::Render3D, &mat, &geo_right_wrist);
      right_wrist.transform().set_position(-6.0000381f, -0.1750183f, 0.0007156f);
      right_elbow.addChild(&right_wrist);

      neck.addComponent(ComponentType::Render3D, &mat, &geo_neck);
      neck.transform().set_position(0.0249983f, 3.6625015f, 2.5999998f);
      body.addChild(&neck);

      left_hip.addComponent(ComponentType::Render3D, &mat, &geo_left_hip);
      left_hip.transform().set_position(1.9500000f, -0.7724991f, 0.000000f);
      root.addChild(&left_hip);

      left_knee.addComponent(ComponentType::Render3D, &mat, &geo_left_knee);
      left_knee.transform().set_position(0.0000006f, -2.2200001f, 0.000000f);
      left_hip.addChild(&left_knee);

      left_ankle.addComponent(ComponentType::Render3D, &mat, &geo_left_ankle);
      left_ankle.transform().set_position(-0.0800152f, -3.6399994f, -0.0000098f);
      left_knee.addChild(&left_ankle);

      right_hip.addComponent(ComponentType::Render3D, &mat, &geo_right_hip);
      right_hip.transform().set_position(-1.9500000f, -0.7724991f, 0.000000f);
      root.addChild(&right_hip);

      right_knee.addComponent(ComponentType::Render3D, &mat, &geo_right_knee);
      right_knee.transform().set_position(0.0000006f, -2.2000000f, 0.000000f);
      right_hip.addChild(&right_knee);

      right_ankle.addComponent(ComponentType::Render3D, &mat, &geo_right_ankle);
      right_ankle.transform().set_position(0.0199911f, -3.6799995f, 0.0000039f);
      right_knee.addChild(&right_ankle);
    }
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
  //root.addChild(&terrain);
  
  Robot robot;
  robot.init(mat);
  root.addChild(&robot.root);

  float animation_speed = 0.0001f;
  float animation_alpha = 0.0f;
  int32 index = 0;
  float animation[10] = { 0.0416666679084301, 0.2083333283662796, 0.5, 0.5833333134651184, 0.6666666865348816, 0.9166666865348816, 1.125, 1.208333373069763, 1.291666626930237, 1.666666626930237 };


  //plane_root.transform().set_rotation(0.0f, DirectX::XM_PI, 0.0f);
  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());
  auto& cam = Core::instance().cam_;
  cam.is_navigation_enabled_ = true;
  cam.set_position(0.0f, 4.5f, 45.0f);

  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened() && 
         !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {

    animation_alpha += animation_speed;
    if (animation_alpha > 1.0f) {
      index++;
      animation_alpha = 0.0f;
    }

    robot.pelvis_presley.transform().set_rotation(tweening_func(animation[index], animation[index + 1], animation_alpha), 0.0f, 0.0f);



    cam.render(&root);

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
