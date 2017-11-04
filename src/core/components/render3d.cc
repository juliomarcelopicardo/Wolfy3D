/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "core/components/render3d.h"
#include "core/components/component.h"
#include "core/components/transform.h"
#include "core/geometry.h"
#include "core/material.h"
#include "core/object.h"
#include "core/core.h"

namespace SLX {

  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  Render3DComponent::Render3DComponent() : Component() {
    type_ = ComponentType::Render3D;

  }

  Render3DComponent::~Render3DComponent() {
	  material_ = nullptr;
	  geometry_ = nullptr;
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  void Render3DComponent::init() {

    if (!material_) {
      material_->init();
    }
    
    if (!geometry_) {
      geometry_->initTriangle();
    }

    if (material_ && geometry_) {
      initialized_ = true;
    }
  }

  void Render3DComponent::setup(CoreMaterial* mat, CoreGeometry* geo) {
    if (!initialized_) {
      init();
    }

    if (mat != nullptr) {
      material_ = mat;
    }

    if (geometry_ != nullptr) {
      geometry_ = geo;
    }
  }

  void Render3DComponent::update() {
    if (!initialized_) {
      init();
    }
  }

  void Render3DComponent::shutdown() {
    geometry_ = nullptr;
    material_ = nullptr;
  }

  void Render3DComponent::render(TransformComponent* transform) {
    if (initialized_) {
      auto* device_context = Core::instance().d3d_.deviceContext();
      auto& cam = Core::instance().cam_;

      DirectX::XMStoreFloat4x4(&material_->custom_constant_buffer_.matrices.model, transform->global_model_matrix());
      DirectX::XMStoreFloat4x4(&material_->custom_constant_buffer_.matrices.view, DirectX::XMMatrixTranspose(Core::instance().cam_.viewMatrix()));
      DirectX::XMStoreFloat4x4(&material_->custom_constant_buffer_.matrices.projection, DirectX::XMMatrixTranspose(Core::instance().cam_.projectionMatrix()));
      material_->custom_constant_buffer_.current_time = (float32)Time();
      material_->custom_constant_buffer_.padding = 0.0f;
      material_->custom_constant_buffer_.padding2 = 0.3f;
      material_->custom_constant_buffer_.padding3 = 0.6f;

      D3D11_MAPPED_SUBRESOURCE new_matrices;
      ZeroMemory(&new_matrices, sizeof(D3D11_MAPPED_SUBRESOURCE));
      device_context->Map(material_->matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &new_matrices);
      memcpy(new_matrices.pData, &material_->custom_constant_buffer_, sizeof(CustomConstantBuffer));
      device_context->Unmap(material_->matrix_buffer_, 0);

      uint32 stride = sizeof(VertexData);
      uint32 offset = 0;

      device_context->IASetVertexBuffers(0, 1, &geometry_->vertex_buffer_, &stride, &offset);
      device_context->IASetIndexBuffer(geometry_->vertex_index_buffer_, DXGI_FORMAT_R32_UINT, 0);
      device_context->IASetPrimitiveTopology(geometry_->topology_);
      device_context->VSSetShader(material_->vertex_shader_, 0, 0);
      device_context->PSSetShader(material_->pixel_shader_, 0, 0);
      device_context->VSSetConstantBuffers(0, 1, &material_->matrix_buffer_);
      device_context->PSSetConstantBuffers(0, 1, &material_->matrix_buffer_);
      device_context->IASetInputLayout(material_->input_layout_);
      device_context->DrawIndexed(geometry_->vertex_index_.size(), 0, 0);
    }
  }

  /*******************************************************************************
  ***                              Private methods                             ***
  *******************************************************************************/


}; /* SLX */
