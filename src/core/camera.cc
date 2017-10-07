/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "core/geometry.h"
#include "core/core.h"
#include "core/window.h"

namespace SLX {

  
  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  CoreGeometry::CoreGeometry() {
    
  }

  CoreGeometry::~CoreGeometry() {
    vertex_index_.clear();
    vertex_position_.clear();
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  bool CoreGeometry::init() {

    // QUAD de ejemplo
    int32 num_vertices = 4;
    int32 num_indices = 6;

    // Rellenamos info de vertices e indices.
    vertex_position_.resize(num_vertices);
    vertex_index_.resize(num_indices);

    vertex_position_[0] = { -1.0f, -1.0f, 0.0f };
    vertex_position_[1] = { 1.0f, -1.0f, 0.0f };
    vertex_position_[2] = { -1.0f, 1.0f, 0.0f };
    vertex_position_[3] = { 1.0f, 1.0f, 0.0f };

    vertex_index_[0] = 0;
    vertex_index_[1] = 1;
    vertex_index_[2] = 2;
    vertex_index_[3] = 2;
    vertex_index_[4] = 1;
    vertex_index_[5] = 3;

    // Creamos un buffer para subir la informacion de los vertices a la grafica.
    D3D11_BUFFER_DESC vertex_description;
    ZeroMemory(&vertex_description, sizeof(D3D11_BUFFER_DESC));

    vertex_description.Usage = D3D11_USAGE_DEFAULT;
    vertex_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_description.ByteWidth = sizeof(D3DXVECTOR3) * num_vertices;

    D3D11_SUBRESOURCE_DATA vertex_data;
    ZeroMemory(&vertex_data, sizeof(D3D11_SUBRESOURCE_DATA));
    vertex_data.pSysMem = vertex_position_.data();

    HRESULT result = Core::instance().d3d_.device()->CreateBuffer(&vertex_description, &vertex_data, &vertex_buffer_);

    if (FAILED(result)) {
      MessageBox(NULL, "ERROR - Vertex buffer not created", "ERROR", MB_OK);
      return false;
    }

    // Creamos un buffer para subir la informacion de los indices a la grafica.
    D3D11_BUFFER_DESC index_description;
    ZeroMemory(&index_description, sizeof(D3D11_BUFFER_DESC));

    index_description.Usage = D3D11_USAGE_DEFAULT;
    index_description.BindFlags = D3D11_BIND_INDEX_BUFFER;
    index_description.ByteWidth = sizeof(uint32) * num_indices;

    D3D11_SUBRESOURCE_DATA index_data;
    ZeroMemory(&index_data, sizeof(D3D11_SUBRESOURCE_DATA));
    index_data.pSysMem = vertex_index_.data();

    result = Core::instance().d3d_.device()->CreateBuffer(&index_description, &index_data, &vertex_index_buffer_);

    if (FAILED(result)) {
      MessageBox(NULL, "ERROR - Vertex buffer not created", "ERROR", MB_OK);
      return false;
    }

    return true;
  }

  void CoreGeometry::render() {

    auto& window = Core::instance().window_;
    auto* device_context = Core::instance().d3d_.deviceContext();

    D3DXVECTOR3 camera_position = { 0.0, 5.0, -10.0 };
    D3DXVECTOR3 camera_look_at = { 0.0, 0.0, 0.0 };
    D3DXVECTOR3 camera_up = { 0.0f, 1.0f, 0.0f };
    D3DXMATRIX model, view, projection;

    D3DXMATRIX scale, rotate, translate, result, identity;

    D3DXMatrixScaling(&scale, 0.02f, .02f, .02f);
    D3DXMatrixRotationYawPitchRoll(&rotate, 0.0f, 0.0f, 0.0f);
    D3DXMatrixTranslation(&translate, 0.0f, 0.0f, 0.0f);
    result = scale * rotate * translate;

    D3DXMatrixTranspose(&model, &result);

    D3DXMatrixLookAtLH(&view, &camera_position, &camera_look_at, &camera_up);
    D3DXMatrixTranspose(&view, &view);

    D3DXMatrixPerspectiveFovLH(&projection, D3DXToRadian(45.0f), window.width_ / window.height_, 0.01f, 100.0f);
    D3DXMatrixTranspose(&projection, &projection);

    D3D11_MAPPED_SUBRESOURCE new_matrices;
   // ZeroMemory(&new_matrices, sizeof(D3D11_MAPPED_SUBRESOURCE));
    //device_context->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &new_matrices);
   // memcpy(new_matrices.pData, &matrix_data_, sizeof(matrix_data_));
   // device_context->Unmap(matrix_buffer_, 0);

    unsigned int stride = sizeof(D3DXVECTOR3);
    unsigned int offset = 0;

    device_context->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
    device_context->IASetIndexBuffer(vertex_index_buffer_, DXGI_FORMAT_R32_UINT, 0);
    device_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //device_context->VSSetShader(vertex_shader_, 0, 0);
    //device_context->PSSetShader(pixel_shader_, 0, 0);
    //device_context->VSSetConstantBuffers(0, 1, &matrix_buffer_);
    //device_context->IASetInputLayout(input_layout_);
    device_context->DrawIndexed(vertex_index_.size(), 0, 0);
  }




}; /* SLX */
