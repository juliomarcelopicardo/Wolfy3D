/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __BULLET_H__
#define __BULLET_H__ 1

#include <vector>
#include "Wolfy3D.h"
#include "core/geo.h"
#include "core/core.h"
#include "core/entity.h"

namespace W3D {
  
class Bullet {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Bullet();
  /// Default class destructor
	~Bullet();
  /// copy constructor.
  Bullet(const Bullet& copy);
  /// operator of assignment.
  Bullet operator=(const Bullet& copy);

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes all the elements of the class.
  ///--------------------------------------------------------------------------
  void init();

  ///--------------------------------------------------------------------------
  /// @fn   void update(const float32& delta_time);
  ///
  /// @param delta_time Delta time, time in miliseconds between frames.
  /// @brief updates all the elements of the class.
  ///--------------------------------------------------------------------------
  void update(const float32& delta_time);


/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/



/*******************************************************************************
***                       Public  Attributes                                 ***
*******************************************************************************/


  /* Hierarchy */

  /// Object Root node.
  Entity root_;
  /// Bullet geometry node.
  Entity bullet_;

  /* Parameters */

  /// Bullet speed
  float32 projectile_speed_;
  /// Bullet velocity
  DirectX::XMFLOAT3 projectile_velocity_;
  /// Set if the bullet is active or not.
  bool is_active_;



private:

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/



  /* Init methods */

  /// Init hierarchy.
  void initHierarchy();
  /// Initialize the geometries.
  void initGeometries();
  /// Initialize the transforms.
  void initTransforms();
  /// Initialize the material.
  void initMaterials();
  /// Initialize the render components.
  void initRenderComponents();


/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/


  /* Render Properties */
  
  /// Material used to render the plane. 
  MaterialDiffuse material_;
  /// Bullet geometry.
  Geo geometry_;



}; /* Bullet */

}; /* W3D */

#endif