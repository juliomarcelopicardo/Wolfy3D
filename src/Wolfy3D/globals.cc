/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
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

W3D::int32 WINAPI WinMain(HINSTANCE hInstance,
                          HINSTANCE hPrevInstance,
                          LPSTR lpCmdLine,
                          W3D::int32 nCmdShow) {

  auto& core = W3D::Core::instance();

  // Determinamos el tiempo inicial y abrimos el fichero del debugger.
  core.start_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  core.debugger_.StartChromeDebuggerFile();

  // guardamos los datos de la ventana(instancia) que nos facilita windows. 
  core.window_.instance_handle_ = hInstance;
  core.window_.nCmdShow = nCmdShow;

  // Ejemplo absurdo para ver cuanto dura el main.
  core.debugger_.GenerateTextChromeDebuggerFile(W3D::kDebuggerFileState_Start, "Categoria", "Hilo principal");
  W3D::int32 main_return = W3D::main();
  core.debugger_.GenerateTextChromeDebuggerFile(W3D::kDebuggerFileState_End, "Categoria", "Hilo principal");

  core.debugger_.CloseChromeDebuggerFile(); // Cerramos el fichero del debugger.
  return main_return;
}

#pragma endregion 
