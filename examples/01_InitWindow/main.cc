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
#include "core/object.h"
#include "core/texture.h"
#include "imgui/imgui.h"

namespace SLX {
int32 main() {
  
  Window::Init(1024, 978);

  CoreGeometry geo, geo2;
  CoreMaterial mat;
  CoreTexture texture;

  geo.init();
  geo2.init("./../data/Heightmap.bmp", 10);
  mat.init();
  texture.load("./../data/texture.png");

  Object a, b;
  a.addComponent(ComponentType::Transform);
  a.addComponent(ComponentType::Render3D);
  a.render3D_->setup(&mat, &geo);
  a.render3D_->init();
  a.init();

  b.addComponent(ComponentType::Transform);
  b.addComponent(ComponentType::Render3D);
  b.render3D_->setup(&mat, &geo2);
  b.render3D_->init();
  b.init();

  char textico[256];
  sprintf_s(textico, "Iniciando ventana con dimensiones %d x %d", Window::Width(), Window::Height());
  auto& cam = Core::instance().cam_;

  float sin_value;

  // enter the main loop:
  while (Window::StartFrame() && Window::IsOpened()) {

    a.update();
    b.update();

    sin_value = DirectX::XMScalarSin((float)Time() * 0.001f);
    if (Input::IsMouseButtonDown(Input::kMouseButton_Left)) {
      OutputDebugString("MouseButton");
    }

    a.transform_->set_position(0.0f, sin_value, 0.0f);
    a.transform_->set_scale(sin_value, sin_value, sin_value);
    a.transform_->set_rotation(0.0f, (float)Time() * 0.01f, 0.0f);

    b.transform_->set_position(-5.0f, 0.0f, 0.0f);
    b.transform_->set_rotation(0.0f, (float)Time() * 0.01f, 0.0f);

    texture.use();
    cam.render(&a);
    cam.render(&b);

	ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	ImGui::ShowTestWindow(0);
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
