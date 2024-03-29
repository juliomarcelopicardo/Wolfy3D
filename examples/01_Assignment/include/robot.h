/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __ROBOT_H__
#define __ROBOT_H__ 1

#include <vector>
#include "Wolfy3D.h"
#include "core/texture.h"
#include "core/geo.h"
#include "core/core.h"
#include "core/entity.h"
#include "animation_controller.h"

namespace W3D {
  
class Robot {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Robot();
  /// Default class destructor
	~Robot();

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
  /// @brief updates all the elements of the class.
  /// @param delta_time Delta time, time in miliseconds between frames.
  ///--------------------------------------------------------------------------
  void update(const float32& delta_time);

  ///--------------------------------------------------------------------------
  /// @fn   void checkDistanceToPlane(const DirectX::XMVECTOR& plane_pos);
  ///
  /// @brief checks if the distance to the plane is enough to attack.
  /// @param plane_pos Plane position in world.
  ///--------------------------------------------------------------------------
  void checkDistanceToPlane(const DirectX::XMVECTOR& plane_pos);


/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void set_material_color(const float32 r, const float32 g, const float32 b);
  ///
  /// @brief Material albedo color setter.
  /// @param r Red component of the color.
  /// @param g Green component of the color.
  /// @param b Blue component of the color.
  ///--------------------------------------------------------------------------
  void set_material_color(const float32 r, const float32 g, const float32 b);

  ///--------------------------------------------------------------------------
  /// @fn   void set_animations_speed(const float32 speed);
  ///
  /// @brief Sets the animations speed.
  /// @param speed Speed factor scale of the animations.
  ///--------------------------------------------------------------------------
  void set_animations_speed(const float32 speed);

/*******************************************************************************
***                           Public  Attributes                             ***
*******************************************************************************/


  /* Hierarchy */

  /// Class root.
  Entity root_;

  /// Root node.
  Entity robot_root_;
  /// Body node.
  Entity body_;
  /// Left Ankle node.
  Entity left_ankle_;
  /// Left Elbow node.
  Entity left_elbow_;
  /// Left Hip node.
  Entity left_hip_;
  /// Left Knee node.
  Entity left_knee_;
  /// Left Shoulder node.
  Entity left_shoulder_;
  /// Left Wrist node.
  Entity left_wrist_;
  /// Right Ankle node.
  Entity right_ankle_;
  /// Right Elbow node.
  Entity right_elbow_;
  /// Right Hip node.
  Entity right_hip_;
  /// Right Knee node.
  Entity right_knee_;
  /// Right Shoulder node.
  Entity right_shoulder_;
  /// Right Wrist node.
  Entity right_wrist_;
  /// Neck node.
  Entity neck_;
  /// Pelvis node.
  Entity pelvis_presley_;

  /// Camera designed to see the robot animations.
  Entity camera_node_;

  /// Animation controller
  AnimationController anim_controller_;



private:

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/

  /// Private copy constructor.
  Robot(const Robot& copy);
  /// Private operator of assignment.
  Robot operator=(const Robot& copy);

/* Init methods */

  /// Initialize the geometries.
  void initGeometries();
  /// Initialize the names of the nodes.
  void initNames();
  /// Initialize textures used in the material.
  void initHierarchy();
  /// Initialize the transforms.
  void initTransforms();
  /// Initialize the material.
  void initMaterials();
  /// Initialize the render components.
  void initRenderComponents();
  /// Initialize the animation controller.
  void initAnimations();


  /* Imgui methods */

  /// Main update function of ImGui.
  void updateImGui();
  /// Generate imgui stats of a node.
  void generateNodeStatsImGui(Entity* entity);
  /// Generate recursively all the info from the root_entity and it's children.
  void generateRootTreeStatsImGui(Entity* root_entity);

/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/



  /* Render Properties */
  
  /// Body geometry.
  Geometry geo_body_;
  /// Left Ankle geometry.
  Geometry geo_left_ankle_;
  /// Left Elbow geometry.
  Geometry geo_left_elbow_;
  /// Left Hip geometry.
  Geometry geo_left_hip_;
  /// Left Knee geometry.
  Geometry geo_left_knee_;
  /// Left Shoulder geometry.
  Geometry geo_left_shoulder_;
  /// Left Wrist geometry.
  Geometry geo_left_wrist_;
  /// Right Ankle geometry.
  Geometry geo_right_ankle_;
  /// Right Elbow geometry.
  Geometry geo_right_elbow_;
  /// Right Hip geometry.
  Geometry geo_right_hip_;
  /// Right Knee geometry.
  Geometry geo_right_knee_;
  /// Right Shoulder geometry.
  Geometry geo_right_shoulder_;
  /// Right Wrist geometry.
  Geometry geo_right_wrist_;
  /// Neck geometry.
  Geometry geo_neck_;
  /// Pelvis geometry.
  Geometry geo_pelvis_presley_;

  /// Material used to render. 
  MaterialDiffuse material_;

  /// Distance to robot is enough to attack.
  bool is_near_to_plane_;
  /// Distance between robots and plane to change animations.
  float32 distance_to_change_animations_;

}; /* Robot */

}; /* W3D */

#endif