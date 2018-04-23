/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "robot.h"
#include "animation.h"
#include "imgui/imgui.h"

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Animation::Animation() {
  robot_root.name = "root";
  body.name = "body";
  left_ankle.name = "left_ankle";
  left_elbow.name = "left_elbow";
  left_hip.name = "left_hip";
  left_knee.name = "left_knee";
  left_shoulder.name = "left_shoulder";
  left_wrist.name = "left_wrist";
  right_ankle.name = "right_ankle";
  right_elbow.name = "right_elbow";
  right_hip.name = "right_hip";
  right_knee.name = "right_knee";
  right_shoulder.name = "right_shoulder";
  right_wrist.name = "right_wrist";
  neck.name = "neck";
  pelvis_presley.name = "pelvis";
  robot = nullptr;
}

Animation::~Animation() {}

Animation::Animation(const Animation& copy) {
  robot_root = copy.robot_root;
  body = copy.body;
  left_ankle = copy.left_ankle;
  left_elbow = copy.left_elbow;
  left_hip = copy.left_hip;
  left_knee = copy.left_knee;
  left_shoulder = copy.left_shoulder;
  left_wrist = copy.left_wrist;
  right_ankle = copy.right_ankle;
  right_elbow = copy.right_elbow;
  right_hip = copy.right_hip;
  right_knee = copy.right_knee;
  right_shoulder = copy.right_shoulder;
  right_wrist = copy.right_wrist;
  neck = copy.neck;
  pelvis_presley = copy.pelvis_presley;
  speed = copy.speed;
  robot = copy.robot;
}

Animation& Animation::operator=(const Animation& copy) {
  robot_root = copy.robot_root;
  body = copy.body;
  left_ankle = copy.left_ankle;
  left_elbow = copy.left_elbow;
  left_hip = copy.left_hip;
  left_knee = copy.left_knee;
  left_shoulder = copy.left_shoulder;
  left_wrist = copy.left_wrist;
  right_ankle = copy.right_ankle;
  right_elbow = copy.right_elbow;
  right_hip = copy.right_hip;
  right_knee = copy.right_knee;
  right_shoulder = copy.right_shoulder;
  right_wrist = copy.right_wrist;
  neck = copy.neck;
  pelvis_presley = copy.pelvis_presley;
  speed = copy.speed;
  robot = copy.robot;
  return *this;
}
/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Animation::initFromFile(const char* filename) {
  tinyxml2::XMLDocument xml;
  xml.LoadFile(filename);

  robot_root.setup(xml);
  body.setup(xml);
  left_ankle.setup(xml);
  left_elbow.setup(xml);
  left_hip.setup(xml);
  left_knee.setup(xml);
  left_shoulder.setup(xml);
  left_wrist.setup(xml);
  right_ankle.setup(xml);
  right_elbow.setup(xml);
  right_hip.setup(xml);
  right_knee.setup(xml);
  right_shoulder.setup(xml);
  right_wrist.setup(xml);
  neck.setup(xml);
  pelvis_presley.setup(xml);

  speed = 1.0f;
}

void Animation::update(const float32& delta_time) {
  float32 delta_scaled = delta_time * speed;
  updateBonesPositions(delta_scaled);
  updateBonesRotations(delta_scaled);
}

