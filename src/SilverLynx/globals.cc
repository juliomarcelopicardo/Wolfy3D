/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <chrono>
#include <time.h>
#include "core/window.h"
#include "core/core.h"


/*******************************************************************************
********************************************************************************
***                                                                          ***
***                              MAIN FUNCTION                               ***
***                                                                          ***
********************************************************************************
*******************************************************************************/

#pragma region MAIN

SLX::int32 WINAPI WinMain(HINSTANCE hInstance,
                          HINSTANCE hPrevInstance,
                          LPSTR lpCmdLine,
                          SLX::int32 nCmdShow) {

  auto& core = SLX::Core::instance();

  // Determinamos el tiempo inicial y abrimos el fichero del debugger.
  core.start_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  core.debugger_.StartChromeDebuggerFile();

  // guardamos los datos de la ventana(instancia) que nos facilita windows. 
  core.window_.instance_handle_ = hInstance;
  core.window_.nCmdShow = nCmdShow;

  // Ejemplo absurdo para ver cuanto dura el main.
  core.debugger_.GenerateTextChromeDebuggerFile(SLX::kDebuggerFileState_Start, "Categoria", "Hilo principal");
  SLX::int32 main_return = SLX::main();
  core.debugger_.GenerateTextChromeDebuggerFile(SLX::kDebuggerFileState_End, "Categoria", "Hilo principal");

  core.debugger_.CloseChromeDebuggerFile(); // Cerramos el fichero del debugger.
  return main_return;
}

#pragma endregion 
