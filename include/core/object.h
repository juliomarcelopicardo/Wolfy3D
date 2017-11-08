/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __OBJECT_H__
#define __OBJECT_H__ 1

#include "core/components/transform.h"
#include "core/components/render3d.h"
#include <vector>

namespace SLX {

class Object {

 public:

  /*******************************************************************************
  ***                               Attributes                                 ***
  *******************************************************************************/

  /// Render3D component.
  Render3DComponent* render3D_;

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  /// Default class constructor.
  Object();

  /// Default class destructor.
  ~Object();

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes the component.
  ///--------------------------------------------------------------------------
  void init();

  ///--------------------------------------------------------------------------
  /// @fn     void addComponent(ComponentType component);
  ///
  /// @brief Adds a component to the current obj
  /// @param component type of component to be initialized on this object.
  /// @param mat material to be assigned in case ComponentType is Render3D
  /// @param geo geometry to be assigned in case ComponentType is Render3D
  ///--------------------------------------------------------------------------
  void addComponent(ComponentType component, CoreMaterial *mat, CoreGeometry *geo);

  ///--------------------------------------------------------------------------
  /// @fn     void addChild(Object* obj);
  ///
  /// @brief Adds or attaches another object as a children
  /// @param obj Object that will be attached as a children.
  ///--------------------------------------------------------------------------
  void addChild(Object* obj);

  /*******************************************************************************
  ***                           Transform methods                              ***
  *******************************************************************************/

  void updateLocalModelAndChildrenMatrices();

  /*******************************************************************************
  ***                            Setters & Getters                             ***
  *******************************************************************************/

  TransformComponent* transform();

  /*******************************************************************************
  ***                           Private                                        ***
  *******************************************************************************/

  Object* parent_;
  std::vector<Object*> children_;

  /// Transform component.
  TransformComponent* transform_;

 private:

   Object(const Object& copy);
   Object& operator=(const Object& copy);

  /*******************************************************************************
  ***                               Attributes                                 ***
  *******************************************************************************/

  /// Whether this object is initialized or not.
  bool initialized_;


  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/



}; /* Object */

}; /* SLX */

#endif
