/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
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
#include "d3d.h"
#include <stdio.h>
#include "core/material.h"
#include "core/geometry.h"


namespace SLX {


/*******************************************************************************
***                             Chrome Debugger                              ***
*******************************************************************************/
const char kChromeDebuggerJSonPath[] = "./../build/chrome_debugger.json";

const enum DebuggerFileState {
  kDebuggerFileState_Start = 0,
  kDebuggerFileState_End = 1,
};

struct ChromeDebugger {
  ChromeDebugger();

  void StartChromeDebuggerFile();
  void CloseChromeDebuggerFile();
  void GenerateTextChromeDebuggerFile(DebuggerFileState state, 
                                      const char* category_name,
                                      const char* thread_name);

  FILE* file;
  //std::mutex mutex;
  bool opened;
};



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

  CoreWindow window_;
  DirectXFramework d3d_;
  ChromeDebugger debugger_;


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
