/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserveds.
 *
 *  @project SilverLynx
 *  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
 *           Antonio Diaz <antoniozero@outlook.com>
 *
 */

#ifndef __SILVERLYNX_CORE_H__
#define __SILVERLYNX_CORE_H__ 1

#include "silverlynx.h"
#include "window.h"
#include <stdio.h>


namespace SLX {

/*******************************************************************************
********************************************************************************
***                                                                          ***
***                         SILVERLYNX CORE CLASS                            ***
***                                                                          ***
********************************************************************************
*******************************************************************************/

class Core {

 public:

  /// Singleton instance.
  static Core& instance();
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/
  Core();
  ~Core();

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  Window window_;

  uint64 start_time_;





/*******************************************************************************
***                         Private Copy Constructor                         ***
*******************************************************************************/
 private:
  Core(const Core& copy);
  Core& operator=(const Core& copy);

}; /* CORE */

}; /* SLX */

#endif
