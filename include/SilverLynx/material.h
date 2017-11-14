/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#ifndef __SILVERLYNX_MATERIAL_H__
#define __SILVERLYNX_MATERIAL_H__ 1

#include "SilverLynx/globals.h"
#include "core/texture.h"

namespace SLX {

/* 
  MATERIAL INTERFACE
*/
class Material {

 public: 
  Material();
  ~Material();

  virtual void setupSuperMaterial() = 0;

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
  void set_texture(class CoreTexture* texture);

private:

  // Se borrara cuando se cree la capa de usuario para texturas.
  class CoreTexture* texture_;


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

private:

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

}; /* SLX */

#endif
