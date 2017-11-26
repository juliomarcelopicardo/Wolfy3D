/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "bone.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>
#include <sstream>

namespace W3D {



/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Bone::Bone() {}

Bone::~Bone() {}

Bone::Bone(const Bone& copy) {
  name = copy.name;
  translation = copy.translation;
  rotation = copy.rotation;
}

Bone& Bone::operator=(const Bone& copy) {
  name = copy.name;
  translation = copy.translation;
  rotation = copy.rotation;
  return *this;
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

void Bone::setup(tinyxml2::XMLDocument& doc) {
  // Get the main node.
  tinyxml2::XMLNode* root = doc.FirstChild();

  setupAxisRotation(kAxis_X, root);
  setupAxisRotation(kAxis_Y, root);
  setupAxisRotation(kAxis_Z, root);
  convertEulerAnglesIntoQuaternion();
  setupTranslation(root);
}

void Bone::start(const bool apply_blending, 
                 const DirectX::XMFLOAT4 rot_origin,
                 const DirectX::XMFLOAT4 traslation_origin,
                 const float32 blending_duration) {

  translation.start(apply_blending, traslation_origin, blending_duration);
  rotation.start(apply_blending, rot_origin, blending_duration);
}




/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void Bone::convertEulerAnglesIntoQuaternion() {
  for (uint32 i = 0; i < rotation.num_steps; ++i) {
    DirectX::XMFLOAT3 rot = { rotation.step_values[i].x,
      rotation.step_values[i].y,
      rotation.step_values[i].z };

    rotation.step_values[i] = Math::ConvertEulerToQuaternionFloat4(rot);
  }
}

void Bone::setupAxisRotation(Axis axis, tinyxml2::XMLNode* root) {

  std::string rot_text;
  tinyxml2::XMLElement* time_elem = nullptr;
  tinyxml2::XMLElement* value_elem = nullptr;
  std::vector<float64> temp;

  switch (axis) {
  case Bone::kAxis_X: { rot_text = name + ".rotateX"; }break;
  case Bone::kAxis_Y: { rot_text = name + ".rotateY"; }break;
  case Bone::kAxis_Z: { rot_text = name + ".rotateZ"; }break;
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
    case Bone::kAxis_X: { rotation.step_values[i].x = DirectX::XMConvertToRadians(temp[i]); } break;
    case Bone::kAxis_Y: { rotation.step_values[i].y = DirectX::XMConvertToRadians(temp[i]); } break;
    case Bone::kAxis_Z: { rotation.step_values[i].z = DirectX::XMConvertToRadians(temp[i]); } break;
    }
  }
}

void Bone::setupTranslation(tinyxml2::XMLNode* root) {

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



}; /* W3D */