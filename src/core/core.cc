/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/core.h"
#include <fstream>
#include <stdlib.h>
#include <process.h>
#include <thread>

namespace W3D {

/*******************************************************************************
***                             Chrome Debugger                              ***
*******************************************************************************/

ChromeDebugger::ChromeDebugger() {
  opened = false;
  file = nullptr;
}

void ChromeDebugger::StartChromeDebuggerFile() {

  fopen_s(&file, kChromeDebuggerJSonPath, "w");
  if (!file) {
    OutputDebugString(" ERROR: Cannot open chrome debugger file.");
    exit(EXIT_FAILURE);
  }

  fprintf(file, "{\n\t\"traceEvents\": [");

}

void ChromeDebugger::CloseChromeDebuggerFile() {

  fprintf(file, "\n\t]\n}");
  fclose(file);
  file = nullptr;
}

void ChromeDebugger::GenerateTextChromeDebuggerFile(DebuggerFileState state, 
                                                    const char* category_name,
                                                    const char* thread_name) {
  //std::unique_lock<std::mutex> lock(mutex);
  if (file) {
    int32 process_id = _getpid();
    std::thread::id thread_id = std::this_thread::get_id();
    char ph;
    if (state == kDebuggerFileState_Start) { ph = 'B'; }
    else { ph = 'E'; }

    if (opened) {
      fprintf(file, ",");
    }
    else {
      opened = true;
    }
    fprintf(file, "\n\t\t{ \"name\": \"%s\", ", thread_name);
    fprintf(file, "\"cat\": \"%s\", ", category_name);
    fprintf(file, "\"ph\": \"%c\", ", ph);
    fprintf(file, "\"ts\": %I64u, ", TimeInMicroSeconds());
    fprintf(file, "\"pid\": %d, ", process_id);
    fprintf(file, " \"tid\": %I64u }", thread_id);
  }
  //lock.unlock();
}


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

Core::Core() {
  
}

Core::~Core() {}


void Core::init() {
  error_geometry_.initCube();
  base_quad_geometry_.initQuad();
  error_texture_.initFromFile("../data/textures/error_texture.jpg");
  super_material_.init();
  super_sprite_.init();
}

};/* W3D */
