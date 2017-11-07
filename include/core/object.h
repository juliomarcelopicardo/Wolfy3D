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

  /// Transform component.
  TransformComponent* transform_;
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
  /// @fn   void update();
  ///
  /// @brief  Updates the component.
  ///--------------------------------------------------------------------------
  void update();

  ///--------------------------------------------------------------------------
  /// @fn     void addComponent(ComponentType component);
  ///
  /// @brief Adds a component to the current obj
  /// @param component type of component to be initialized on this object.
  ///--------------------------------------------------------------------------
  void addComponent(ComponentType component);

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


  /*******************************************************************************
  ***                           Private                                        ***
  *******************************************************************************/

  Object* parent_;
  std::vector<Object*> children_;

 private:

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
