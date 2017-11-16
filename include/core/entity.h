/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __OBJECT_H__
#define __OBJECT_H__ 1

#include "core/components/transform.h"
#include "core/components/render.h"
#include "Wolfy3D/material.h"
#include "core/geo.h"
#include <vector>

namespace W3D {

class Entity {

 public:

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  /// Default class constructor.
  Entity();

  /// Default class destructor.
  ~Entity();

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn     void addComponent(ComponentType component);
  ///
  /// @brief Adds a component to the current entity.  
  /// @param component type of component to be initialized on this entity.
  /// @param mat material to be assigned in case ComponentType is Render3D
  /// @param geo geometry to be assigned in case ComponentType is Render3D
  ///--------------------------------------------------------------------------
  void addComponent(ComponentType component, Material* mat, Geo* geo);

  ///--------------------------------------------------------------------------
  /// @fn     void addChild(Entity* entity);
  ///
  /// @brief Adds or attaches another entity as a children
  /// @param entity Entity that will be attached as a children.
  ///--------------------------------------------------------------------------
  void addChild(Entity* entity);

  /*******************************************************************************
  ***                           Transform methods                              ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn       void updateLocalModelAndChildrenMatrices();
  ///
  /// @brief Updates the local model of this entity and all of its children.
  ///--------------------------------------------------------------------------
  void updateLocalModelAndChildrenMatrices();

  /*******************************************************************************
  ***                            Setters & Getters                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn     TransformComponent& transform();
  ///
  /// @brief Transform component getter
  /// @return TransformComponent attached to this entity.
  ///--------------------------------------------------------------------------
  TransformComponent& transform();

  ///--------------------------------------------------------------------------
  /// @fn     Render3DComponent* render3D();
  ///
  /// @brief Render3DComponent getter.
  /// @return Render3DComponent pointer attached to this entity.
  ///--------------------------------------------------------------------------
  RenderComponent* render3D();

  /*******************************************************************************
  ***                           Private                                        ***
  *******************************************************************************/

  /// Parent of this entity  
  Entity* parent_;
  /// Childrens attached to this entity  
  std::vector<Entity*> children_;

 private:

   Entity(const Entity& copy);
   Entity& operator=(const Entity& copy);

  /*******************************************************************************
  ***                               Attributes                                 ***
  *******************************************************************************/

  /// Whether this entity is initialized or not.
  bool initialized_;
  /// Transform component.
  TransformComponent transform_;
  /// Render3D component.
  RenderComponent* render3D_;
  
  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/



}; /* Entity */

}; /* W3D */

#endif
