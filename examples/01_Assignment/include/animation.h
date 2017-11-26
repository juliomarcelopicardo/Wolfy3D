/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __ANIMATION_H__
#define __ANIMATION_H__ 1

#include <vector>
#include "Wolfy3D.h"
#include "bone.h"

namespace W3D {
  
class Animation {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Animation();
  /// Default class destructor
	~Animation();
  /// Private copy constructor.
  Animation(const Animation& copy);
  /// Private operator of assignment.
  Animation& operator=(const Animation& copy);

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   void initFromFile();
  ///
  /// @brief  Initializes all the bpmes of the class by parsing an xml file.
  /// @param  filename XML file with the bones info.
  ///--------------------------------------------------------------------------
  void initFromFile(const char* filename);

  ///--------------------------------------------------------------------------
  /// @fn   void update(const float32& delta_time);
  ///
  /// @param delta_time Delta time, time in miliseconds between frames.
  /// @brief updates all the elements of the class.
  ///--------------------------------------------------------------------------
  void update(const float32& delta_time);

  ///--------------------------------------------------------------------------
  /// @fn   void start(const bool apply_blending = true, 
  ///                  const float32 blending_duration = 0.5f);
  ///
  /// @brief Starts the animation from the first step applying a smooth blending.
  /// @param apply_blending If true will apply a interpolation to the next step.
  /// @param blending_duration Time to interpole to the next animation.
  ///--------------------------------------------------------------------------
  void start(const bool apply_blending = true, const float32 blending_duration = 0.5f);


/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/



/*******************************************************************************
***                           Public  Attributes                                 ***
*******************************************************************************/

  /// Speed index, 1.0f will be normal speed. The higher, the faster.
  float32 speed;
  /// Robot class.
  class Robot* robot;



private:

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/

  /// Updates all the bones positions.
  void updateBonesPositions(const float32& delta_time);
  /// Updates all the bones rotations.
  void updateBonesRotations(const float32& delta_time);


/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/

  /* Bones hierarchy */

/// Root bone.
  Bone robot_root;
  /// Body bone.
  Bone body;
  /// Left Ankle bone.
  Bone left_ankle;
  /// Left Elbow bone.
  Bone left_elbow;
  /// Left Hip bone.
  Bone left_hip;
  /// Left Knee bone.
  Bone left_knee;
  /// Left Shoulder bone.
  Bone left_shoulder;
  /// Left Wrist bone.
  Bone left_wrist;
  /// Right Ankle bone.
  Bone right_ankle;
  /// Right Elbow bone.
  Bone right_elbow;
  /// Right Hip bone.
  Bone right_hip;
  /// Right Knee bone.
  Bone right_knee;
  /// Right Shoulder bone.
  Bone right_shoulder;
  /// Right Wrist bone.
  Bone right_wrist;
  /// Neck bone.
  Bone neck;
  /// Pelvis bone.
  Bone pelvis_presley;


}; /* Animation */

}; /* W3D */

#endif