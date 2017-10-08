/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __SILVERLYNX_WINDOW_H__
#define __SILVERLYNX_WINDOW_H__ 1

#include "SilverLynx/globals.h"

namespace SLX {
namespace Window {

void Init(const int32 width = 800,
                const int32 height = 600,
                const bool mouse_cursor_visible = true,
                const char* display_name = "Silverlynx Window");
void Close();
void InitMaximized(const bool full_screen_mode = false,
                         const bool mouse_cursor_visible = true,
                         const char* title = "Silverlynx Window");
void InitByLua(const char* lua_path);
bool IsOpened();
bool StartFrame();
void EndFrame();
void Clear(float red = 0.0f, float green = 0.3f, float blue = 0.0f);
void Destroy();
void SetMouseVisibility(const bool visible);
int32 Height();
int32 Width();

}; /* Window */
}; /* SLX */

#endif
