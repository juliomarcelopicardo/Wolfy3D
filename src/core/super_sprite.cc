﻿/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/globals.h"
#include "core/super_sprite.h"
#include "core/core.h"
#include "DirectXMath.h"

namespace W3D {

  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

SuperSprite::SuperSprite() {}

SuperSprite::~SuperSprite() {}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/


void SuperSprite::init() {
  calculateOrthographicMatrix();
  material_.set_light_sensitivity(false);
  material_.set_texture(&Core::instance().error_texture_);
}


void SuperSprite::render() {

  auto& core = Core::instance();
  auto* device_context = core.d3d_.deviceContext();
  auto& super_mat = core.super_material_;
  Geo* geometry = core.geometry_factory_[core.base_quad_geometry_.id()];


  // Transform.
  DirectX::XMMATRIX rot, tr, sc;
  rot = DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 1.0f);  tr = DirectX::XMMatrixTranslation(200.0f, 200.0f, 0.0f);  sc = DirectX::XMMatrixScaling(100.0f, 100.0f, 1.0);
  // Saving all the matrices and common data of the super material.
  DirectX::XMStoreFloat4x4(&super_mat.settings_.matrices.model, DirectX::XMMatrixTranspose(sc * rot * tr));
  DirectX::XMStoreFloat4x4(&super_mat.settings_.matrices.view, DirectX::XMMatrixIdentity());
  DirectX::XMStoreFloat4x4(&super_mat.settings_.matrices.projection, DirectX::XMMatrixTranspose(ortho_matrix()));
  super_mat.settings_.time = (float32)Time();

  // Setup the super material depending on the type of user's material associated.
  material_.setupSuperMaterial();

  // Allocating the constant buffer used in the material.
  D3D11_MAPPED_SUBRESOURCE shader_constant_buffer;
  ZeroMemory(&shader_constant_buffer, sizeof(D3D11_MAPPED_SUBRESOURCE));
  device_context->Map(super_mat.buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &shader_constant_buffer);
  memcpy(shader_constant_buffer.pData, &super_mat.settings_, sizeof(MaterialSettings));
  device_context->Unmap(super_mat.buffer_, 0);

  uint32 stride = sizeof(Geo::VertexData);
  uint32 offset = 0;

  // Setup the render.
  device_context->IASetVertexBuffers(0, 1, &geometry->vertex_buffer_, &stride, &offset);
  device_context->IASetIndexBuffer(geometry->vertex_index_buffer_, DXGI_FORMAT_R32_UINT, 0);
  device_context->IASetPrimitiveTopology(geometry->topology_);
  device_context->VSSetShader(super_mat.vertex_shader_, 0, 0);
  device_context->PSSetShader(super_mat.pixel_shader_, 0, 0);
  device_context->VSSetConstantBuffers(0, 1, &super_mat.buffer_);
  device_context->PSSetConstantBuffers(0, 1, &super_mat.buffer_);
  device_context->IASetInputLayout(super_mat.input_layout_);
  device_context->DrawIndexed(geometry->vertex_index_.size(), 0, 0);
}


void SuperSprite::calculateOrthographicMatrix() {
  DirectX::XMMATRIX m;
  m = DirectX::XMMatrixOrthographicOffCenterLH(0.0f,
                                               (float32)Window::Width(),
                                               (float32)Window::Height(),
                                               0.0f, 
                                               -1.0f, 
                                               1.0f);
  DirectX::XMStoreFloat4x4(&ortho_matrix_, m);
}


/*******************************************************************************
***                           Setters & Getters                              ***
*******************************************************************************/

DirectX::XMMATRIX SuperSprite::ortho_matrix() {
  return DirectX::XMLoadFloat4x4(&ortho_matrix_);
}


}; /* W3D */
