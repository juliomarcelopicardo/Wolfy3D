/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __ANIMATION_CONTROLLER_H__
#define __ANIMATION_CONTROLLER_H__ 1

#include <vector>
#include "Wolfy3D.h"
#include "animation.h"

namespace W3D {
  
class AnimationController {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  AnimationController();
  /// Default class destructor
	~AnimationController();
  /// Private copy constructor.
  AnimationController(const AnimationController& copy);
  /// Private operator of assignment.
  AnimationController& operator=(const AnimationController& copy);

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/
  
  ///--------------------------------------------------------------------------
  /// @fn   void init();
  ///
  /// @brief  Initializes all the animations of the class.
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
***                           Public  Attributes                                 ***
*******************************************************************************/

  /// Robot where the animations will be played.
  class Robot* robot;
  /// Pointer to the current animation which is being played.
  Animation* current_animation;
  /// Idle animation.
  Animation idle;
  /// Attack animation.
  Animation attack;
  /// Die animation.
  Animation die;


private:

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/




/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/




}; /* AnimationController */

}; /* W3D */

#endif