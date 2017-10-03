/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "core/core.h"

namespace SLX {

/*******************************************************************************
********************************************************************************
***                                                                          ***
***                                  CORE                                    ***
***                                                                          ***
********************************************************************************
*******************************************************************************/

/*******************************************************************************
***                       Constructor and destructor                         ***
*******************************************************************************/



Core& Core::instance() {
  static Core* singleton = new Core();
  return *singleton;
}

Core::Core() {}

Core::~Core() {}

};/* JI */
