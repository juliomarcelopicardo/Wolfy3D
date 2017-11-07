/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __RENDER3D_H__
#define __RENDER3D_H__ 1

#include <DirectXMath.h>
#include "core/components/component.h"

namespace SLX {

class Render3DComponent : public Component {

  public:

    /*******************************************************************************
    ***                        Constructor and destructor                        ***
    *******************************************************************************/


    /// Default class constructor.
    Render3DComponent();

    /// Default class destructor.
    ~Render3DComponent();

    /*******************************************************************************
    ***                               Public methods                             ***
    *******************************************************************************/

    ///--------------------------------------------------------------------------
    /// @fn   void init();
    ///
    /// @brief  Initializes the component.
    ///--------------------------------------------------------------------------
    void init();

    ///--------------------------------------------------------------------------
    /// @fn   void update();
    ///
    /// @brief  Updates the component.
    ///--------------------------------------------------------------------------
    void update();

    ///--------------------------------------------------------------------------
    /// @fn   void shutdown();
    ///
    /// @brief  Deallocates any memory and setup from this component.
    ///--------------------------------------------------------------------------
    void shutdown();

    ///--------------------------------------------------------------------------
    /// @fn   void setup(CoreMaterial* mat, CoreGeometry* geo);
    ///
    /// @brief  Setups the material and geometry for this component.
    /// @param  mat CoreMaterial to assign to this component.
    /// @param  geo CoreGeometry to assign to this component.
    ///--------------------------------------------------------------------------
    void setup(class CoreMaterial* mat, class CoreGeometry* geo);

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

    /*******************************************************************************
    ***                       Private Attributes                                 ***
    *******************************************************************************/

  private:
    
    /// Material of the component.
    class CoreMaterial* material_;
    /// Geometry of the component.
    class CoreGeometry* geometry_;

    /*******************************************************************************
    ***                              Private methods                             ***
    *******************************************************************************/


  };

}; /* SLX */

#endif
