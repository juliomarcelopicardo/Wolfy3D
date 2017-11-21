/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef AEROPLANE_H
#define AEROPLANE_H

#include <vector>
#include "core/geo.h"
#include "Wolfy3D.h"
#include "core/core.h"
#include "core/entity.h"

__declspec(align(16)) class Aeroplane {

public:
  
  /// Struct forming a bullet
  struct Bullet {
    W3D::Entity* obj;
    bool shot;
    DirectX::XMVECTOR dir;
  };

  /// Maximum number of bullets in the bullet pool
  const int kNumberOfBullets = 10;

  /// Mode of the Camera to setup the view according camera nodes
  enum class CameraMode {
    Tail,
    Gun,
    AroundLanding
  };

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Aeroplane();
  /// Default class destructor
	~Aeroplane();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes the airplane resources, geometries and matrices.
  ///         Spawns it along camera nodes in the specified scene root.
  /// @param  scene scene root to place the airplane.
  ///--------------------------------------------------------------------------
  void init(W3D::Entity* scene);

  ///--------------------------------------------------------------------------
  /// @fn     void shoot();
  ///
  /// @brief  shoots a bullet facing the airplane gun direction.
  ///--------------------------------------------------------------------------
  void shoot();

  ///--------------------------------------------------------------------------
  /// @fn       void update();
  ///
  /// @brief  updates aeroplane logic such as components rotations, speed...
  ///--------------------------------------------------------------------------
  void update();

  ///--------------------------------------------------------------------------
  /// @fn   void move_pitch(W3D::float32 pitch_limit_degrees, bool facing_upwards);
  ///
  /// @brief Moves the aeroplane in pitch axis according params.
  /// @param pitch_limit_degrees maximum degrees the pitch can rotate to.
  /// @param facing_upwards if true aeroplane will move +X, -X otherwise.
  ///--------------------------------------------------------------------------
  void move_pitch(W3D::float32 pitch_limit_degrees, bool facing_upwards);

  ///--------------------------------------------------------------------------
  /// @fn   void move_roll_yaw(W3D::float32 roll_limit_degrees, bool facing_leftwards, bool enable_yaw);
  ///
  /// @brief Moves the aeroplane in roll and yaw axis according params.
  /// @param roll_limit_degrees maximum degrees the roll can rotate to.
  /// @param facing_leftwards if true aeroplane will move (-Y,+Z), (Y,-Z) otherwise.
  /// @param enable_yaw enables yaw rotation along roll. Useful to disable when
  ///        we want to stabilize the aeroplane to its original Roll rotation.
  ///--------------------------------------------------------------------------
  void move_roll_yaw(W3D::float32 roll_limit_degrees, bool facing_leftwards, bool enable_yaw);

  ///--------------------------------------------------------------------------
  /// @fn     void move_forward();
  ///
  /// @brief Moves the aeroplane forward according forward_speed.
  ///--------------------------------------------------------------------------
  void move_forward();

  ///--------------------------------------------------------------------------
  /// @fn     void toggleCameraMode();
  ///
  /// @brief Toggles the camera mode between Tail, Gun, Landing.
  ///        This will change the position and the target of the camera
  ///        inside update_camera_view function.
  ///--------------------------------------------------------------------------
  void toggleCameraMode();

  ///--------------------------------------------------------------------------
  /// @fn     void update_camera_view(W3D::Cam* cam);
  ///
  /// @brief Updates camera position and target according CameraMode.
  ///        CameraMode will decide which camera node spot will make the view.
  /// @param cam Camera to fill with the view parameters (position, target).
  ///--------------------------------------------------------------------------
  void update_camera_view(W3D::Cam* cam);

  ///--------------------------------------------------------------------------
  /// @fn       void imgui_debug();
  ///
  /// @brief IMGUI render code showing aeroplane debug information.
  ///--------------------------------------------------------------------------
  void imgui_debug();

/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void set_speed(W3D::float32 forward_speed, W3D::float32 rotation_speed_radians);
  ///
  /// @brief Forward and Rotation speed setters.
  /// @param forward_speed speed of the aeroplane when moving forward.
  /// @param rotation_speed_radians speed of the aeroplane when rotating Roll,Pitch,Yaww axis.
  ///--------------------------------------------------------------------------
  void set_speed(W3D::float32 forward_speed, W3D::float32 rotation_speed_radians);

  ///--------------------------------------------------------------------------
  /// @fn   W3D::Entity& root()
  ///
  /// @brief Aeroplane root getter.
  /// @return W3D::Entity root of the aeroplane.
  ///--------------------------------------------------------------------------
  W3D::Entity& root();

  ///--------------------------------------------------------------------------
  /// @fn   W3D::Entity& prop()
  ///
  /// @brief Aeroplane propeller component Entity getter.
  /// @return W3D::Entity aeroplane propeller.
  ///--------------------------------------------------------------------------
  W3D::Entity& prop();

  ///--------------------------------------------------------------------------
  /// @fn   W3D::Entity& turret()
  ///
  /// @brief Turret component Entity getter.
  /// @return W3D::Entity aeroplane turret.
  ///--------------------------------------------------------------------------
  W3D::Entity& turret();

/*******************************************************************************
***                       Public  Attributes                                 ***
*******************************************************************************/

  /// Speed the aeroplane will take when moving forwards
  W3D::float32 forward_speed_;
  /// Acceleration of the aeroplane (1.0f max)
  W3D::float32 acceleration_;
  /// Speed the bullet will take when moving forwards
  W3D::float32 bullet_speed_;
  /// Speed the aeroplane will take when rotating Yaw,Pitch,Roll
  W3D::float32 rotation_speed_;

private:

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void move_yaw(bool facing_leftwards)
  ///
  /// @brief Moves the aeroplane in yaw axis according facing_leftwards param.
  /// @param facing_leftwards if true aeroplane will move -Y, +Y otherwise.
  ///--------------------------------------------------------------------------
  void move_yaw(bool facing_leftwards);

/*******************************************************************************
***                       Private Attributes                                 ***
*******************************************************************************/

  /// Material 
  W3D::MaterialDiffuse mat_;
  /// Geometry of the main aeroplane
  W3D::Geo geo_plane_;
  /// Geometry of the propeller
  W3D::Geo geo_prop_;
  /// Geometry of the turret
  W3D::Geo geo_turret_;
  /// Geometry of the gun
  W3D::Geo geo_gun_;
  /// Root of the aeroplane
  W3D::Entity plane_root_;
  /// Plane body Entity
  W3D::Entity plane_;
  /// Plane propeller Entity
  W3D::Entity prop_;
  /// Plane turret Entity
  W3D::Entity turret_;
  ///  Plane gun Entity
  W3D::Entity gun_;
  /// Node to be placed on airplane spawning point (landing rotation camera spot)
  W3D::Entity landing_node_;
  /// Plane camera node to assign camera position
  W3D::Entity camera_node_;
  /// Plane camera gun node to assign camera position
  W3D::Entity camera_gun_node_;
  /// Plane camera landing node to assign camera position
  W3D::Entity camera_landing_node_;
  /// Plane bullets pool
  std::vector<Bullet> bullets_;
  /// Node to spawn bullets in front of the gun
  W3D::Entity gun_node_;
  /// Geometry of the bullets
  W3D::Geo geo_bullet_;
  /// Root node of the whole airplane Entity
  W3D::Entity root_node_;
  /// Current bullet in bullet pool
  int current_bullet_;
  /// Turns on the Aeroplane Engine
  bool engine_enabled_;
  /// Mode of the Camera to display the aeroplane
  CameraMode camera_mode_;
};

#endif