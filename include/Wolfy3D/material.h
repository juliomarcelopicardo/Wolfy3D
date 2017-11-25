/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#ifndef __WOLFY3D_MATERIAL_H__
#define __WOLFY3D_MATERIAL_H__ 1

#include "Wolfy3D/globals.h"
#include "core/texture.h"
#include <DirectXMath.h>

namespace W3D {

/* 
  MATERIAL INTERFACE
*/
class Material {

 public: 
  Material();
  ~Material();

  virtual void setupSuperMaterial() = 0;
  void set_light_sensitivity(const bool is_light_sensitive);

 protected:

  uint32 is_light_sensitive_;
 
 private:

  Material(const Material& copy);
  Material& operator=(const Material& copy);
};


/*
  MATERIAL TEXTURE SUBCLASS
*/
class MaterialTextured: public Material {

public:
  MaterialTextured();
  ~MaterialTextured();

  void setupSuperMaterial() override;
  void set_texture(class Texture* texture);

private:

  // Se borrara cuando se cree la capa de usuario para texturas.
  class Texture* texture_;


  MaterialTextured(const MaterialTextured& copy);
  MaterialTextured& operator=(const MaterialTextured& copy);
};

/*
MATERIAL DIFFUSE SUBCLASS
*/
class MaterialDiffuse : public Material {

public:
  MaterialDiffuse();
  ~MaterialDiffuse();

  void setupSuperMaterial() override;
  void set_color(const DirectX::XMFLOAT4& color);
  void set_color(const float32 r, 
                 const float32 g, 
                 const float32 b, 
                 const float32 a = 1.0f);

private:

  DirectX::XMFLOAT4 color;

  MaterialDiffuse(const MaterialDiffuse& copy);
  MaterialDiffuse& operator=(const MaterialDiffuse& copy);
};

/*
MATERIAL NORMALS SUBCLASS
*/
class MaterialNormals : public Material {

public:
  MaterialNormals();
  ~MaterialNormals();

  void setupSuperMaterial() override;

private:

  MaterialNormals(const MaterialNormals& copy);
  MaterialNormals& operator=(const MaterialNormals& copy);
};


/*
MATERIAL TERRAIN SUBCLASS
*/
class MaterialTerrain : public Material {

public:
  MaterialTerrain();
  ~MaterialTerrain();

  void setupSuperMaterial() override;

  Texture* texture_materialmap_;
  Texture* texture_grass_;
  Texture* texture_moss_;
  Texture* texture_asphalt_;

private:



  MaterialTerrain(const MaterialTerrain& copy);
  MaterialTerrain& operator=(const MaterialTerrain& copy);
};




}; /* W3D */

#endif
