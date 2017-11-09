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
  /*
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

  terrain.addComponent(ComponentType::Render3D, &mat, &geo_terrain);
  terrain.transform().set_position(-50.0f, -10.0f, -30.0f);
  root.addChild(&terrain);

  cam_node.transform().set_position(0.0f, 4.5f, -15.0f);
  plane_root.addChild(&cam_node);

  plane.addComponent(ComponentType::Render3D, &mat, &geo_plane);
  plane_root.addChild(&plane);

  prop.addComponent(ComponentType::Render3D, &mat, &geo_prop);
  prop.transform().set_position(0.0f, 0.0f, 1.9f);
  plane.addChild(&prop);

  turret.addComponent(ComponentType::Render3D, &mat, &geo_turret);
  turret.transform().set_position(0.0f, 1.05f, -1.3f);
  plane.addChild(&turret);

  gun.addComponent(ComponentType::Render3D, &mat, &geo_gun);
  gun.transform().set_position(0.0f, 0.5f, 0.0f);
  turret.addChild(&gun);

  */
  /*
   ROBOTTTTTTTTTTTT
  
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



  root.addChild(&robot.root);
  robot.root.transform().set_position(0.0f, 0.0f, 20.0f);

  robot.body.addComponent(ComponentType::Render3D, &mat, &robot.geo_body);
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
  cam.set_position(0.0f, 4.5f, -15.0f);

  float speed = 0.1f;
  float rotation_speed = 0.0001f;

  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened() && 
         !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {

    if (Input::IsMouseButtonDown(Input::kMouseButton_Left)) {
      DirectX::XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
      robot.neck.transform().set_world_position(DirectX::XMLoadFloat3(&position));
    }
    if (Input::IsMouseButtonDown(Input::kMouseButton_Middle)) {
      DirectX::XMFLOAT3 position = { 1.0f, 0.0f, 0.0f };
      robot.neck.transform().worldTraslate(1.0f, 0.0f, 0.0f);
    }

    texture.use();
    cam.render(&root);
    prop.transform().set_rotation(0.0f, 0.0f, (float32)Time() * 0.01f);
    turret.transform().set_rotation(0.0f, (float32)Time() * 0.001f, 0.0f);

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
  */


int32 main() {

  Window::Init(1024, 978);

  CoreGeometry geo, geo2;
  CoreMaterial mat;
  CoreTexture texture;
  Object root, cube, cube1;

  mat.init();
  texture.load("./../data/texture.png");
  //geo.initQuad();
  geo.initCube();
  //geo.initPyramid(50 ,1, 3);
  //geo.initFromFile("./../data/geometries/plane/plane.x");
  //geo.initExtruded(100, 2.0f, 1.0f, 4.0f);
  //geo.initTerrain("./../data/Heightmap.bmp", { 10, 2, 10 });
  //geo2.initTriangle({ 3.0f, 3.0f });

    char textico[256];
    sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());
    auto& cam = Core::instance().cam_;
    cam.set_position(0.0f, 4.5f, -15.0f);

    float speed = 0.1f;
    float rotation_speed = 0.0001f;

    cube.addComponent(ComponentType::Render3D, &mat, &geo);
    cube1.addComponent(ComponentType::Render3D, &mat, &geo);
    cube.transform().set_position(1.0f, 0.0f, 0.0f);
    cube1.transform().set_position(-2.0f, 0.0f, 0.0f);

    root.addChild(&cube);
    //root.addChild(&cube1);
    


      DirectX::XMVECTOR quat;
      DirectX::XMFLOAT4 quatf;
      DirectX::XMFLOAT3 euler = { 1.9f, 1.2f, 1.3f };
   
      //roll pitch yaw

      cube.transform().set_rotation(euler);  
     
     
      /*
      DirectX::XMFLOAT4X4 m;
      DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&cube.transform().local_model_matrix_)));

      float sp = -m._32;
      if(sp <= -1.0f) {
        euler.x = -1.570796f;
      } else if(sp >= 1.0f) {
          euler.x = 1.570796f; 
        } else{ euler.x = asin(sp);
          }
            if(fabs(sp) > 0.9999f) {
              euler.z = 0.0f;
            euler.y = atan2(-m._13, m._11);
          } else{
            euler.y = atan2(m._31, m._33);
            euler.z = atan2(m._12, m._22);
          }

      */
      /*
      DirectX::XMVECTOR quat_x, quat_y, quat_z;
      quat_x = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), euler.x);
      quat_y = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), euler.y);
      quat_z = DirectX::XMQuaternionRotationAxis(DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), euler.z);
      quat = DirectX::XMQuaternionMultiply(DirectX::XMQuaternionMultiply(quat_z, quat_x), quat_y);
      quat = DirectX::XMQuaternionNormalize(quat);
      float32 sp = -2.0f * (quatf.y * quatf.z + quatf.w * quatf.x);

    if(fabs(sp) > 0.9999f) {
        euler.z = 1.570796f * sp;
        euler.x = atan2(-quatf.x * quatf.z - quatf.w * quatf.y, 0.5f - quatf.y * quatf.y - quatf.z * quatf.z);
        euler.y = 0.0f;
    } else{
      // Compute ang l e s
        euler.x = asin(sp);
        euler.y = atan2(quatf.x * quatf.z - quatf.w * quatf.y , 0.5f - quatf.x * quatf.x * quatf.y * quatf.y);
        euler.z = atan2(quatf.x * quatf.y - quatf.w * quatf.z , 0.5f - quatf.x * quatf.x - quatf.z * quatf.z);
    }
      */
    


    // enter the main loop:
    while (Window::StartFrame() && Window::IsOpened() &&
    !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {

    if (Input::IsMouseButtonPressed(Input::kMouseButton_Left)) {
      cube.transform().traslate(0.001f, 0.0f, 0.0f);
      cube1.transform().traslate(-0.001f, 0.0f, 0.0f);
    }
    if (Input::IsMouseButtonPressed(Input::kMouseButton_Right)) {
      cube.transform().traslate(-0.001f, 0.0f, 0.0f);
      cube1.transform().traslate(0.001f, 0.0f, 0.0f);
    }

    cube.transform().rotate(0.0f, 0.0002f, 0.0f);
    root.transform().rotate(0.0001f, 0.0f, 0.0001f);
    cube1.transform().set_rotation(cube.transform().world_rotation_float3());
    texture.use();
    cam.render(&root);
    cam.render(&cube1);
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
