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

  Geo geo, geo2;
  Geo geo_plane, geo_prop, geo_turret, geo_gun, geo_terrain;
  MaterialDiffuse mat; 
  MaterialNormals mat_normals;
  MaterialTextured mat_texture;
  Texture texture, texture2;
  

  Texture assesment_texture[4];
  assesment_texture[0].load("./../data/textures/materialmap.dds");
  assesment_texture[1].load("./../data/textures/grass.dds");
  assesment_texture[2].load("./../data/textures/moss.dds");
  assesment_texture[3].load("./../data/textures/asphalt.dds");
  MaterialAssesment mat_assesment;
  mat_assesment.texture_materialmap_ = &assesment_texture[0];
  mat_assesment.texture_grass_ = &assesment_texture[1];
  mat_assesment.texture_moss_ = &assesment_texture[2];
  mat_assesment.texture_asphalt_ = &assesment_texture[3];

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
    Entity robot_root;
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

      robot_root.transform().set_position(0.0f, -7.0f, 0.0f);

      root.name_ = "root";
      root.transform().set_position(0.1027778f, 7.5644722f, 0.000000f);
      robot_root.addChild(&root);

      pelvis_presley.addComponent(kComponentType_Render, &mat, &geo_pelvis_presley);
      pelvis_presley.name_ = "pelvis";
      pelvis_presley.transform().set_position(-0.0250011f, 1.5250000f, -0.0000005f);
      root.addChild(&pelvis_presley);

      body.addComponent(kComponentType_Render, &mat, &geo_body);
      body.name_ = "body";
      body.transform().set_position(0.0500099f, 4.3749992f, 0.0000003f);
      pelvis_presley.addChild(&body);

      left_shoulder.addComponent(kComponentType_Render, &mat, &geo_left_shoulder);
      left_shoulder.name_ = "left_shoulder";
      left_shoulder.transform().set_position(4.6000000f, 0.0000000f, -0.0009992f);
      body.addChild(&left_shoulder);

      left_elbow.addComponent(kComponentType_Render, &mat, &geo_left_elbow);
      left_elbow.name_ = "left_elbow";
      left_elbow.transform().set_position(3.4250019f, -0.0499817f, -0.0004262f);
      left_shoulder.addChild(&left_elbow);

      left_wrist.addComponent(kComponentType_Render, &mat, &geo_left_wrist);
      left_wrist.name_ = "left_wrist";
      left_wrist.transform().set_position(5.5250008f, -0.0999710f, 0.0003968f);
      left_elbow.addChild(&left_wrist);

      right_shoulder.addComponent(kComponentType_Render, &mat, &geo_right_shoulder);
      right_shoulder.name_ = "right_shoulder";
      right_shoulder.transform().set_position(-4.4500023f, 0.0500000f, -0.0000021f);
      body.addChild(&right_shoulder);

      right_elbow.addComponent(kComponentType_Render, &mat, &geo_right_elbow);
      right_elbow.name_ = "right_elbow";
      right_elbow.transform().set_position(-3.3999996f, 0.0250229f, -0.0000194f);
      right_shoulder.addChild(&right_elbow);

      right_wrist.addComponent(kComponentType_Render, &mat, &geo_right_wrist);
      right_wrist.name_ = "right_wrist";
      right_wrist.transform().set_position(-6.0000381f, -0.1750183f, 0.0007156f);
      right_elbow.addChild(&right_wrist);

      neck.addComponent(kComponentType_Render, &mat, &geo_neck);
      neck.name_ = "neck";
      neck.transform().set_position(0.0249983f, 3.6625015f, 2.5999998f);
      body.addChild(&neck);

      left_hip.addComponent(kComponentType_Render, &mat, &geo_left_hip);
      left_hip.name_ = "left_hip";
      left_hip.transform().set_position(1.9500000f, -0.7724991f, 0.000000f);
      root.addChild(&left_hip);

      left_knee.addComponent(kComponentType_Render, &mat, &geo_left_knee);
      left_knee.name_ = "left_knee";
      left_knee.transform().set_position(0.0000006f, -2.2200001f, 0.000000f);
      left_hip.addChild(&left_knee);

      left_ankle.addComponent(kComponentType_Render, &mat, &geo_left_ankle);
      left_ankle.name_ = "left_ankle";
      left_ankle.transform().set_position(-0.0800152f, -3.6399994f, -0.0000098f);
      left_knee.addChild(&left_ankle);

      right_hip.addComponent(kComponentType_Render, &mat, &geo_right_hip);
      right_hip.name_ = "right_hip";
      right_hip.transform().set_position(-1.9500000f, -0.7724991f, 0.000000f);
      root.addChild(&right_hip);

      right_knee.addComponent(kComponentType_Render, &mat, &geo_right_knee);
      right_knee.name_ = "right_knee";
      right_knee.transform().set_position(0.0000006f, -2.2000000f, 0.000000f);
      right_hip.addChild(&right_knee);

      right_ankle.addComponent(kComponentType_Render, &mat, &geo_right_ankle);
      right_ankle.name_ = "right_ankle";
      right_ankle.transform().set_position(0.0199911f, -3.6799995f, 0.0000039f);
      right_knee.addChild(&right_ankle);
    }
  };


  struct StepsInfo {

    enum Mode {
      kMode_None = 0,
      kMode_Rotation,
      kMode_Translation,
    };

    StepsInfo() {
      mode = kMode_None;
      step_timers.clear();
      step_values.clear();
      num_steps = 0;
      origin = { 0.0f, 0.0f, 0.0f, 1.0f };
      destiny = { 0.0f, 0.0f, 0.0f, 1.0f };
      alpha = 0.0f;
      timer = 0.0f;
      timer_limit = 0.0f;
      step_destiny = 0;
    }

    Mode mode;
    std::vector<float32> step_timers; // Key frames times.
    std::vector<DirectX::XMFLOAT4> step_values; // quaternion, positions, etc.
    uint32 num_steps;
    DirectX::XMFLOAT4 origin; // To interpole.
    DirectX::XMFLOAT4 destiny; // To interpole.
    float32 alpha; // Interpolation alpha.
    float32 timer; // Chronometer
    float32 timer_limit; // Time to change to the next step or key frame.
    uint32 step_destiny; // Step which will be set as destiny.

    void startWithBlending(DirectX::XMFLOAT4 origin_value, const float blending_duration) {
      step_destiny = 0;
      alpha = 0.0f;
      timer = 0.0f;
      timer_limit = blending_duration;
      origin = origin_value;
      destiny = step_values[step_destiny];
    }

    void startWithoutBlending() {
      step_destiny = 0;
      alpha = 0.0f;
      timer = 0.0f;
      timer_limit = step_timers[step_destiny];
      origin = step_values[0];
      destiny = step_values[step_destiny];
    }

    void startNewStep() {
      step_destiny += 1;
      if (step_destiny == num_steps) {
        step_destiny = 0;
      }
      timer = 0.0f;
      timer_limit = step_timers[step_destiny]; // Ya que son todos iguales x y z
      origin = destiny;
      destiny = step_values[step_destiny];
    }

    // Returns the rotation or traslation.
    DirectX::XMVECTOR update(const float32 delta_time) {
      timer += delta_time;

      // Relleno el alpha.
      alpha = timer / timer_limit; // values between 0 and 1 to interpole
      if (alpha > 1.0f) {
        alpha = 0.0f;
      }
      // Check if we need to change to the next step.
      if (timer > timer_limit) {
        startNewStep();
      }

      // retorno la rotacion que corresponde.
      switch (mode) {
        case StepsInfo::kMode_Rotation: { return Math::QuaternionLerpVector(origin, destiny, alpha); } break;
        case StepsInfo::kMode_Translation: { return Math::LerpVector(origin, destiny, alpha); } break;
      }

      MessageBox(NULL, "Error StepsInfo Mode not set", "ERROR", MB_OK);
      return DirectX::XMVECTOR();
    }



  };

  struct BoneInfo {

    BoneInfo() {
      translation.mode = StepsInfo::Mode::kMode_Translation;
      rotation.mode = StepsInfo::Mode::kMode_Rotation;
    }

    StepsInfo translation;
    StepsInfo rotation;

    std::string name;

    void startAnimationWithInitialBlending(DirectX::XMFLOAT4 rot_origin,
                                           DirectX::XMFLOAT4 traslation_origin,
                                           const float32 blending_duration) {

      translation.startWithBlending(traslation_origin, blending_duration);
      rotation.startWithBlending(rot_origin, blending_duration);
    }

    void startAnimationWithoutBlending() {
      translation.startWithoutBlending();
      rotation.startWithoutBlending();
    }

    enum Axis {
      kAxis_X = 0,
      kAxis_Y = 1,
      kAxis_Z = 2,
    };

    void setupAxisRotation(Axis axis, tinyxml2::XMLNode* root) {

      std::string rot_text;
      tinyxml2::XMLElement* time_elem = nullptr;
      tinyxml2::XMLElement* value_elem = nullptr;
      std::vector<float64> temp;

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
          value_elem = i->FirstChildElement()->NextSiblingElement()->FirstChildElement("float_array");
          break;
        }
      }

      if (!time_elem || !value_elem) {
        MessageBox(NULL, "Error loading animation from file", "ERROR", MB_OK);
      }

      // TIMERS
      rotation.num_steps = time_elem->IntAttribute("count");
      rotation.step_timers.resize(rotation.num_steps);
      std::istringstream time_string(time_elem->GetText());
      std::copy(std::istream_iterator<float64>(time_string),
                std::istream_iterator<float64>(),
                std::back_inserter(temp));

      for (int i = 0; i < rotation.num_steps; i++) {
        rotation.step_timers[i] = temp[i]; 
      }

      temp.clear();
      // VALUES -> angles
      rotation.num_steps = value_elem->IntAttribute("count");
      rotation.step_values.resize(rotation.num_steps);
      std::istringstream rot_string(value_elem->GetText());
      std::copy(std::istream_iterator<float64>(rot_string),
                std::istream_iterator<float64>(),
                std::back_inserter(temp));

      for (int i = 0; i < rotation.num_steps; i++) {
        switch (axis) {
          case BoneInfo::kAxis_X: { rotation.step_values[i].x = DirectX::XMConvertToRadians(temp[i]); } break;
          case BoneInfo::kAxis_Y: { rotation.step_values[i].y = DirectX::XMConvertToRadians(temp[i]); } break;
          case BoneInfo::kAxis_Z: { rotation.step_values[i].z = DirectX::XMConvertToRadians(temp[i]); } break;
        }
      }
    }

    void setupTranslation(tinyxml2::XMLNode* root) {

      std::string tr_text = name + ".translate";
      tinyxml2::XMLElement* time_elem = nullptr;
      tinyxml2::XMLElement* value_elem = nullptr;
      std::vector<float64> temp;

      // Searching for the correct child.
      for (auto* i = root->FirstChildElement(); i != nullptr; i = i->NextSiblingElement()) {
        std::string id = i->Attribute("id");
        if (id == tr_text) {
          time_elem = i->FirstChildElement()->FirstChildElement("float_array");
          value_elem = i->FirstChildElement()->NextSiblingElement()->FirstChildElement("float_array");
          break;
        }
      }

      if (!time_elem || !value_elem) {
        MessageBox(NULL, "Error loading animation from file", "ERROR", MB_OK);
      }

      // TIMERS
      translation.num_steps = time_elem->IntAttribute("count");
      translation.step_timers.resize(translation.num_steps);
      std::istringstream time_string(time_elem->GetText());
      std::copy(std::istream_iterator<float64>(time_string),
                std::istream_iterator<float64>(),
                std::back_inserter(temp));

      for (int i = 0; i < translation.num_steps; i++) {
        translation.step_timers[i] = temp[i];
      }

      temp.clear();
      // VALUES -> positions
      translation.step_values.resize(translation.num_steps);
      std::istringstream tr_string(value_elem->GetText());
      std::copy(std::istream_iterator<float64>(tr_string),
        std::istream_iterator<float64>(),
        std::back_inserter(temp));

      uint32 num_positions = temp.size() / 3;
      uint32 index = 0;
      for (int i = 0; i < num_positions; i++) {
        translation.step_values[i].x = temp[index] * 0.1;
        index++;
        translation.step_values[i].y = temp[index] * 0.1;
        index++;
        translation.step_values[i].z = temp[index] * 0.1;
        index++;
        translation.step_values[i].w = 1.0f;
      }
    }

    void setup(tinyxml2::XMLDocument& doc) {
      // Get the main node.
      tinyxml2::XMLNode* root = doc.FirstChild();

      setupAxisRotation(kAxis_X, root);
      setupAxisRotation(kAxis_Y, root);
      setupAxisRotation(kAxis_Z, root);
      convertEulerAnglesIntoQuaternion();
      setupTranslation(root);
    }

    void convertEulerAnglesIntoQuaternion() {
      for (uint32 i = 0; i < rotation.num_steps; ++i) {
        DirectX::XMFLOAT3 rot = { rotation.step_values[i].x, 
                                  rotation.step_values[i].y, 
                                  rotation.step_values[i].z };

        rotation.step_values[i] = Math::ConvertEulerToQuaternionFloat4(rot);
      }
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
    float32 speed;

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

      speed = 1.0f;
    }

    void update(const float32 delta_time, Robot* robot) {
      float32 delta_scaled = delta_time * speed;
      // POSITIONS 
      robot->root.transform().set_position(bone_root.translation.update(delta_scaled));
      robot->pelvis_presley.transform().set_position(bone_pelvis_presley.translation.update(delta_scaled));
      robot->body.transform().set_position(bone_body.translation.update(delta_scaled));
      robot->right_shoulder.transform().set_position(bone_right_shoulder.translation.update(delta_scaled));
      robot->right_elbow.transform().set_position(bone_right_elbow.translation.update(delta_scaled));
      robot->right_wrist.transform().set_position(bone_right_wrist.translation.update(delta_scaled));
      robot->left_shoulder.transform().set_position(bone_left_shoulder.translation.update(delta_scaled));
      robot->left_elbow.transform().set_position(bone_left_elbow.translation.update(delta_scaled));
      robot->left_wrist.transform().set_position(bone_left_wrist.translation.update(delta_scaled));
      robot->neck.transform().set_position(bone_neck.translation.update(delta_scaled));
      robot->left_hip.transform().set_position(bone_left_hip.translation.update(delta_scaled));
      robot->left_knee.transform().set_position(bone_left_knee.translation.update(delta_scaled));
      robot->left_ankle.transform().set_position(bone_left_ankle.translation.update(delta_scaled));
      robot->right_ankle.transform().set_position(bone_right_ankle.translation.update(delta_scaled));
      robot->right_hip.transform().set_position(bone_right_hip.translation.update(delta_scaled));
      robot->right_knee.transform().set_position(bone_right_knee.translation.update(delta_scaled));

      // ROTATIONS
      /*
      */
      robot->root.transform().set_quaternion_rotation(bone_root.rotation.update(delta_scaled));
      robot->pelvis_presley.transform().set_quaternion_rotation(bone_pelvis_presley.rotation.update(delta_scaled));
      robot->body.transform().set_quaternion_rotation(bone_body.rotation.update(delta_scaled));
      robot->right_shoulder.transform().set_quaternion_rotation(bone_right_shoulder.rotation.update(delta_scaled));
      robot->right_elbow.transform().set_quaternion_rotation(bone_right_elbow.rotation.update(delta_scaled));
      robot->right_wrist.transform().set_quaternion_rotation(bone_right_wrist.rotation.update(delta_scaled));
      robot->left_shoulder.transform().set_quaternion_rotation(bone_left_shoulder.rotation.update(delta_scaled));
      robot->left_elbow.transform().set_quaternion_rotation(bone_left_elbow.rotation.update(delta_scaled));
      robot->left_wrist.transform().set_quaternion_rotation(bone_left_wrist.rotation.update(delta_scaled));
      robot->neck.transform().set_quaternion_rotation(bone_neck.rotation.update(delta_scaled));
      robot->left_hip.transform().set_quaternion_rotation(bone_left_hip.rotation.update(delta_scaled));
      robot->left_knee.transform().set_quaternion_rotation(bone_left_knee.rotation.update(delta_scaled));
      robot->left_ankle.transform().set_quaternion_rotation(bone_left_ankle.rotation.update(delta_scaled));
      robot->right_ankle.transform().set_quaternion_rotation(bone_right_ankle.rotation.update(delta_scaled));
      robot->right_hip.transform().set_quaternion_rotation(bone_right_hip.rotation.update(delta_scaled));
      robot->right_knee.transform().set_quaternion_rotation(bone_right_knee.rotation.update(delta_scaled));
    }

    void play(const bool initial_blending, Robot* robot, const float32 blending_duration = 1.0f) {
      if (initial_blending) {
        bone_root.startAnimationWithInitialBlending(robot->root.transform().quaternion_rotation_float4(), robot->root.transform().position_float4(), blending_duration);
        bone_body.startAnimationWithInitialBlending(robot->body.transform().quaternion_rotation_float4(), robot->body.transform().position_float4(), blending_duration);
        bone_left_ankle.startAnimationWithInitialBlending(robot->left_ankle.transform().quaternion_rotation_float4(), robot->left_ankle.transform().position_float4(), blending_duration);
        bone_left_elbow.startAnimationWithInitialBlending(robot->left_elbow.transform().quaternion_rotation_float4(), robot->left_elbow.transform().position_float4(), blending_duration);
        bone_left_hip.startAnimationWithInitialBlending(robot->left_hip.transform().quaternion_rotation_float4(), robot->left_hip.transform().position_float4(), blending_duration);
        bone_left_knee.startAnimationWithInitialBlending(robot->left_knee.transform().quaternion_rotation_float4(), robot->left_knee.transform().position_float4(), blending_duration);
        bone_left_shoulder.startAnimationWithInitialBlending(robot->left_shoulder.transform().quaternion_rotation_float4(), robot->left_shoulder.transform().position_float4(), blending_duration);
        bone_left_wrist.startAnimationWithInitialBlending(robot->left_wrist.transform().quaternion_rotation_float4(), robot->left_wrist.transform().position_float4(), blending_duration);
        bone_right_ankle.startAnimationWithInitialBlending(robot->right_ankle.transform().quaternion_rotation_float4(), robot->right_ankle.transform().position_float4(), blending_duration);
        bone_right_elbow.startAnimationWithInitialBlending(robot->right_elbow.transform().quaternion_rotation_float4(), robot->right_elbow.transform().position_float4(), blending_duration);
        bone_right_hip.startAnimationWithInitialBlending(robot->right_hip.transform().quaternion_rotation_float4(), robot->right_hip.transform().position_float4(), blending_duration);
        bone_right_knee.startAnimationWithInitialBlending(robot->right_knee.transform().quaternion_rotation_float4(), robot->right_knee.transform().position_float4(), blending_duration);
        bone_right_shoulder.startAnimationWithInitialBlending(robot->right_shoulder.transform().quaternion_rotation_float4(), robot->right_shoulder.transform().position_float4(), blending_duration);
        bone_right_wrist.startAnimationWithInitialBlending(robot->right_wrist.transform().quaternion_rotation_float4(), robot->right_wrist.transform().position_float4(), blending_duration);
        bone_neck.startAnimationWithInitialBlending(robot->neck.transform().quaternion_rotation_float4(), robot->neck.transform().position_float4(), blending_duration);
        bone_pelvis_presley.startAnimationWithInitialBlending(robot->pelvis_presley.transform().quaternion_rotation_float4(), robot->pelvis_presley.transform().position_float4(), blending_duration);
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
      robot = r;
    }

    void update(const float delta_time) {
      if (current_animation) {
        current_animation->update(delta_time, robot);
      }
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

  
  terrain.addComponent(kComponentType_Render, &mat_assesment, &geo_terrain);
  terrain.transform().set_position(-50.0f, -10.0f, -30.0f);
  root.addChild(&terrain);
  

  //plane_root.transform().set_rotation(0.0f, DirectX::XM_PI, 0.0f);
  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());
  auto& cam = Core::instance().cam_;
  cam.is_navigation_enabled_ = true;
  cam.set_position(0.0f, 4.5f, 45.0f);



  float debug_speed = 1.0f;

  Robot robot;
  robot.init(mat);
  root.addChild(&robot.robot_root);

  AnimController anim_controller;
  anim_controller.init(&robot);

  // enter the main loop:

  while (Window::StartFrame() && Window::IsOpened() &&
    !Input::IsKeyboardButtonDown(Input::kKeyboardButton_Escape)) {
    static uint64 last_time_updated = Time();
    uint64 tick = Time();
    uint64 delta = tick - last_time_updated;

    char delta_[128];
    sprintf(delta_, "%f\n", (float32)delta);
    if ((float32)delta > 10) {
      OutputDebugString(delta_);
    }

    if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Left)) {
      anim_controller.current_animation = &anim_controller.attack;
      anim_controller.current_animation->play(true, anim_controller.robot, 0.5f);
    }

    if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Right)) {
      anim_controller.current_animation = &anim_controller.idle;
      anim_controller.current_animation->play(true, anim_controller.robot, 0.5f);
    }

    if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Up)) {
      anim_controller.current_animation = &anim_controller.die;
      anim_controller.current_animation->play(true, anim_controller.robot, 0.5f);
    }

    anim_controller.update((float32)delta * 0.001);
    //anim_controller.update(0.001);
    cam.render(&root);

    ImGui::SliderFloat("Animation Speed", &debug_speed, 0.0f, 5.0f);
    anim_controller.attack.speed = debug_speed;
    anim_controller.die.speed = debug_speed;
    anim_controller.idle.speed = debug_speed;
    
    ImGuiGenerateRootTreeStats(&robot.root);

    ImGui::Text("Wolfy3D speed: %.3f ms/frame (%.1f FPS)",
      1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    Window::EndFrame();

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
