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
#include "core/camera.h"
#include "core/material.h"
#include "core/geometry.h"
#include "core/input.h"


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
***                               Public methods                             ***
*******************************************************************************/

  ///--------------------------------------------------------------------------
  /// @fn    void init();
  ///
  /// @brief initializes the core attributes.
  ///--------------------------------------------------------------------------
  void init();

/*******************************************************************************
***                               Attributes                                 ***
*******************************************************************************/

  /// Core Window containing the main application window.
  CoreWindow window_;
  /// DirectX11 Framework.
  DirectXFramework d3d_;
  /// Chrome debugger.
  ChromeDebugger debugger_;
  /// Application start time. Used for timestamp purposes.
  uint64 start_time_;
  /// Main application camera.
  CoreCamera cam_;
  /// Application input module.
  CoreInput input_;
  /// Default material to be assigned to uninitialized 3DComponents.
  CoreMaterial default_material_;
  /// Default geometry to be assigned to uninitialized 3DComponents.
  CoreGeometry default_geometry_;

/*******************************************************************************
***                         Private Copy Constructor                         ***
*******************************************************************************/
 private:
  Core(const Core& copy);
  Core& operator=(const Core& copy);

}; /* CORE */

}; /* SLX */

#endif
