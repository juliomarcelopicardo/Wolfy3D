/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "core/window.h"
#include "core/core.h"

namespace SLX {
namespace Window {

void Init(const int32 width,
                const int32 height,
                const bool mouse_cursor_visible,
                const char* display_name) {

  Core::instance().window_.init(width, height, display_name);
  Core::instance().d3d_.init();
}

void Close() {
  Core::instance().d3d_.shutdown();
}

void StartFrame() {
  Core::instance().window_.updateMessages();
  Core::instance().d3d_.startRenderFrame();
}

void EndFrame() {
  Core::instance().d3d_.endRenderFrame();
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
}; /* SLX */
