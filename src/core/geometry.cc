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
  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
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

  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  return true;
}

bool CoreGeometry::init(const char * height_map_filename, 
                        const float grid_size) {

  FILE* filePtr;
  int32 error;
  uint32 count;
  BITMAPFILEHEADER bitmapFileHeader;
  BITMAPINFOHEADER bitmapInfoHeader;
  int32 imageSize, i, j, k, index;
  unsigned char* bitmapImage;
  unsigned char height;
  DirectX::XMINT2 heightmap_size;
  int32 num_vertices = 24;
  int32 num_indices = 36;

  // Rellenamos info de vertices e indices.
  vertex_data_.resize(num_vertices);
  vertex_index_.resize(num_indices);

  // Open the height map file in binary.
  if (fopen_s(&filePtr, height_map_filename, "rb")) {
    MessageBox(NULL, "ERROR - Heightmap filename incorrect.", "ERROR", MB_OK);
    return false;
  }

  // Read in the file header.
  count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
  if (count != 1) {
    MessageBox(NULL, "ERROR - Heightmap file is empty.", "ERROR", MB_OK);
    return false;
  }

  // Read in the bitmap info header.
  count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
  if (count != 1) {
    MessageBox(NULL, "ERROR - Heightmap info header incorrect.", "ERROR", MB_OK);
    return false;
  }

  // Save the dimensions of the terrain.
  heightmap_size = { bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight };

  // Calculate the size of the bitmap image data.
  imageSize = heightmap_size.x * heightmap_size.y * 3;

  // Allocate memory for the bitmap image data.
  bitmapImage = new unsigned char[imageSize];
  if (!bitmapImage) {
    MessageBox(NULL, "ERROR - Allocating memory for the bitmap image data.", "ERROR", MB_OK);
    return false;
  }

  // Move to the beginning of the bitmap data.
  fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

  // Read in the bitmap image data.
  count = fread(bitmapImage, 1, imageSize, filePtr);
  if (count != imageSize) {
    delete[] bitmapImage;
    MessageBox(NULL, "ERROR - Allocating memory for the bitmap image data.", "ERROR", MB_OK);
    return false;
  }

  // Close the file.
  error = fclose(filePtr);
  if (error != 0) {
    delete[] bitmapImage;
    MessageBox(NULL, "ERROR - File couldnt be closed.", "ERROR", MB_OK);
    return false;
  }

  // Initialize the position in the image data buffer.
  k = 0;

  // Save the heightmap_data.
  std::vector<DirectX::XMFLOAT3> height_map_data;
  height_map_data.resize(heightmap_size.x * heightmap_size.y);

  // Read the image data into the height map.
  for (j = 0; j< heightmap_size.y; j++)
  {
    for (i = 0; i<heightmap_size.x; i++)
    {
      height = bitmapImage[k];

      index = (heightmap_size.y * j) + i;

      height_map_data[index].x = (float)i / (float)heightmap_size.x * grid_size;
      height_map_data[index].y = (float)height / 256.0f;
      height_map_data[index].z = (float)j / (float)heightmap_size.y * grid_size;

      k += 3;
    }
  }

  // Release the bitmap image data.
  delete[] bitmapImage;
  bitmapImage = nullptr;

  /* GEOMETRY CREATION */
  int32 num_points_per_row = 256;
  int32 num_squares_per_row = 255;

  num_vertices = num_points_per_row * num_squares_per_row * 2;
  num_indices = num_vertices;
  vertex_data_.resize(num_vertices);
  vertex_index_.resize(num_indices);

  int32 map_index = 0;
  int32 direction = -1;

  index = 0;
  for (int32 y = 0; y < num_squares_per_row; y++) {
    direction *= -1;
    for (int32 x = 0; x < num_points_per_row; x++) {

      // NORMALS

      DirectX::XMVECTOR up1, up2, down1, down2, right, left;
      DirectX::XMFLOAT3 normal1, normal2;

      // LEFT AND RIGHT WILL BE SHARED FOR BOTH VERTEX.
      // left
      if (map_index == 0) { left = { -1.0f, 0.0f, 0.0f }; }
      else {
        left = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[y * num_points_per_row + map_index - 1]) , DirectX::XMLoadFloat3(&height_map_data[y * num_points_per_row + map_index]));
      }
      // Right
      if (map_index == num_squares_per_row) { right = { 1.0f, 0.0f, 0.0f }; }
      else {
        right = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[y * num_points_per_row + map_index + 1]) , DirectX::XMLoadFloat3(&height_map_data[y * num_points_per_row + map_index]));
      }

      // Up 
      if (y == 0) { up1 = { 0.0f, 0.0f, -1.0f }; }
      else {
        up1 = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[(y - 1) * num_points_per_row + map_index]) , DirectX::XMLoadFloat3(&height_map_data[y * num_points_per_row + map_index]));
      }
      up2 = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[y * num_points_per_row + map_index]) , DirectX::XMLoadFloat3(&height_map_data[(y + 1) * num_points_per_row + map_index]));
      // Down
      if ((y + 1) == num_squares_per_row) { down2 = { 0.0f, 0.0f, 1.0f }; }
      else {
        down2 = DirectX::XMVectorSubtract(XMLoadFloat3(&height_map_data[(y + 2) * num_points_per_row + map_index]) , XMLoadFloat3(&height_map_data[(y + 1) * num_points_per_row + map_index]));
      }
      down1 = DirectX::XMVectorSubtract(XMLoadFloat3(&height_map_data[(y + 1) * num_points_per_row + map_index]) , XMLoadFloat3(&height_map_data[y * num_points_per_row + map_index]));

      // Calculating the normals for both vertex. Doing the average between its 4 normals from its 4 neighbors.
      DirectX::XMVECTOR normal, n1, n2, n3, n4;
      DirectX::XMFLOAT2 uv = { 0.0f, 0.0f };
      DirectX::XMFLOAT4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

      // VERTICES 
      if (direction > 0) { // Going to the right direction. X+
        n1 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(right, up1));
        n2 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up1, left));
        n3 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(left, down1));
        n4 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(down1, right));
        normal = DirectX::XMVector3Normalize(DirectX::XMVectorAdd(DirectX::XMVectorAdd(n1, n2), DirectX::XMVectorAdd(n3, n4)));
        XMStoreFloat3(&normal1, normal);
        // 1.
        vertex_data_[index] = { height_map_data[y * num_points_per_row + map_index], normal1, uv, color };
        vertex_index_[index] = index;
        index++;
        // 2.
        vertex_data_[index] = { height_map_data[(y + 1) * num_points_per_row + map_index], normal2, uv, color };
        vertex_index_[index] = index;
        index++;
      }
      else { // X-
        n1 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(right, up2));
        n2 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up2, left));
        n3 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(left, down2));
        n4 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(down2, right));
        normal = DirectX::XMVector3Normalize(DirectX::XMVectorAdd(DirectX::XMVectorAdd(n1, n2), DirectX::XMVectorAdd(n3, n4)));
        XMStoreFloat3(&normal2, normal);
        // 2.
        vertex_data_[index] = { height_map_data[(y + 1) * num_points_per_row + map_index], normal2, uv, color };
        vertex_index_[index] = index;
        index++;
        // 1.
        vertex_data_[index] = { height_map_data[y * num_points_per_row + map_index], normal2, uv, color };
        vertex_index_[index] = index;
        index++;
      }

      map_index += direction;
      // To repeat both side limits twice.
      if (map_index > num_squares_per_row) { map_index = num_squares_per_row; }
      else if (map_index < 0) { map_index = 0; }

    }
  }
  
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

  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

  return true;
}


}; /* SLX */
