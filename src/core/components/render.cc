﻿/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/components/render.h"
#include "core/components/transform.h"
#include "core/geo.h"
#include "core/super_material.h"
#include "core/entity.h"
#include "core/core.h"


namespace W3D {

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  RenderComponent::RenderComponent() {
    initialized_ = false;
  }

  RenderComponent::~RenderComponent() {
	  material_ = nullptr;
	  geometry_ = nullptr;
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  void RenderComponent::init(Material* mat, Geo* geo) {
    material_ = mat;
    geometry_ = geo;
    if (!geo) { geometry_ = &Core::instance().error_geometry_; }
    if (mat) { initialized_ = true; }
  }

  void RenderComponent::render(TransformComponent* transform) {
    if (initialized_) {
      auto* device_context = Core::instance().d3d_.deviceContext();
      auto& camera = Core::instance().cam_;
      auto& super_mat = Core::instance().super_material_;

      // Saving all the matrices and common data of the super material.
      DirectX::XMStoreFloat4x4(&super_mat.params_.matrices.model, transform->global_model_matrix());
      DirectX::XMStoreFloat4x4(&super_mat.params_.matrices.view, DirectX::XMMatrixTranspose(camera.viewMatrix()));
      DirectX::XMStoreFloat4x4(&super_mat.params_.matrices.projection, DirectX::XMMatrixTranspose(camera.projectionMatrix()));
      super_mat.params_.time = (float32)Time();
      // Setup the super material depending on the type of user's material associated.
      material_->setupSuperMaterial();
      //super_mat.params_.padding = 0.0f;
      //super_mat.params_.padding2 = 0.3f;

      D3D11_MAPPED_SUBRESOURCE new_buffer;
      ZeroMemory(&new_buffer, sizeof(D3D11_MAPPED_SUBRESOURCE));
      device_context->Map(super_mat.matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &new_buffer);
      memcpy(new_buffer.pData, &super_mat.params_, sizeof(MaterialParams));
      device_context->Unmap(super_mat.matrix_buffer_, 0);

      uint32 stride = sizeof(VertexData);
      uint32 offset = 0;

      device_context->IASetVertexBuffers(0, 1, &geometry_->vertex_buffer_, &stride, &offset);
      device_context->IASetIndexBuffer(geometry_->vertex_index_buffer_, DXGI_FORMAT_R32_UINT, 0);
      device_context->IASetPrimitiveTopology(geometry_->topology_);
      device_context->VSSetShader(super_mat.vertex_shader_, 0, 0);
      device_context->PSSetShader(super_mat.pixel_shader_, 0, 0);
      device_context->VSSetConstantBuffers(0, 1, &super_mat.matrix_buffer_);
      device_context->PSSetConstantBuffers(0, 1, &super_mat.matrix_buffer_);
      device_context->IASetInputLayout(super_mat.input_layout_);
      device_context->DrawIndexed(geometry_->vertex_index_.size(), 0, 0);
    }
  }

  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/


}; /* W3D */