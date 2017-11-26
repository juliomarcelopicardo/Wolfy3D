/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "robot.h"
#include "imgui/imgui.h"

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Robot::Robot() {}

Robot::~Robot() {}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Robot::init() {
  initNames();
  initHierarchy();
  initTransforms();
  initGeometries();
  initMaterials();
  initRenderComponents();
  initAnimations();
}

void Robot::update(const float32& delta_time) {
  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Left)) {
    anim_controller_.current_animation = &anim_controller_.attack;
    anim_controller_.current_animation->start(true, 0.5f);
  }

  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Right)) {
    anim_controller_.current_animation = &anim_controller_.idle;
    anim_controller_.current_animation->start(true, 0.5f);
  }

  if (Input::IsKeyboardButtonDown(Input::kKeyboardButton_Up)) {
    anim_controller_.current_animation = &anim_controller_.die;
    anim_controller_.current_animation->start(true, 0.5f);
  }

  anim_controller_.update(delta_time * 0.001f);
  updateImGui();
}


/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

void Robot::set_material_color(const float32 r, const float32 g, const float32 b) {
  material_.set_color(r, g, b);
}

void Robot::set_animations_speed(const float32 speed) {
  anim_controller_.attack.speed = speed;
  anim_controller_.idle.speed = speed;
  anim_controller_.die.speed = speed;
}



/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Robot::initGeometries() {
  geo_body_.initFromFile("./../data/geometries/robot/body.x");
  geo_left_ankle_.initFromFile("./../data/geometries/robot/left_ankle.x");
  geo_left_elbow_.initFromFile("./../data/geometries/robot/left_elbow.x");
  geo_left_hip_.initFromFile("./../data/geometries/robot/left_hip.x");
  geo_left_knee_.initFromFile("./../data/geometries/robot/left_knee.x");
  geo_left_shoulder_.initFromFile("./../data/geometries/robot/left_shoulder.x");
  geo_left_wrist_.initFromFile("./../data/geometries/robot/left_wrist.x");
  geo_right_ankle_.initFromFile("./../data/geometries/robot/right_ankle.x");
  geo_right_elbow_.initFromFile("./../data/geometries/robot/right_elbow.x");
  geo_right_hip_.initFromFile("./../data/geometries/robot/right_hip.x");
  geo_right_knee_.initFromFile("./../data/geometries/robot/right_knee.x");
  geo_right_shoulder_.initFromFile("./../data/geometries/robot/right_shoulder.x");
  geo_right_wrist_.initFromFile("./../data/geometries/robot/right_wrist.x");
  geo_neck_.initFromFile("./../data/geometries/robot/neck.x");
  geo_pelvis_presley_.initFromFile("./../data/geometries/robot/pelvis.x");
}

void Robot::initHierarchy() {
  root_.addChild(&robot_root_);
  root_.addChild(&camera_node_);
  robot_root_.addChild(&pelvis_presley_);
  pelvis_presley_.addChild(&body_);
  body_.addChild(&left_shoulder_);
  left_shoulder_.addChild(&left_elbow_);
  left_elbow_.addChild(&left_wrist_);
  body_.addChild(&right_shoulder_);
  right_shoulder_.addChild(&right_elbow_);
  right_elbow_.addChild(&right_wrist_);
  body_.addChild(&neck_);
  robot_root_.addChild(&left_hip_);
  left_hip_.addChild(&left_knee_);
  left_knee_.addChild(&left_ankle_);
  robot_root_.addChild(&right_hip_);
  right_hip_.addChild(&right_knee_);
  right_knee_.addChild(&right_ankle_);
}

void Robot::initNames() {
  root_.name_ = "Red Robot";
  camera_node_.name_ = "Camera Node";
  robot_root_.name_ = "Robot root";
  pelvis_presley_.name_ = "Pelvis";
  body_.name_ = "Body";
  left_shoulder_.name_ = "Left shoulder";
  left_elbow_.name_ = "Left elbow";
  left_wrist_.name_ = "Left wrist";
  right_shoulder_.name_ = "Right shoulder";
  right_elbow_.name_ = "Right elbow";
  right_wrist_.name_ = "Right wrist";
  neck_.name_ = "Neck";
  left_hip_.name_ = "Left hip";
  left_knee_.name_ = "Left knee";
  left_ankle_.name_ = "Left ankle";
  right_hip_.name_ = "Right hip";
  right_knee_.name_ = "Right knee";
  right_ankle_.name_ = "Right ankle";
}

