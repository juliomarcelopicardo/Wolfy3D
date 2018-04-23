/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "core/components/render.h"
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

void RenderComponent::init(Material* mat, Geometry* geo) {
  material_ = mat;
  geometry_ = geo;
  if (!geo) { geometry_ = &Core::instance().error_geometry_; }
  if (mat) { initialized_ = true; }
}

void RenderComponent::render(TransformComponent* transform) {
  if (initialized_) {
      
    auto& camera = Core::instance().cam_;
    auto& super_mat = Core::instance().super_material_;

    // Saving all the matrices and common data of the super material.
    DirectX::XMStoreFloat4x4(&super_mat.settings_.matrices.model, transform->global_model_matrix());
    DirectX::XMStoreFloat4x4(&super_mat.settings_.matrices.view, DirectX::XMMatrixTranspose(camera.view_matrix()));
    DirectX::XMStoreFloat4x4(&super_mat.settings_.matrices.projection, DirectX::XMMatrixTranspose(camera.projection_matrix()));
    super_mat.settings_.time = (float32)Time();
    // Setup the super material depending on the type of user's material associated.
    material_->setupSuperMaterial();
    // Preparing the device context to draw.
    setupDeviceContext();
      
  }
}

/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

void RenderComponent::setupDeviceContext() {
  auto& core = Core::instance();
  auto* device_context = core.d3d_.deviceContext();
  auto& super_mat = core.super_material_;
  Geo* geometry = core.geometry_factory_[geometry_->id()];

  D3D11_MAPPED_SUBRESOURCE shader_constant_buffer;
  ZeroMemory(&shader_constant_buffer, sizeof(D3D11_MAPPED_SUBRESOURCE));
  device_context->Map(super_mat.buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &shader_constant_buffer);
  memcpy(shader_constant_buffer.pData, &super_mat.settings_, sizeof(MaterialSettings));
  device_context->Unmap(super_mat.buffer_, 0);

  uint32 stride = sizeof(Geo::VertexData);
  uint32 offset = 0;

  device_context->OMSetBlendState(core.d3d_.blendState(), 0, 0xffffffff);
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

}; /* W3D */
