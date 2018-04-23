/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __SKYBOX_H__
#define __SKYBOX_H__ 1

#include <vector>
#include "Wolfy3D.h"
#include "core/texture.h"
#include "core/geo.h"
#include "core/core.h"
#include "core/entity.h"

namespace W3D {
  
class SkyBox {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  SkyBox();
  /// Default class destructor
	~SkyBox();

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
  /// @param delta_time Delta time, time in miliseconds between frames.
  /// @brief updates all the elements of the class.
  ///--------------------------------------------------------------------------
  void update(const float32& delta_time);


/*******************************************************************************
***                          Setters and Getters                             ***
*******************************************************************************/



/*******************************************************************************
***                       Public  Attributes                                 ***
*******************************************************************************/


  /* Hierarchy */

  /// Object Root node.
  Entity root_;





private:

/*******************************************************************************
***                             Private methods                              ***
*******************************************************************************/

  /// Private copy constructor.
  SkyBox(const SkyBox& copy);
  /// Private operator of assignment.
  SkyBox operator=(const SkyBox& copy);

/* Init methods */

/// Initialize the geometries.
  void initGeometries();
  /// Initialize textures used in the material.
  void initTextures();
  /// Initialize the transforms.
  void initTransforms();
  /// Initialize the material.
  void initMaterials();
  /// Initialize the render components.
  void initRenderComponents();


/*******************************************************************************
***                           Private Attributes                             ***
*******************************************************************************/


  /* Render Properties */
  
  /// Material used to render the box. 
  MaterialTextured material_;
  /// SkyBox geometry.
  Geometry geometry_;
  /// Texture used as the skybox cube background.
  Texture2D texture_;


}; /* SkyBox */

}; /* W3D */

#endif