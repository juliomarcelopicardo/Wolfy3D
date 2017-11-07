#ifndef AEROPLANE_H
#define AEROPLANE_H

//*********************************************************************************************
// File:			Aeroplane.h
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include <vector>
#include "core/geometry.h"
#include "silverlynx.h"
#include "core/core.h"

__declspec(align(16)) class Aeroplane {

public:
   
  struct Bullet {
    SLX::Object* obj;
    bool shot;
    DirectX::XMVECTOR dir;
  };

  const int kNumberOfBullets = 10;

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
  ///--------------------------------------------------------------------------
  void init(SLX::Object* scene);


  void shoot();
  void update();

  ///--------------------------------------------------------------------------
  /// @fn   void move_pitch(SLX::float32 pitch_limit_degrees, bool facing_upwards);
  ///
  /// @brief Moves the aeroplane in pitch axis according params.
  /// @param pitch_limit_degrees maximum degrees the pitch can rotate to.
  /// @param facing_upwards if true aeroplane will move +X, -X otherwise.
  ///--------------------------------------------------------------------------
  void move_pitch(SLX::float32 pitch_limit_degrees, bool facing_upwards);

  ///--------------------------------------------------------------------------
  /// @fn   void move_roll_yaw(SLX::float32 roll_limit_degrees, bool facing_leftwards, bool enable_yaw);
  ///
  /// @brief Moves the aeroplane in roll and yaw axis according params.
  /// @param roll_limit_degrees maximum degrees the roll can rotate to.
  /// @param facing_leftwards if true aeroplane will move (-Y,+Z), (Y,-Z) otherwise.
  /// @param enable_yaw enables yaw rotation along roll. Useful to disable when
  ///        we want to stabilize the aeroplane to its original Roll rotation.
  ///--------------------------------------------------------------------------
  void move_roll_yaw(SLX::float32 roll_limit_degrees, bool facing_leftwards, bool enable_yaw);

  ///--------------------------------------------------------------------------
  /// @fn     void move_forward();
  ///
  /// @brief Moves the aeroplane forward according forward_speed.
  ///--------------------------------------------------------------------------
  void move_forward();

/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void set_speed(SLX::float32 forward_speed, SLX::float32 rotation_speed_radians);
  ///
  /// @brief Forward and Rotation speed setters.
  /// @param forward_speed speed of the aeroplane when moving forward.
  /// @param rotation_speed_radians speed of the aeroplane when rotating Roll,Pitch,Yaww axis.
  ///--------------------------------------------------------------------------
  void set_speed(SLX::float32 forward_speed, SLX::float32 rotation_speed_radians);

  ///--------------------------------------------------------------------------
  /// @fn   SLX::Object& root()
  ///
  /// @brief Aeroplane root getter.
  /// @return SLX::Object root of the aeroplane.
  ///--------------------------------------------------------------------------
  SLX::Object& root();

  ///--------------------------------------------------------------------------
  /// @fn   SLX::Object& camera_node()
  ///
  /// @brief Aeroplane main camera position node getter.
  /// @return SLX::Object camera node to place the camera.
  ///--------------------------------------------------------------------------
  SLX::Object& camera_node();

  ///--------------------------------------------------------------------------
  /// @fn   SLX::Object& prop()
  ///
  /// @brief Aeroplane propeller component object getter.
  /// @return SLX::Object aeroplane propeller.
  ///--------------------------------------------------------------------------
  SLX::Object& prop();

  ///--------------------------------------------------------------------------
  /// @fn   SLX::Object& turret()
  ///
  /// @brief Turret component object getter.
  /// @return SLX::Object aeroplane turret.
  ///--------------------------------------------------------------------------
  SLX::Object& turret();

/*******************************************************************************
***                       Public  Attributes                                 ***
*******************************************************************************/

  /// Speed the aeroplane will take when moving forwards
  SLX::float32 forward_speed_;
  /// Speed the bullet will take when moving forwards
  SLX::float32 bullet_speed_;
  /// Speed the aeroplane will take when rotating Yaw,Pitch,Roll
  SLX::float32 rotation_speed_;

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
  SLX::CoreMaterial mat_;
  /// Geometry of the main aeroplane
  SLX::CoreGeometry geo_plane_;
  /// Geometry of the propeller
  SLX::CoreGeometry geo_prop_;
  /// Geometry of the turret
  SLX::CoreGeometry geo_turret_;
  /// Geometry of the gun
  SLX::CoreGeometry geo_gun_;
  /// Root of the aeroplane
  SLX::Object plane_root_;
  /// Plane body object
  SLX::Object plane_;
  /// Plane propeller object
  SLX::Object prop_;
  /// Plane turret object
  SLX::Object turret_;
  ///  Plane gun object
  SLX::Object gun_;
  /// Plane camera node to assign camera position
  SLX::Object camera_node_;
  /// Plane bullets pool
  std::vector<Bullet> bullets_;

  SLX::Object gun_node_;

  SLX::CoreGeometry geo_bullet_;

  int current_bullet_;
};

#endif