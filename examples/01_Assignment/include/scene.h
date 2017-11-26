/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __SCENE_H__
#define __SCENE_H__ 1

#include "Wolfy3D.h"
#include "airplane.h"
#include "terrain.h"
#include "bullet.h"
#include "skybox.h"
#include "robot.h"

namespace W3D {


/// Class to manage all the scene which will be rendered.
class Scene {

public:
  

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Scene();
  /// Default class destructor
	~Scene();

/*******************************************************************************
***                             Public methods                               ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes all the elements of the scene.
  ///--------------------------------------------------------------------------
  void init();

  ///--------------------------------------------------------------------------
  /// @fn   void update();
  ///
  /// @param delta_time Delta time, miliseconds between frames.
  /// @brief updates all the elements of the scene.
  ///--------------------------------------------------------------------------
  void update(const float32 delta_time);

  ///--------------------------------------------------------------------------
  /// @fn   void render();
  ///
  /// @brief  Renderize all the elementrs of the scene.
  ///--------------------------------------------------------------------------
  void render();




/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/



/*******************************************************************************
***                          Public  Attributes                              ***
*******************************************************************************/

  /// Main root of the whole scene. Will be the node rendered recursively.
  Entity root_;

  /* Scene objects */

  /// Airplane object.
  Airplane plane_;
  /// Terrain object.
  Terrain terrain_;
  /// Skybox object.
  SkyBox sky_box_;
  /// Red Robot.
  Robot red_robot_;
  /// Blue Robot.
  Robot blue_robot_;
  /// Green Robot.
  Robot green_robot_;
  /// Yellow Robot.
  Robot yellow_robot_;

  /// Land track node.
  Entity landing_track_;
  /// Landing track camera_;
  Entity landing_track_camera_;

private:

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/
  
/// Private copy constructor.
  Scene(const Scene& copy);
  /// Private operator of assignment.
  Scene operator=(const Scene& copy);


  /* Camera Modes */

  /// Depending on the camera mode, will set the camera position and target.
  void updateCameraMode();
  /// Update inputs.
  void switchCameraMode();
  

  /* Robots */
  
  /// Init Robots
  void initRobots();
  /// Update Robots
  void updateRobots(const float32 delta_time);
  /// Active Robots animations
  void activeRobots();
  /// Sets the animation speed of the robots.
  void setRototsAnimationSpeed(const float32 speed);


  /* Animations debug mode */
  
  /// Enable debug mode
  void enableAnimationsDebugMode();
  /// Disable Animations debug mode.
  void disableAnimationsDebugMode();

/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/

  enum CameraMode {
    kCameraMode_Plane3rdPerson = 0,
    kCameraMode_LandingTrack = 1,
    kCameraMode_PlaneGun = 2,
    kCameraMode_RedRobot = 3,
    kCameraMode_GreenRobot = 4,
    kCameraMode_BlueRobot = 5,
    kCameraMode_YellowRobot = 6,
  };

  /// Will set will camera will be rendering the scene.
  CameraMode camera_mode_;


  /* Animations Debug Mode */

  /// Sets if the debug mode for tha 
  bool is_debug_mode_active_;
  /// Debug mode animation speed scale.
  float32 debug_mode_speed_;
  /// Speed of the animations before entering debug mode.
  float32 last_speed_saved_;
  /// Keyframe speed to jump between steps.
  float32 key_frame_step_time_;
  /// Animations current speed.
  float32 animations_speed_;

}; /* Scene */

}; /* W3D */
#endif