void Animation::start(const bool apply_blending, const float32 blending_duration) {
  robot_root.start(apply_blending, robot->robot_root_.transform().quaternion_rotation_float4(), robot->robot_root_.transform().position_float4(), blending_duration);
  body.start(apply_blending, robot->body_.transform().quaternion_rotation_float4(), robot->body_.transform().position_float4(), blending_duration);
  left_ankle.start(apply_blending, robot->left_ankle_.transform().quaternion_rotation_float4(), robot->left_ankle_.transform().position_float4(), blending_duration);
  left_elbow.start(apply_blending, robot->left_elbow_.transform().quaternion_rotation_float4(), robot->left_elbow_.transform().position_float4(), blending_duration);
  left_hip.start(apply_blending, robot->left_hip_.transform().quaternion_rotation_float4(), robot->left_hip_.transform().position_float4(), blending_duration);
  left_knee.start(apply_blending, robot->left_knee_.transform().quaternion_rotation_float4(), robot->left_knee_.transform().position_float4(), blending_duration);
  left_shoulder.start(apply_blending, robot->left_shoulder_.transform().quaternion_rotation_float4(), robot->left_shoulder_.transform().position_float4(), blending_duration);
  left_wrist.start(apply_blending, robot->left_wrist_.transform().quaternion_rotation_float4(), robot->left_wrist_.transform().position_float4(), blending_duration);
  right_ankle.start(apply_blending, robot->right_ankle_.transform().quaternion_rotation_float4(), robot->right_ankle_.transform().position_float4(), blending_duration);
  right_elbow.start(apply_blending, robot->right_elbow_.transform().quaternion_rotation_float4(), robot->right_elbow_.transform().position_float4(), blending_duration);
  right_hip.start(apply_blending, robot->right_hip_.transform().quaternion_rotation_float4(), robot->right_hip_.transform().position_float4(), blending_duration);
  right_knee.start(apply_blending, robot->right_knee_.transform().quaternion_rotation_float4(), robot->right_knee_.transform().position_float4(), blending_duration);
  right_shoulder.start(apply_blending, robot->right_shoulder_.transform().quaternion_rotation_float4(), robot->right_shoulder_.transform().position_float4(), blending_duration);
  right_wrist.start(apply_blending, robot->right_wrist_.transform().quaternion_rotation_float4(), robot->right_wrist_.transform().position_float4(), blending_duration);
  neck.start(apply_blending, robot->neck_.transform().quaternion_rotation_float4(), robot->neck_.transform().position_float4(), blending_duration);
  pelvis_presley.start(apply_blending, robot->pelvis_presley_.transform().quaternion_rotation_float4(), robot->pelvis_presley_.transform().position_float4(), blending_duration);
}




/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/


void Animation::updateBonesPositions(const float32& delta_time) {
  robot->robot_root_.transform().set_position(robot_root.translation.update(delta_time));
  robot->pelvis_presley_.transform().set_position(pelvis_presley.translation.update(delta_time));
  robot->body_.transform().set_position(body.translation.update(delta_time));
  robot->right_shoulder_.transform().set_position(right_shoulder.translation.update(delta_time));
  robot->right_elbow_.transform().set_position(right_elbow.translation.update(delta_time));
  robot->right_wrist_.transform().set_position(right_wrist.translation.update(delta_time));
  robot->left_shoulder_.transform().set_position(left_shoulder.translation.update(delta_time));
  robot->left_elbow_.transform().set_position(left_elbow.translation.update(delta_time));
  robot->left_wrist_.transform().set_position(left_wrist.translation.update(delta_time));
  robot->neck_.transform().set_position(neck.translation.update(delta_time));
  robot->left_hip_.transform().set_position(left_hip.translation.update(delta_time));
  robot->left_knee_.transform().set_position(left_knee.translation.update(delta_time));
  robot->left_ankle_.transform().set_position(left_ankle.translation.update(delta_time));
  robot->right_ankle_.transform().set_position(right_ankle.translation.update(delta_time));
  robot->right_hip_.transform().set_position(right_hip.translation.update(delta_time));
  robot->right_knee_.transform().set_position(right_knee.translation.update(delta_time));
}

void Animation::updateBonesRotations(const float32& delta_time) {
  robot->robot_root_.transform().set_quaternion_rotation(robot_root.rotation.update(delta_time));
  robot->pelvis_presley_.transform().set_quaternion_rotation(pelvis_presley.rotation.update(delta_time));
  robot->body_.transform().set_quaternion_rotation(body.rotation.update(delta_time));
  robot->right_shoulder_.transform().set_quaternion_rotation(right_shoulder.rotation.update(delta_time));
  robot->right_elbow_.transform().set_quaternion_rotation(right_elbow.rotation.update(delta_time));
  robot->right_wrist_.transform().set_quaternion_rotation(right_wrist.rotation.update(delta_time));
  robot->left_shoulder_.transform().set_quaternion_rotation(left_shoulder.rotation.update(delta_time));
  robot->left_elbow_.transform().set_quaternion_rotation(left_elbow.rotation.update(delta_time));
  robot->left_wrist_.transform().set_quaternion_rotation(left_wrist.rotation.update(delta_time));
  robot->neck_.transform().set_quaternion_rotation(neck.rotation.update(delta_time));
  robot->left_hip_.transform().set_quaternion_rotation(left_hip.rotation.update(delta_time));
  robot->left_knee_.transform().set_quaternion_rotation(left_knee.rotation.update(delta_time));
  robot->left_ankle_.transform().set_quaternion_rotation(left_ankle.rotation.update(delta_time));
  robot->right_ankle_.transform().set_quaternion_rotation(right_ankle.rotation.update(delta_time));
  robot->right_hip_.transform().set_quaternion_rotation(right_hip.rotation.update(delta_time));
  robot->right_knee_.transform().set_quaternion_rotation(right_knee.rotation.update(delta_time));
}




}; /* W3D */