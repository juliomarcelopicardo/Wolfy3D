/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/geo.h"
#include "Wolfy3D/sprite.h"
#include "core/core.h"

namespace W3D {


/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Sprite::Sprite() {
  position_ = { 0.0f, 0.0f };
  size_ = { 100.0f, 100.0f };
  rotation_ = 0.0f;
  texture_ = nullptr;
  pivot_ = kPivotPoint_Center;
}

Sprite::~Sprite() {}

Sprite& Sprite::operator=(const Sprite& other) {
  position_ = other.position_;
  size_ = other.size_;
  rotation_ = other.rotation_;
  texture_ = other.texture_;
  pivot_ = other.pivot_;
  return *this;
}

Sprite::Sprite(const Sprite& other) {
  position_ = other.position_;
  size_ = other.size_;
  rotation_ = other.rotation_;
  texture_ = other.texture_;
  pivot_ = other.pivot_;
}

/*******************************************************************************
***                              Public Methods                              ***
*******************************************************************************/

void Sprite::render() {
  Core::instance().super_sprite_.render(this);
}

/*******************************************************************************
***                              Public Setters                              ***
*******************************************************************************/

void Sprite::set_texture(Texture2D* texture){
  texture_ = texture;
}

void Sprite::set_position(const DirectX::XMFLOAT2 position) {
  position_ = position;
}

void Sprite::set_size(const DirectX::XMFLOAT2 size) {
  size_ = size;
}

void Sprite::set_rotation(const float radians) {
  rotation_ = radians;
}

void Sprite::set_pivot(const PivotPoint pivot) {
  pivot_ = pivot;
}

/*******************************************************************************
***                              Public Getters                              ***
*******************************************************************************/

Texture2D* Sprite::texture() {
  return texture_;
}

const DirectX::XMFLOAT2 Sprite::size() {
  return size_;
}

const float Sprite::rotation() {
  return rotation_;
}

const DirectX::XMFLOAT2 Sprite::position() {
  return position_;
}

const Sprite::PivotPoint Sprite::pivot() {
  return pivot_;
}


}; /* W3D */
