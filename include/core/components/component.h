/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__ 1

#include "SilverLynx/globals.h"

namespace SLX {

class Component {

 public:

   /// Public owner setter, to set the object which will possess the component.
   void set_owner(class Object* object);

  protected :

    /*******************************************************************************
    ***                               Attributes                                 ***
    *******************************************************************************/

    /// Type of this component.
    ComponentType type_;
    /// Whether this component have been initialized or not.
    bool initialized_;
    /// Object who possess the component.
    class Object* owner_;

    /*******************************************************************************
    ***                        Constructor and destructor                        ***
    *******************************************************************************/
    
    /// Default class constructor.
    Component::Component();
    /// Default class destructor.
    Component::~Component();

    /*******************************************************************************
    ***                               Virtual methods                            ***
    *******************************************************************************/
    
    ///--------------------------------------------------------------------------
    /// @fn   virtual void init() = 0;
    ///
    /// @brief  Initializes the component.
    ///--------------------------------------------------------------------------
    virtual void init() = 0;

    ///--------------------------------------------------------------------------
    /// @fn   virtual void update() = 0;
    ///
    /// @brief  Updates the component.
    ///--------------------------------------------------------------------------
    virtual void update() = 0;

    ///--------------------------------------------------------------------------
    /// @fn   virtual void shutdown();
    ///
    /// @brief  Deallocates any memory and setup from this component.
    ///--------------------------------------------------------------------------
    virtual void shutdown() = 0;

  };

}; /* SLX */

#endif
