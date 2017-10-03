/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserveds.
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



namespace SLX {

/*******************************************************************************
********************************************************************************
***                                                                          ***
***                                  UTILS                                   ***
***                                                                          ***
********************************************************************************
*******************************************************************************/

#pragma region UTILS

uint64 Time() {
  return (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - Core::instance().start_time_);
}

uint64 TimeInMicroSeconds() {
  return (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() - Core::instance().start_time_);
}

void Sleep(const uint64 miliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

void SleepSeconds(const uint64 seconds) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


void Chronometer::start() {
  timer = Time();
}

void Chronometer::restart() {
  timer = 0;
  total_average = 0;
  iterations = 0;
}

uint64 Chronometer::end() {
  uint64 result = Time() - timer;
  total_average += result;
  iterations += 1;
  return result;
}

uint64 Chronometer::average() {
  if (!iterations) { return 0; }
  else {
    return total_average / iterations;
  }
}

#pragma endregion


/*******************************************************************************
********************************************************************************
***                                                                          ***
***                                  UTILS                                   ***
***                                                                          ***
********************************************************************************
*******************************************************************************/

#pragma region WINDOW

void WindowInit(const int32 width, 
                const int32 height, 
	        			const bool mouse_cursor_visible, 
                const char* display_name) {
  
  Core::instance().window_.init(width, height, display_name);
}

#pragma endregion


int32 WindowHeight() {
  return Core::instance().window_.height_;
}

int32 WindowWidth() {
  return Core::instance().window_.width_;
}

}; /* SLX */
