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

private:

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/
  
/// Private copy constructor.
  Scene(const Scene& copy);
  /// Private operator of assignment.
  Scene operator=(const Scene& copy);


/*******************************************************************************
***                       Private Attributes                                 ***
*******************************************************************************/



}; /* Scene */

}; /* W3D */
#endif