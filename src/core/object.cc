/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/object.h"
#include "core/core.h"
#include "core/window.h"
#include "core/geometry.h"


namespace SLX {

  
  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  Object::Object() {
    initialized_ = false;
    render3D_ = nullptr;
    transform_ = nullptr;
    parent_ = nullptr;
  }

  Object::~Object() {
    if (transform_) {
      delete transform_;
    }

    if (render3D_) {
      delete render3D_;
    }
    children_.clear();
    parent_ = nullptr;
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  void Object::init() {
    if (!initialized_) {
      if (!transform_) {
        transform_ = new TransformComponent;
        transform_->init();
        transform_->set_owner(this);
        initialized_ = true;
      }
    }
  }

  void Object::update() {

    if (!initialized_) {
      init();
    }

    if (transform_) {
      transform_->update();
    }

    if (render3D_) {
      render3D_->update();
    }
  }

  void Object::addComponent(ComponentType component) {
    switch (component) {
      case SLX::ComponentType::Render3D: {
        if (!render3D_) {
          render3D_ = new Render3DComponent;
          render3D_->init();
          render3D_->set_owner(this);
        }
        break;
      }
    }
  }

  void Object::addChild(Object* obj) {
    uint32 num_children = children_.size();
    for (uint32 i = 0; i < num_children; ++i) {
      if (children_[i] == obj) {
        OutputDebugString(" ERROR: children already attached to this object.\n");
        return;
      }
    }
    children_.push_back(obj);
    DirectX::XMStoreFloat4x4(&obj->transform_->parent_model_matrix_, transform_->global_model_matrix());
    obj->parent_ = this;
    obj->updateLocalModelAndChildrenMatrices();
  }

  void Object::updateLocalModelAndChildrenMatrices() {
    transform_->calculateLocalModelMatrix();
    uint32 num_children = children_.size();
    for (uint32 i = 0; i < num_children; i++) {
      DirectX::XMStoreFloat4x4(&children_[i]->transform_->parent_model_matrix_, transform_->global_model_matrix());
      children_[i]->updateLocalModelAndChildrenMatrices();
    }
  }

}; /* SLX */
