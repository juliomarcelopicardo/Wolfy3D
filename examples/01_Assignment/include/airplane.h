/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __AIRPLANE_H__
#define __AIRPLANE_H__ 1

#include <vector>
#include "core/geo.h"
#include "Wolfy3D.h"
#include "core/core.h"
#include "core/entity.h"
#include "bullet.h"

namespace W3D {
  
class Airplane {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Airplane();
  /// Default class destructor
	~Airplane();

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

  /* Skin */
  
  /// Albedo color.
  DirectX::XMFLOAT4 color_;

  /* Hierarchy */

  /// Object Root node.
  Entity root_;
  /// Plane root node.
  Entity plane_root_;
  /// Plane node.
  Entity plane_;
  /// Prop node.
  Entity prop_;
  /// Turret node.
  Entity turret_;
  /// Gun node.
  Entity gun_;
  /// Gun camera
  Entity gun_camera_;
  /// Bullet spawn point.
  Entity bullet_spawn_point_;
  /// Back 3rd person camera node.
  Entity back_camera_;

  /* Bullets */

  /// Bullet pull.
  std::vector<Bullet> bullet_;
  /// Number of bullets
  uint32 num_bullets_;
  /// Bullet index
  uint32 bullet_index_;

private:

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/

  /// Private copy constructor.
  Airplane(const Airplane& copy);
  /// Private operator of assignment.
  Airplane operator=(const Airplane& copy);



  /* Init methods */

  /// Initialize the geometries.
  void initGeometries();
  /// Initialize hierarchy nodes.
  void initHierarchy();
  /// Initialize the transforms.
  void initTransforms();
  /// Initialize the render components.
  void initRenderComponents();
  /// Will set the quaternion constraints.
  void setupLerpQuaternionConstraints();


  /* Bullets */

  /// Fires a bullet
  void fire();


  /* Transformation update */
  
  /// Rotations update.
  void updateRotations(const float32& delta_time);
  /// Update Lerping values.
  void updateRotationLerpingValues(const float32& delta_time);
  /// Update Z rotation lerping Values.
  void updateRotationLerpingValuesZ(const float32& delta_time);
  /// Update X rotation lerping Values.
  void updateRotationLerpingValuesX(const float32& delta_time);
  /// Update translations.
  void updateTranslations(const float32& delta_time);
  

  /* Input update */

  /// Input update.
  void updateInput();


  /* ImGui update */

  /// Main update function of ImGui.
  void updateImGui();
  /// Update function for the rotation in X axis.
  void updateImGuiRotationX();
  /// Update function for the rotation in Z axis.
  void updateImGuiRotationZ();

/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/

  /* Render Properties */
  
  /// Material used to render the plane. 
  MaterialDiffuse material_;
    /// Main body of the plane geometry.
  Geo geo_plane_;
  /// Gun geometry.
  Geo geo_gun_;
  /// Prop geometry.
  Geo geo_prop_;
  /// Turret geometry.
  Geo geo_turret_;
 

  /* Rotation constraints */

  /// Save the z rotation quaternion.
  DirectX::XMFLOAT4 z_quaternion_rotation_;
  /// Quaternion limits where 0 is the negative and 1 the positive.
  DirectX::XMFLOAT4 z_quaternion_limit_[2];
  /// Alpha lerp Z axis rotation. Values will go between -1 and 1
  float32 z_rotation_alpha_;
  /// Save the X rotation quaternion.
  DirectX::XMFLOAT4 x_quaternion_rotation_;
  /// Quaternion limits where 0 is the negative and 1 the positive.
  DirectX::XMFLOAT4 x_quaternion_limit_[2];
  /// Alpha lerp Z axis rotation. Values will go between -1 and 1
  float32 x_rotation_alpha_;
  /// Quaternion rotation when the plane is in idle or not moving.
  DirectX::XMFLOAT4 quaternion_idle_rotation;


  /* Rotation Parameters */

  /// Propeller rotation speed
  float32 prop_rotation_speed_;
  /// Plane Z axis rotation speed.
  float32 z_rotation_speed_;
  /// Plane Z rotation to idle speed. Speed used to come back to idle after rotating.
  float32 z_rotation_to_idle_speed_;
  /// Z axis rotation limit in degrees.
  float32 z_rotation_constraint_degrees;
  /// Plane X axis rotation speed.
  float32 x_rotation_speed_;
  /// Plane X rotation to idle speed. Speed used to come back to idle after rotating.
  float32 x_rotation_to_idle_speed_;
  /// X axis rotation limit in degrees.
  float32 x_rotation_constraint_degrees;
  /// Y axis max rotation speed.
  float32 y_rotation_speed_;
  /// Turret rotation speed.
  float32 turret_rotation_speed_;
  /// Gun Rotation speed.
  float32 gun_rotation_speed_;

  /* Traslation Parameters */
  
  /// Max ascension / descension speed.
  float32 up_traslation_speed_;
  /// If active will be able to accelerate and rotate.
  bool is_plane_engine_active_;
  /// Max forward speed.
  float32 max_forward_speed_;
  /// forward speed.
  float32 forward_speed_;
  /// Traslation Velocity vector.
  DirectX::XMFLOAT3 traslation_velocity_;
  /// Forward acceleration.
  float32 forward_acceleration_;

  /* Input */

  /// A key pressed.
  bool is_A_key_pressed_;
  /// D key pressed.
  bool is_D_key_pressed_;
  /// W key pressed.
  bool is_W_key_pressed_;
  /// S key pressed.
  bool is_S_key_pressed_;
  /// Spacebar down.
  bool is_SpaceBar_key_down_;
  /// Right mouse button (Fire)
  bool is_right_mouse_button_down_;



}; /* Airplane */

}; /* W3D */

#endif