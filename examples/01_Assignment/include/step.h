/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __STEPS__H__
#define __STEPS__H__ 1

#include <vector>
#include <DirectXMath.h>
#include "Wolfy3D.h"
#include "core/texture.h"
#include "core/geo.h"
#include "core/core.h"
#include "core/entity.h"

namespace W3D {
  
class StepsInfo {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  StepsInfo();
  /// Default class destructor
	~StepsInfo();
  /// copy constructor.
  StepsInfo(const StepsInfo& copy);
  /// operator of assignment.
  StepsInfo& operator=(const StepsInfo& copy);

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   DirectX::XMVECTOR update(const float32& delta_time);
  ///
  /// @brief updates all the elements of the class.
  /// @param delta_time Delta time, time in miliseconds between frames.
  /// @returns Actual transformation (position or quaternion).
  ///--------------------------------------------------------------------------
  DirectX::XMVECTOR update(const float32& delta_time);

  ///--------------------------------------------------------------------------
  /// @fn   void start(const bool apply_blending,
  ///                  const DirectX::XMFLOAT4 origin_value = { 0.0f, 0.0f, 0.0f, 0.0f }, 
  ///                  const float32 blending_duration = 0.0f);
  ///
  /// @brief Starts the animation from the first step applying a smooth blending.
  /// @param apply_blending If true will apply a interpolation to the next step.
  /// @param origin_value Origin Transformation value. Current position or rotation.
  /// @param blending_duration Time to interpole to the next animation.
  ///--------------------------------------------------------------------------
  void start(const bool apply_blending = false,
             const DirectX::XMFLOAT4 origin_value = { 0.0f, 0.0f, 0.0f, 0.0f }, 
             const float32 blending_duration = 0.0f);



/*******************************************************************************
***                            Setters and Getters                           ***
*******************************************************************************/



/*******************************************************************************
***                            Public  Attributes                            ***
*******************************************************************************/

  enum Mode {
    kMode_Rotation = 0,
    kMode_Translation,
  };


  /* Info */

  /// Rotation or traslation mode.
  Mode mode;
  /// Timers for each animation step.
  std::vector<float32> step_timers; 
  /// Value of the transformation such as quaternion, positions, etc.
  std::vector<DirectX::XMFLOAT4> step_values;
  /// Num steps of the animation.
  uint32 num_steps;
  

private:

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void startNextStep();
  ///
  /// @brief Jumps to the next step of the animation info.
  ///--------------------------------------------------------------------------
  void startNextStep();

/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/

  /* Lerping info */

  /// To interpole.
  DirectX::XMFLOAT4 origin;
  /// To interpole.
  DirectX::XMFLOAT4 destiny;
  /// Interpolation alpha.
  float32 alpha;
  /// Chronometer.
  float32 timer;
  /// Time to change to the next step or key frame.
  float32 timer_limit;
  /// Step which will be set as destiny.
  uint32 step_destiny;



}; /* StepsInfo */

}; /* W3D */

#endif