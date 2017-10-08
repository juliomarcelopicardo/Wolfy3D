/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

 
#include <string>
#include "silverlynx.h"
#include "core/geometry.h"
#include "core/material.h"
#include "core/core.h"

namespace SLX {
int32 main() {
  
  Window::Init(1024, 978);

  CoreGeometry geo, geo2;
  CoreMaterial mat;

  geo.init();
  geo2.init();
  mat.init();

  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());


  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened()) {

    geo.render(&mat, 0);
    geo.render(&mat, 1);

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
 
