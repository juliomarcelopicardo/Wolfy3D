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

namespace W3D {

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


/*
MATERIAL ASSESMENT SUBCLASS
*/
class MaterialAssesment : public Material {

public:
  MaterialAssesment();
  ~MaterialAssesment();

  void setupSuperMaterial() override;

  class Texture* texture_materialmap_;
  class Texture* texture_grass_;
  class Texture* texture_moss_;
  class Texture* texture_asphalt_;

private:



  MaterialAssesment(const MaterialAssesment& copy);
  MaterialAssesment& operator=(const MaterialAssesment& copy);
};

}; /* W3D */

#endif
