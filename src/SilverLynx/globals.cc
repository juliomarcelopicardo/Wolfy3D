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

  // Al usar un winmain, nos vemos obligados a usar una aplicacion de tipo win32 que no
  // tiene ventana de consola de comandos, asi que con esta funcion sera como hacer 
  // un printf pero los mensajes apareceran en la ventana OUTPUT del VISUAL PREMOH.
  OutputDebugString(" Ejecutando el MAIN PRINCIPAL");

  auto& core = SLX::Core::instance();

  // guardamos los datos de la ventana(instancia) que nos facilita windows. 
  core.window_.instance_handle_ = hInstance;
  core.window_.nCmdShow = nCmdShow;

  //SLX::Core::instance().start_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  return SLX::main();
}

#pragma endregion 
