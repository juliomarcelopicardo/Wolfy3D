/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/


#ifndef __TERRAIN_H__
#define __TERRAIN_H__ 1

#include <vector>
#include "Wolfy3D.h"
#include "core/texture.h"
#include "core/geo.h"
#include "core/core.h"
#include "core/entity.h"

namespace W3D {
  
class Terrain {

public:
  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor
  Terrain();
  /// Default class destructor
	~Terrain();

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
  Terrain(const Terrain& copy);
  /// Private operator of assignment.
  Terrain operator=(const Terrain& copy);

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
  
  /// Material used to render the plane. 
  MaterialTerrain material_;
  /// Terrain geometry.
  Geo geo_terrain_;
  /// Texture used as the material map.
  Texture map_;
  /// Texture used as grass.
  Texture grass_;
  /// Texture moss.
  Texture moss_;
  /// Texture used to render asphalt.
  Texture asphalt_;


}; /* Terrain */

}; /* W3D */

#endif