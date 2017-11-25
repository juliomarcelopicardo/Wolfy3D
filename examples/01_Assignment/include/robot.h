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
  Geo geo_body_;
  /// Left Ankle geometry.
  Geo geo_left_ankle_;
  /// Left Elbow geometry.
  Geo geo_left_elbow_;
  /// Left Hip geometry.
  Geo geo_left_hip_;
  /// Left Knee geometry.
  Geo geo_left_knee_;
  /// Left Shoulder geometry.
  Geo geo_left_shoulder_;
  /// Left Wrist geometry.
  Geo geo_left_wrist_;
  /// Right Ankle geometry.
  Geo geo_right_ankle_;
  /// Right Elbow geometry.
  Geo geo_right_elbow_;
  /// Right Hip geometry.
  Geo geo_right_hip_;
  /// Right Knee geometry.
  Geo geo_right_knee_;
  /// Right Shoulder geometry.
  Geo geo_right_shoulder_;
  /// Right Wrist geometry.
  Geo geo_right_wrist_;
  /// Neck geometry.
  Geo geo_neck_;
  /// Pelvis geometry.
  Geo geo_pelvis_presley_;

  /// Material used to render. 
  MaterialDiffuse material_;


}; /* Robot */

}; /* W3D */

#endif