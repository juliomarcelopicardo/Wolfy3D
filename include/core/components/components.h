/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __COMPONENTS_H__
#define __COMPONENTS_H__ 1

#include "silverlynx.h"
#include "components/transform.h"

namespace SLX {

  enum class ComponentType {
    Transform
  };

  union Component {
    TransformComponent transform;
  };

  struct Components {
    ComponentType type;
    Component cmp;
  };

}; /* SLX */

#endif
