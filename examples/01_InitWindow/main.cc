/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserveds.
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
  
  WindowInit(1024, 978);

  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", WindowWidth(), WindowHeight());

  OutputDebugString(textico);
  return 0;
}

}; /* SLX */
 
