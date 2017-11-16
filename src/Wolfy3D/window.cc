/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/wnd.h"
#include "core/core.h"

namespace W3D {
namespace Window {

void Init(const int32 width,
                const int32 height,
                const bool mouse_cursor_visible,
                const char* display_name) {

  Core::instance().window_.init(width, height, display_name);
}

void Close() {
	Core::instance().window_.shutdown();
}

bool StartFrame() {
  return Core::instance().window_.startFrame();
}

void EndFrame() {
  Core::instance().window_.endFrame();
}

int32 Height() {
  return Core::instance().window_.height_;
}

int32 Width() {
  return Core::instance().window_.width_;
}

bool IsOpened() {
  return Core::instance().window_.is_opened_;
}

}; /* Window */
}; /* W3D */
