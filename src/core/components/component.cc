/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "core/object.h"
#include "core/components/component.h"

namespace SLX {

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/


  Component::Component() {
    type_ = ComponentType::None;
    initialized_ = false;
    owner_ = nullptr;
  }

  Component::~Component() {
    owner_ = nullptr;
  }

  void Component::set_owner(Object* object) {
    owner_ = object;
  }
}; /* SLX */
