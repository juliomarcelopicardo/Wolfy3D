/** Copyright Julio Picardo and Antonio Diaz. SouthBros 2017-18, all rights reserved.
*
*  @project SilverLynx
*  @authors Julio Marcelo Picardo <picardope@esat-alumni.com>
*           Antonio Diaz <antoniozero@outlook.com>
*
*/

#include "SilverLynx/globals.h"
#include "SilverLynx/time.h"
#include "core/geometry.h"
#include "core/core.h"
#include "core/camera.h"
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
    if (vertex_buffer_) { vertex_buffer_->Release(); }
    if (vertex_index_buffer_) { vertex_index_buffer_->Release(); }
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  bool CoreGeometry::init() {



    // QUAD de ejemplo
    int32 num_vertices = 24;
    int32 num_indices = 36;

    // Rellenamos info de vertices e indices.
    vertex_position_.resize(num_vertices);
    vertex_index_.resize(num_indices);

    vertex_position_[0] = { -0.5f, 0.5f, -0.5f };
    vertex_position_[1] = { 0.5f, 0.5f, -0.5f };
    vertex_position_[2] = { -0.5f, -0.5f, -0.5f };
    vertex_position_[3] = { 0.5f, -0.5f, -0.5f };

    vertex_position_[4] = { -0.5f, 0.5f, 0.5f };
    vertex_position_[5] = { 0.5f, 0.5f, 0.5f };
    vertex_position_[6] = { -0.5f, -0.5f, 0.5f };
    vertex_position_[7] = { 0.5f, -0.5f, 0.5f };

    vertex_position_[8] = { -0.5f, 0.5f, -0.5f };
    vertex_position_[9] = { -0.5f, -0.5f, -0.5f };
    vertex_position_[10] = { -0.5f, 0.5f, 0.5f };
    vertex_position_[11] = { -0.5f, -0.5f, 0.5f };

    vertex_position_[12] = { 0.5f, 0.5f, -0.5f };
    vertex_position_[13] = { 0.5f, -0.5f, -0.5f };
    vertex_position_[14] = { 0.5f, 0.5f, 0.5f };
    vertex_position_[15] = { 0.5f, -0.5f, 0.5f };

    vertex_position_[16] = { -0.5f, -0.5f, -0.5f };
    vertex_position_[17] = { -0.5f, -0.5f, 0.5f };
    vertex_position_[18] = { 0.5f, -0.5f, -0.5f };
    vertex_position_[19] = { 0.5f, -0.5f, 0.5f };

    vertex_position_[20] = { -0.5f, 0.5f, 0.5f };
    vertex_position_[21] = { -0.5f, 0.5f, -0.5f };
    vertex_position_[22] = { 0.5f, 0.5f, 0.5f };
    vertex_position_[23] = { 0.5f, 0.5f, -0.5f };

    vertex_index_[0] = 0;
    vertex_index_[1] = 2;
    vertex_index_[2] = 3;
    vertex_index_[3] = 0;
    vertex_index_[4] = 3;
    vertex_index_[5] = 1;
    vertex_index_[6] = 5;
    vertex_index_[7] = 7;
    vertex_index_[8] = 6;
    vertex_index_[9] = 5;
    vertex_index_[10] = 6;
    vertex_index_[11] = 4;
    vertex_index_[12] = 10;
    vertex_index_[13] = 11;
    vertex_index_[14] = 9;
    vertex_index_[15] = 9;
    vertex_index_[16] = 8;
    vertex_index_[17] = 10;
    vertex_index_[18] = 12;
    vertex_index_[19] = 13;
    vertex_index_[20] = 15;
    vertex_index_[21] = 12;
    vertex_index_[22] = 15;
    vertex_index_[23] = 14;
    vertex_index_[24] = 16;
    vertex_index_[25] = 17;
    vertex_index_[26] = 19;
    vertex_index_[27] = 16;
    vertex_index_[28] = 19;
    vertex_index_[29] = 18;
    vertex_index_[30] = 20;
    vertex_index_[31] = 21;
    vertex_index_[32] = 23;
    vertex_index_[33] = 20;
    vertex_index_[34] = 23;
    vertex_index_[35] = 22;

    // Creamos un buffer para subir la informacion de los vertices a la grafica.
    D3D11_BUFFER_DESC vertex_description;
    ZeroMemory(&vertex_description, sizeof(D3D11_BUFFER_DESC));

    vertex_description.Usage = D3D11_USAGE_DEFAULT;
    vertex_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertex_description.ByteWidth = sizeof(DirectX::XMFLOAT3) * num_vertices;

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

    // Creamos un buffer para almacenar las matrices.
    D3D11_BUFFER_DESC matrix_description;
    ZeroMemory(&matrix_description, sizeof(D3D11_BUFFER_DESC));

    matrix_description.Usage = D3D11_USAGE_DYNAMIC;
    matrix_description.ByteWidth = sizeof(DirectX::XMFLOAT4X4) * 3;
    matrix_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    matrix_description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    result = Core::instance().d3d_.device()->CreateBuffer(&matrix_description, NULL, &matrix_buffer_);

    if (FAILED(result)) {
      MessageBox(NULL, "ERROR - Matrix buffer not created", "ERROR", MB_OK);
      return false;
    }

    return true;
  }

  void CoreGeometry::render(const CoreMaterial* material) {

    auto& window = Core::instance().window_;
    auto* device_context = Core::instance().d3d_.deviceContext();
    auto& cam = Core::instance().cam_;
    
    // --------------------- TEMPORAL HASTA QUE HAYA NODOS U OBJECTS.
    DirectX::XMMATRIX model, view, projection;
    DirectX::XMMATRIX scale, rotation, translation, result;

    float sin_value = DirectX::XMScalarSin((float)Time() * 0.001f);
    scale = DirectX::XMMatrixScaling(sin_value, sin_value, sin_value);
    rotation = DirectX::XMMatrixRotationRollPitchYaw(0.0f, (float)Time() * 0.01f, 0.0f);
    translation = DirectX::XMMatrixTranslation(sin_value, 0.0f, 0.0f);
    result = scale * rotation * translation;
    model = DirectX::XMMatrixTranspose(result);
    // ------------------------

    DirectX::XMFLOAT4X4 mvp[3];
    DirectX::XMStoreFloat4x4(mvp, model); 
    DirectX::XMStoreFloat4x4(&mvp[1], DirectX::XMMatrixTranspose(Core::instance().cam_.viewMatrix()));
    DirectX::XMStoreFloat4x4(&mvp[2], DirectX::XMMatrixTranspose(Core::instance().cam_.projectionMatrix()));

    D3D11_MAPPED_SUBRESOURCE new_matrices;
    ZeroMemory(&new_matrices, sizeof(D3D11_MAPPED_SUBRESOURCE));
    device_context->Map(matrix_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &new_matrices);
    memcpy(new_matrices.pData, mvp, sizeof(DirectX::XMFLOAT4X4) * 3);
    device_context->Unmap(matrix_buffer_, 0);

    uint32 stride = sizeof(DirectX::XMFLOAT3);
    uint32 offset = 0;

    device_context->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
    device_context->IASetIndexBuffer(vertex_index_buffer_, DXGI_FORMAT_R32_UINT, 0);
    device_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    device_context->VSSetShader(material->vertex_shader_, 0, 0);
    device_context->PSSetShader(material->pixel_shader_, 0, 0);
    device_context->VSSetConstantBuffers(0, 1, &matrix_buffer_);
    device_context->IASetInputLayout(material->input_layout_);
    device_context->DrawIndexed(vertex_index_.size(), 0, 0);
  }




}; /* SLX */
