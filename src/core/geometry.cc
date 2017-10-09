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

namespace SLX {

  
  /*******************************************************************************
  ***                        Constructor and destructor                        ***
  *******************************************************************************/

  CoreGeometry::CoreGeometry() {
    
  }

  CoreGeometry::~CoreGeometry() {
    vertex_index_.clear();
    vertex_data_.clear();
    if (vertex_buffer_) { vertex_buffer_->Release(); }
    if (vertex_index_buffer_) { vertex_index_buffer_->Release(); }
    if (matrix_buffer_) { matrix_buffer_->Release(); }
  }

  /*******************************************************************************
  ***                               Public methods                             ***
  *******************************************************************************/

  bool CoreGeometry::init() {

    // CUBO de ejemplo
    int32 num_vertices = 24;
    int32 num_indices = 36;

    // Rellenamos info de vertices e indices.
    vertex_data_.resize(num_vertices);
    vertex_index_.resize(num_indices);

                        // Position,             Normal                 UV              COLOR
    vertex_data_[0] = { { -0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[1] = { { 0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[2] = { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[3] = { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };

    vertex_data_[4] = { { -0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[5] = { { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[6] = { { -0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[7] = { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };

    vertex_data_[8] = { { -0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[9] = { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[10] = { { -0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[11] = { { -0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };

    vertex_data_[12] = { { 0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[13] = { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[14] = { { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[15] = { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };

    vertex_data_[16] = { { -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[17] = { { -0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[18] = { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[19] = { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };

    vertex_data_[20] = { { -0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[21] = { { -0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[22] = { { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };
    vertex_data_[23] = { { 0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } };

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
    vertex_description.ByteWidth = sizeof(VertexData) * num_vertices;

    D3D11_SUBRESOURCE_DATA vertex_data;
    ZeroMemory(&vertex_data, sizeof(D3D11_SUBRESOURCE_DATA));
    vertex_data.pSysMem = vertex_data_.data();

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


}; /* SLX */
