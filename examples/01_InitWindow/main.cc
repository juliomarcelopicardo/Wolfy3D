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


namespace SLX {
int32 main() {
  
  Window::Init(1024, 978);

  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());

  while (1) {
    Window::StartFrame();

    // Render objects, etc.

    Window::EndFrame();
  }

  Window::Close();

  OutputDebugString(textico);
  return 0;
}

}; /* SLX */
 
