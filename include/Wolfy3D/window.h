/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __WOLFY3D_WINDOW_H__
#define __WOLFY3D_WINDOW_H__ 1

#include "Wolfy3D/globals.h"

namespace W3D {
namespace Window {

void Init(const int32 width = 800,
                const int32 height = 600,
                const bool mouse_cursor_visible = true,
                const char* display_name = "Silverlynx Window");
void Close();
bool IsOpened();
bool StartFrame(const float32 delta_seconds);
void EndFrame();
int32 Height();
int32 Width();

}; /* Window */
}; /* W3D */

#endif
