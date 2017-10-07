/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

  

#include <Windows.h>
#include <string>
#include "silverlynx.h"
#include "core/geometry.h"
#include "core/material.h"


namespace SLX {
int32 main() {
  
  Window::Init(1024, 978);

  CoreGeometry geo;
  CoreMaterial mat;

  geo.init();
  mat.init();

  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());

  while (Window::IsOpened()) {
    Window::StartFrame();
    geo.render();
    // Render objects, etc.

    Window::EndFrame();
  }

  Window::Close();

  // Al usar un winmain, nos vemos obligados a usar una aplicacion de tipo win32 que no
  // tiene ventana de consola de comandos, asi que con esta funcion sera como hacer 
  // un printf pero los mensajes apareceran en la ventana OUTPUT del VISUAL PREMOH.
  OutputDebugString(textico);
  return 0;
}

}; /* SLX */
 
