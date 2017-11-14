/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/globals.h"
#include "core/object.h"
#include "core/core.h"
#include "core/window.h"
#include "core/geometry.h"


namespace W3D {

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  Object::Object() {
    initialized_ = false;
    render3D_ = nullptr;
    parent_ = nullptr;
    transform_.set_owner(this);
  }

  Object::~Object() {
    if (render3D_) {
      delete render3D_;
    }
    children_.clear();
    parent_ = nullptr;
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  void Object::addComponent(ComponentType component, Material *mat, CoreGeometry *geo) {
    switch (component) {
      case W3D::ComponentType::Render3D: {
        if (!render3D_) {
          render3D_ = new Render3DComponent;
          render3D_->init(mat, geo);
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
    DirectX::XMStoreFloat4x4(&obj->transform_.parent_model_matrix_, transform_.global_model_matrix());
    obj->parent_ = this;
    obj->updateLocalModelAndChildrenMatrices();
  }

  /*******************************************************************************
  ***                           Transform methods                              ***
  *******************************************************************************/

  void Object::updateLocalModelAndChildrenMatrices() {

    transform_.calculateLocalModelMatrix();
    uint32 num_children = children_.size();
    for (uint32 i = 0; i < num_children; i++) {
      DirectX::XMStoreFloat4x4(&children_[i]->transform_.parent_model_matrix_, transform_.global_model_matrix());
      children_[i]->updateLocalModelAndChildrenMatrices();
    }
  }

  /*******************************************************************************
  ***                            Setters & Getters                             ***
  *******************************************************************************/

  W3D::TransformComponent& Object::transform() {
    return transform_;
  }

  W3D::Render3DComponent* Object::render3D() {
    return render3D_;
  }

}; /* W3D */