void Robot::initTransforms() {
  root_.transform().set_scale(0.5f);
  camera_node_.transform().set_position(0.0f, 5.0f, 30.0f);
  robot_root_.transform().set_position(0.1027778f, 7.5644722f, 0.000000f);
  pelvis_presley_.transform().set_position(-0.0250011f, 1.5250000f, -0.0000005f);
  body_.transform().set_position(0.0500099f, 4.3749992f, 0.0000003f);
  left_shoulder_.transform().set_position(4.6000000f, 0.0000000f, -0.0009992f);
  left_elbow_.transform().set_position(3.4250019f, -0.0499817f, -0.0004262f);
  left_wrist_.transform().set_position(5.5250008f, -0.0999710f, 0.0003968f);
  right_shoulder_.transform().set_position(-4.4500023f, 0.0500000f, -0.0000021f);
  right_elbow_.transform().set_position(-3.3999996f, 0.0250229f, -0.0000194f);
  right_wrist_.transform().set_position(-6.0000381f, -0.1750183f, 0.0007156f);
  neck_.transform().set_position(0.0249983f, 3.6625015f, 2.5999998f);
  left_hip_.transform().set_position(1.9500000f, -0.7724991f, 0.000000f);
  left_knee_.transform().set_position(0.0000006f, -2.2200001f, 0.000000f);
  left_ankle_.transform().set_position(-0.0800152f, -3.6399994f, -0.0000098f);
  right_hip_.transform().set_position(-1.9500000f, -0.7724991f, 0.000000f);
  right_knee_.transform().set_position(0.0000006f, -2.2000000f, 0.000000f);
  right_ankle_.transform().set_position(0.0199911f, -3.6799995f, 0.0000039f);
}

void Robot::initRenderComponents() {
  pelvis_presley_.addComponent(kComponentType_Render, &material_, &geo_pelvis_presley_);
  body_.addComponent(kComponentType_Render, &material_, &geo_body_);
  left_shoulder_.addComponent(kComponentType_Render, &material_, &geo_left_shoulder_);
  left_elbow_.addComponent(kComponentType_Render, &material_, &geo_left_elbow_);
  left_wrist_.addComponent(kComponentType_Render, &material_, &geo_left_wrist_);
  right_shoulder_.addComponent(kComponentType_Render, &material_, &geo_right_shoulder_);
  right_elbow_.addComponent(kComponentType_Render, &material_, &geo_right_elbow_);
  right_wrist_.addComponent(kComponentType_Render, &material_, &geo_right_wrist_);
  neck_.addComponent(kComponentType_Render, &material_, &geo_neck_);
  left_hip_.addComponent(kComponentType_Render, &material_, &geo_left_hip_);
  left_knee_.addComponent(kComponentType_Render, &material_, &geo_left_knee_);
  left_ankle_.addComponent(kComponentType_Render, &material_, &geo_left_ankle_);
  right_hip_.addComponent(kComponentType_Render, &material_, &geo_right_hip_);
  right_knee_.addComponent(kComponentType_Render, &material_, &geo_right_knee_);
  right_ankle_.addComponent(kComponentType_Render, &material_, &geo_right_ankle_);
}

void Robot::initAnimations() {
  anim_controller_.robot = this;
  anim_controller_.init();
}


void Robot::initMaterials() {
  material_.set_color(0.6f, 0.6f, 0.6f, 1.0f);
}


void Robot::updateImGui() {
  ImGui::PushID(this);
  generateRootTreeStatsImGui(&root_);
  ImGui::PopID();
}

void Robot::generateNodeStatsImGui(Entity* entity) {
  DirectX::XMFLOAT3 temp;

  ImGui::PushID(entity);

  // Position
  temp = entity->transform().position_float3();
  ImGui::DragFloat3(" Position", &temp.x);
  entity->transform().set_position(temp);

  // rotation
  temp = entity->transform().euler_rotation_float3();
  ImGui::DragFloat3(" Rotation", &temp.x, 0.05f);
  entity->transform().set_euler_rotation(temp);


  ImGui::PopID();
}

void Robot::generateRootTreeStatsImGui(Entity* root_entity) {

  if (ImGui::TreeNode(root_entity->name_.c_str())) {
    generateNodeStatsImGui(root_entity);
    uint32 size = root_entity->children_.size();
    for (uint32 i = 0; i < size; i++) {
      generateRootTreeStatsImGui(root_entity->children_[i]);
    }
    ImGui::TreePop();
  }

}

}; /* W3D */