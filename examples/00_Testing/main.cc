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

  struct BoneInfo {

    BoneInfo() {
      speed = 1.0f;
      alpha = 0.0f;
      timer = 0.0f;
      timer_limit = 0.0f;
      step_destiny = 0;
    }

    std::string name;
    std::vector<DirectX::XMFLOAT3> rotation_timers;
    std::vector<DirectX::XMFLOAT3> rotation_radians;
    uint32 vectors_size;

    // Animation info
    DirectX::XMFLOAT3 origin_rotation; // To interpole.
    DirectX::XMFLOAT3 destiny_rotation; // To interpole.
    float32 alpha;
    float32 timer;
    float32 timer_limit;
    float32 speed;
    uint32 step_destiny; // Nos dira a que paso queremos llegar en las anims.

    void startAnimationWithInitialBlending(DirectX::XMFLOAT3 rot_origin) {
      step_destiny = 1;
      alpha = 0;
      timer = 0.0f;
      timer_limit = rotation_timers[step_destiny].x;
      origin_rotation = rot_origin;
      destiny_rotation = rotation_radians[step_destiny];
    }

    void startAnimationWithoutBlending() {
      step_destiny = 1;
      alpha = 0;
      timer = 0.0f;
      timer_limit = rotation_timers[step_destiny].x;
      origin_rotation = rotation_radians[0];
      destiny_rotation = rotation_radians[step_destiny];
    }

    void startNewStep() {
      step_destiny += 1;
      if (step_destiny == vectors_size) {
        step_destiny = 1;
      }
      timer = 0.0f;
      timer_limit = rotation_timers[step_destiny].x; // Ya que son todos iguales x y z
      origin_rotation = destiny_rotation;
      destiny_rotation = rotation_radians[step_destiny];
    }

    // Retorna la rotacion actual.
    DirectX::XMFLOAT3 update(const float32 delta_time) {
      timer += speed * delta_time;

      // Relleno el alpha.
      alpha = timer / timer_limit; // obtengo valor entre 0 y 1
      if (alpha > 1.0f) { 
        alpha = 0.0f;
      }
      // Compruebo si he terminado el step.
      if (timer > timer_limit) {
        startNewStep();
      }

      // retorno la rotacion que corresponde.
      return tweening_func(origin_rotation, destiny_rotation, alpha);
    }

    enum Axis {
      kAxis_X = 0,
      kAxis_Y = 1,
      kAxis_Z = 2,
    };

    void setupAxisRotation(Axis axis, tinyxml2::XMLNode* root) {

      std::string rot_text;
      tinyxml2::XMLElement* time_elem = nullptr;
      tinyxml2::XMLElement* rot_elem = nullptr;
      std::vector<float32> temp;

      switch (axis) {
        case BoneInfo::kAxis_X: { rot_text = name + ".rotateX"; }break;
        case BoneInfo::kAxis_Y: { rot_text = name + ".rotateY"; }break;
        case BoneInfo::kAxis_Z: { rot_text = name + ".rotateZ"; }break;
      }

      // Searching for the correct child.
      for (auto* i = root->FirstChildElement(); i != nullptr; i = i->NextSiblingElement()) {
        std::string id = i->Attribute("id");
        if (id == rot_text) {
          time_elem = i->FirstChildElement()->FirstChildElement("float_array");
          rot_elem = i->FirstChildElement()->NextSiblingElement()->FirstChildElement("float_array");
          break;
        }
      }

      if (!time_elem || !rot_elem) {
        MessageBox(NULL, "Error loading animation from file", "ERROR", MB_OK);
      }

      // TIMERS
      vectors_size = time_elem->IntAttribute("count");
      rotation_timers.resize(vectors_size);
      std::istringstream time_string(time_elem->GetText());
      std::copy(std::istream_iterator<float32>(time_string), 
                std::istream_iterator<float32>(), 
                std::back_inserter(temp));

      for (int i = 0; i < vectors_size; i++) {
        switch (axis) {
          case BoneInfo::kAxis_X: { rotation_timers[i].x = temp[i]; } break;
          case BoneInfo::kAxis_Y: { rotation_timers[i].y = temp[i]; } break;
          case BoneInfo::kAxis_Z: { rotation_timers[i].z = temp[i]; } break;
        } 
      }

      temp.clear();
      // ANGLES
      vectors_size = rot_elem->IntAttribute("count");
      rotation_radians.resize(vectors_size);
      std::istringstream rot_string(rot_elem->GetText());
      std::copy(std::istream_iterator<float32>(rot_string), 
                std::istream_iterator<float32>(), 
                std::back_inserter(temp));

      for (int i = 0; i < vectors_size; i++) {
        //rotation_radians[i].x = DirectX::XMConvertToRadians(temp[i]);
        switch (axis) {
          case BoneInfo::kAxis_X: { rotation_radians[i].x = DirectX::XMConvertToRadians(temp[i]); } break;
          case BoneInfo::kAxis_Y: { rotation_radians[i].y = DirectX::XMConvertToRadians(temp[i]); } break;
          case BoneInfo::kAxis_Z: { rotation_radians[i].z = DirectX::XMConvertToRadians(temp[i]); } break;
        }
      }
    }


    void setup(tinyxml2::XMLDocument& doc) {
      // Get the main node.
      tinyxml2::XMLNode* root = doc.FirstChild();

      setupAxisRotation(kAxis_X, root);
      setupAxisRotation(kAxis_Y, root);
      setupAxisRotation(kAxis_Z, root);

    }

  };

  struct Animation {

    BoneInfo bone_root;
    BoneInfo bone_body;
    BoneInfo bone_left_ankle;
    BoneInfo bone_left_elbow;
    BoneInfo bone_left_hip;
    BoneInfo bone_left_knee;
    BoneInfo bone_left_shoulder;
    BoneInfo bone_left_wrist;
    BoneInfo bone_right_ankle;
    BoneInfo bone_right_elbow;
    BoneInfo bone_right_hip;
    BoneInfo bone_right_knee;
    BoneInfo bone_right_shoulder;
    BoneInfo bone_right_wrist;
    BoneInfo bone_neck;
    BoneInfo bone_pelvis_presley;

    void init(const char* filename) {

      tinyxml2::XMLDocument xml;
      xml.LoadFile(filename);

      bone_root.name = "root";
      bone_body.name = "body";
      bone_left_ankle.name = "left_ankle";
      bone_left_elbow.name = "left_elbow";
      bone_left_hip.name = "left_hip";
      bone_left_knee.name = "left_knee";
      bone_left_shoulder.name = "left_shoulder";
      bone_left_wrist.name = "left_wrist";
      bone_right_ankle.name = "right_ankle";
      bone_right_elbow.name = "right_elbow";
      bone_right_hip.name = "right_hip";
      bone_right_knee.name = "right_knee";
      bone_right_shoulder.name = "right_shoulder";
      bone_right_wrist.name = "right_wrist";
      bone_neck.name = "neck";
      bone_pelvis_presley.name = "pelvis";

      bone_root.setup(xml);
      bone_body.setup(xml);
      bone_left_ankle.setup(xml);
      bone_left_elbow.setup(xml);
      bone_left_hip.setup(xml);
      bone_left_knee.setup(xml);
      bone_left_shoulder.setup(xml);
      bone_left_wrist.setup(xml);
      bone_right_ankle.setup(xml);
      bone_right_elbow.setup(xml);
      bone_right_hip.setup(xml);
      bone_right_knee.setup(xml);
      bone_right_shoulder.setup(xml);
      bone_right_wrist.setup(xml);
      bone_neck.setup(xml);
      bone_pelvis_presley.setup(xml);
    }

    void update(const float32 delta_time, Robot* robot) {
      robot->root.transform().set_rotation(bone_root.update(delta_time));
      robot->body.transform().set_rotation(bone_body.update(delta_time));
      robot->left_ankle.transform().set_rotation(bone_left_ankle.update(delta_time));
      robot->left_elbow.transform().set_rotation(bone_left_elbow.update(delta_time));
      robot->left_hip.transform().set_rotation(bone_left_hip.update(delta_time));
      robot->left_knee.transform().set_rotation(bone_left_knee.update(delta_time));
      robot->left_shoulder.transform().set_rotation(bone_left_shoulder.update(delta_time));
      robot->left_wrist.transform().set_rotation(bone_left_wrist.update(delta_time));
      robot->right_ankle.transform().set_rotation(bone_right_ankle.update(delta_time));
      robot->right_elbow.transform().set_rotation(bone_right_elbow.update(delta_time));
      robot->right_hip.transform().set_rotation(bone_right_hip.update(delta_time));
      robot->right_knee.transform().set_rotation(bone_right_knee.update(delta_time));
      robot->right_shoulder.transform().set_rotation(bone_right_shoulder.update(delta_time));
      robot->right_wrist.transform().set_rotation(bone_right_wrist.update(delta_time));
      robot->neck.transform().set_rotation(bone_neck.update(delta_time));
      robot->pelvis_presley.transform().set_rotation(bone_pelvis_presley.update(delta_time));
    }

    void play(const bool initial_blending, Robot* robot) {
      if (initial_blending) {
        bone_root.startAnimationWithInitialBlending(robot->root.transform().rotation_float3());
        bone_body.startAnimationWithInitialBlending(robot->body.transform().rotation_float3());
        bone_left_ankle.startAnimationWithInitialBlending(robot->left_ankle.transform().rotation_float3());
        bone_left_elbow.startAnimationWithInitialBlending(robot->left_elbow.transform().rotation_float3());
        bone_left_hip.startAnimationWithInitialBlending(robot->left_hip.transform().rotation_float3());
        bone_left_knee.startAnimationWithInitialBlending(robot->left_knee.transform().rotation_float3());
        bone_left_shoulder.startAnimationWithInitialBlending(robot->left_shoulder.transform().rotation_float3());
        bone_left_wrist.startAnimationWithInitialBlending(robot->left_wrist.transform().rotation_float3());
        bone_right_ankle.startAnimationWithInitialBlending(robot->right_ankle.transform().rotation_float3());
        bone_right_elbow.startAnimationWithInitialBlending(robot->right_elbow.transform().rotation_float3());
        bone_right_hip.startAnimationWithInitialBlending(robot->right_hip.transform().rotation_float3());
        bone_right_knee.startAnimationWithInitialBlending(robot->right_knee.transform().rotation_float3());
        bone_right_shoulder.startAnimationWithInitialBlending(robot->right_shoulder.transform().rotation_float3());
        bone_right_wrist.startAnimationWithInitialBlending(robot->right_wrist.transform().rotation_float3());
        bone_neck.startAnimationWithInitialBlending(robot->neck.transform().rotation_float3());
        bone_pelvis_presley.startAnimationWithInitialBlending(robot->pelvis_presley.transform().rotation_float3());
      }
      else {
        bone_root.startAnimationWithoutBlending();
        bone_body.startAnimationWithoutBlending();
        bone_left_ankle.startAnimationWithoutBlending();
        bone_left_elbow.startAnimationWithoutBlending();
        bone_left_hip.startAnimationWithoutBlending();
        bone_left_knee.startAnimationWithoutBlending();
        bone_left_shoulder.startAnimationWithoutBlending();
        bone_left_wrist.startAnimationWithoutBlending();
        bone_right_ankle.startAnimationWithoutBlending();
        bone_right_elbow.startAnimationWithoutBlending();
        bone_right_hip.startAnimationWithoutBlending();
        bone_right_knee.startAnimationWithoutBlending();
        bone_right_shoulder.startAnimationWithoutBlending();
        bone_right_wrist.startAnimationWithoutBlending();
        bone_neck.startAnimationWithoutBlending();
        bone_pelvis_presley.startAnimationWithoutBlending();
      }
    }

  };

  struct AnimController {

    AnimController() {
      current_animation = nullptr;
      is_running = false;
      robot = nullptr;
    }

    Robot* robot;
    Animation* current_animation;
    Animation idle;
    Animation attack;
    Animation die;

    bool is_running;

    void init(Robot* r) {
      idle.init("../data/animations/RobotIdleAnimDAE.txt");
      attack.init("../data/animations/RobotAttackAnimDAE.txt");
      die.init("../data/animations/RobotDieAnimDAE.txt");
      current_animation = &attack;
      robot = r;
      current_animation->play(false, robot);
    }

    void update(const float delta_time) {
      current_animation->update(delta_time, robot);
    }

    

  };
  
  


  

  //geo.initQuad();
  //geo.initCube();
  //geo.initPyramid(50 ,1, 3);
  //geo.initFromFile("./../data/geometries/plane/plane.x");
  //geo.initExtruded(100, 2.0f, 1.0f, 4.0f);
  //geo.initTerrain("./../data/Heightmap.bmp", { 10, 2, 10 });
  //geo2.initTriangle({ 3.0f, 3.0f });
  //geo_plane.initFromFile("./../data/geometries/plane/plane.x");
  //geo_prop.initFromFile("./../data/geometries/plane/prop.x");
  //geo_gun.initFromFile("./../data/geometries/plane/gun.x");
  //geo_turret.initFromFile("./../data/geometries/plane/turret.x");
  geo_terrain.initTerrain("./../data/textures/Heightmap.bmp", { 100.0f, 7.0f, 100.0f });

  texture.load("./../data/textures/texture.png");
  texture2.load("./../data/textures/turtle.png");
  mat_texture.set_texture(&texture);

  Entity plane_root, plane, prop, turret, gun, cam_node, terrain, root;

  
  terrain.addComponent(ComponentType::Render3D, &matass, &geo_terrain);
  terrain.transform().set_position(-50.0f, -10.0f, -30.0f);
  root.addChild(&terrain);
  

  //plane_root.transform().set_rotation(0.0f, DirectX::XM_PI, 0.0f);
  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());
  auto& cam = Core::instance().cam_;
  cam.is_navigation_enabled_ = true;
  cam.set_position(0.0f, 4.5f, 45.0f);






  Robot robot;
  robot.init(mat);
  root.addChild(&robot.root);

  AnimController anim_controller;
  anim_controller.init(&robot);

  // enter the main loop:

  while (Window::StartFrame() && Window::IsOpened() && 
         !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {
    static uint64 last_time_updated = Time();
    uint64 tick = Time();
    uint64 delta = tick - last_time_updated;

    anim_controller.update((float32)delta * 0.001);
    
    if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Left)) {
      anim_controller.current_animation = &anim_controller.attack;
      anim_controller.current_animation->play(true, anim_controller.robot);
    }

    if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Right)) {
      anim_controller.current_animation = &anim_controller.idle;
      anim_controller.current_animation->play(true, anim_controller.robot);
    }

    cam.render(&root);

    Window::EndFrame();

    uint64 sleepy = 16 - (Time() - tick);
    if (sleepy > 0) {
      Sleep(sleepy);
    }
    last_time_updated = tick;
  }

  Window::Close();

  // Al usar un winmain, nos vemos obligados a usar una aplicacion de tipo win32 que no
  // tiene ventana de consola de comandos, asi que con esta funcion sera como hacer 
  // un printf pero los mensajes apareceran en la ventana OUTPUT del VISUAL PREMOH.
  OutputDebugString(textico);
  return 0;
}


}; /* W3D */
