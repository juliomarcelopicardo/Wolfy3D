/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __RENDER_H__
#define __RENDER_H__ 1

#include <DirectXMath.h>
#include "Wolfy3D/material.h"

namespace W3D {

class RenderComponent {

public:

/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

  /// Default class constructor.
  RenderComponent();

  /// Default class destructor.
  ~RenderComponent();

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn   void init(Material* mat, CoreGeometry* geo);
  ///
  /// @brief  Setups the material and geometry for this component.
  /// @param  mat Material to assign to this component.
  /// @param  geo CoreGeometry to assign to this component.
  ///--------------------------------------------------------------------------
  void init(class Material* mat, class Geo* geo);

  ///--------------------------------------------------------------------------
  /// @fn   void render(TransformComponent* transform);
  ///
  /// @brief  renders this component using the specified transform.
  /// @param  transform TransformComponent use to obtain matrices for rendering.
  ///--------------------------------------------------------------------------
  void render(class TransformComponent* transform);

/*******************************************************************************
***                           Private                                        ***
*******************************************************************************/


private:

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/
   
  ///--------------------------------------------------------------------------
  /// @fn   void setupDeviceContext();
  ///
  /// @brief  setup the device context sending all the info to render.
  ///--------------------------------------------------------------------------
  void setupDeviceContext();

/*******************************************************************************
***                       Private Attributes                                 ***
*******************************************************************************/

  /// Whether this component have been initialized or not
  bool initialized_;
  /// Material of the component.
  class Material* material_;
  /// Geometry of the component.
  class Geo* geometry_;


}; /* RenderComponent */

}; /* W3D */

#endif
