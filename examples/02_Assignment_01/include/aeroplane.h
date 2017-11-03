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
    DirectX::XMFLOAT4 position;
    DirectX::XMVECTOR forward;
    DirectX::XMMATRIX orientation_matrix;
    DirectX::XMMATRIX world_matrix;
    SLX::CoreGeometry mesh;
    bool shot;
  };

  const int kNumberOfBullets = 10;

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  Aeroplane(SLX::float32 fX = 0.0f, SLX::float32 fY = 0.0f,
            SLX::float32 fZ = 0.0f, SLX::float32 fRotY = 0.0f);

	~Aeroplane();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes the airplane resources, geometries and matrices.
  ///--------------------------------------------------------------------------
  void init();

  void move_pitch(SLX::float32 pitch_limit_degrees, bool facing_upwards);
  void move_roll_yaw(SLX::float32 roll_limit_degrees, bool facing_leftwards, bool enable_yaw);
  void move_forward();

/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

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

  SLX::float32 forward_speed_;
  SLX::float32 rotation_speed_;

private:

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

  void move_yaw(bool facing_leftwards);

/*******************************************************************************
***                       Private Attributes                                 ***
*******************************************************************************/

  SLX::CoreMaterial mat_;

  SLX::CoreGeometry geo_plane_;
  SLX::CoreGeometry geo_prop_;
  SLX::CoreGeometry geo_turret_;
  SLX::CoreGeometry geo_gun_;

  SLX::Object plane_root_;
  SLX::Object plane_;
  SLX::Object prop_;
  SLX::Object turret_;
  SLX::Object gun_;

  SLX::Object camera_node_;

  std::vector<Bullet> bullets_;
};

#endif