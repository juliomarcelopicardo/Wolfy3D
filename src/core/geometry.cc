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

bool CoreGeometry::initTriangle(const float32 width, const float32 height,
                                const DirectX::XMFLOAT4 color) {

  // CUBO de ejemplo
  num_vertices_ = 3;
  num_indices_ = 3;
  float32 half_width = width * 0.5f;
  float32 half_height = height * 0.5f;

  // Rellenamos info de vertices e indices.
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  vertex_data_[0] = { { 0.0f, half_width, 0.0f },       // Position
                      { 0.0f, 0.0f, 1.0f },             // Normal
                      { 0.0f, 1.0f },                   // UV / TexCoord
                      color };                          // Color
  vertex_data_[1] = { { half_width, -half_height, 0.0f },
                      { 0.0f, 1.0f, 0.0f },
                      { 1.0f, 0.0f },
                      color };
  vertex_data_[2] = { { -half_width, -half_height, 0.0f },
                      { 1.0f, 0.0f, .0f },
                      { 0.0f, 1.0f },
                      color };
  
  vertex_index_[0] = 0;
  vertex_index_[1] = 1;
  vertex_index_[2] = 2;
  
  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }
  if (!createMatrixBuffer()) { return false; }

  return true;
}



bool CoreGeometry::initCube(const DirectX::XMFLOAT3 size, 
                            const DirectX::XMFLOAT4 color) {

  // CUBO de ejemplo
  num_vertices_ = 24;
  num_indices_ = 36;

  // Rellenamos info de vertices e indices.
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);
  DirectX::XMFLOAT3 half_size = { size.x * 0.5f, size.y * 0.5f, size.z * 0.5f };

                          // Position,                              Normal                 UV              COLOR
  vertex_data_[0] = { { -half_size.x, half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };
  vertex_data_[1] = { { half_size.x, half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, color };
  vertex_data_[2] = { { -half_size.x, -half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, color };
  vertex_data_[3] = { { half_size.x, -half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, color };

  vertex_data_[4] = { { -half_size.x, half_size.y, half_size.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, color };
  vertex_data_[5] = { { half_size.x, half_size.y, half_size.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f }, color };
  vertex_data_[6] = { { -half_size.x, -half_size.y, half_size.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f }, color };
  vertex_data_[7] = { { half_size.x, -half_size.y, half_size.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }, color };

  vertex_data_[8] = { { -half_size.x, half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, color };
  vertex_data_[9] = { { -half_size.x, -half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, color };
  vertex_data_[10] = { { -half_size.x, half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };
  vertex_data_[11] = { { -half_size.x, -half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, color };

  vertex_data_[12] = { { half_size.x, half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };
  vertex_data_[13] = { { half_size.x, -half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, color };
  vertex_data_[14] = { { half_size.x, half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, color };
  vertex_data_[15] = { { half_size.x, -half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, color };

  vertex_data_[16] = { { -half_size.x, -half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };
  vertex_data_[17] = { { -half_size.x, -half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, color };
  vertex_data_[18] = { { half_size.x, -half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, color };
  vertex_data_[19] = { { half_size.x, -half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, color };

  vertex_data_[20] = { { -half_size.x, half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };
  vertex_data_[21] = { { -half_size.x, half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }, color };
  vertex_data_[22] = { { half_size.x, half_size.y, half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }, color };
  vertex_data_[23] = { { half_size.x, half_size.y, -half_size.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, color };

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

  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }
  if (!createMatrixBuffer()) { return false; }

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
  int32 num_points_per_row = heightmap_size.x;
  int32 num_squares_per_row = num_points_per_row - 1;
  int32 num_points_per_col = heightmap_size.y;
  int32 num_squares_per_col = num_points_per_col - 1;

  num_vertices_ = num_points_per_row * num_points_per_col;
  num_indices_ = num_squares_per_col * num_points_per_row * 2;
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  for (int32 y = 0; y < num_points_per_col; y++) {
	  for (int32 x = 0; x < num_points_per_row; x++) {

		  // NORMALS
		  DirectX::XMVECTOR up, down, right, left;
		  DirectX::XMFLOAT3 normal;
		  int32 idx = y * num_points_per_row + x;

		  // left
		  if (x == 0) { left = { -1.0f, 0.0f, 0.0f }; }
		  else {
			  left = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[idx - 1]), DirectX::XMLoadFloat3(&height_map_data[idx]));
		  }
		  // Right
		  if (x == num_squares_per_row) { right = { 1.0f, 0.0f, 0.0f }; }
		  else {
			  right = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[idx + 1]), DirectX::XMLoadFloat3(&height_map_data[idx]));
		  }

		  // Up 
		  if (y == 0) { up = { 0.0f, 0.0f, -1.0f }; }
		  else {
			  up = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[idx - num_points_per_row]), DirectX::XMLoadFloat3(&height_map_data[idx]));
		  }
		  // Down
		  if (y == num_squares_per_row) { down = { 0.0f, 0.0f, 1.0f }; }
		  else {
			  down = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&height_map_data[idx + num_points_per_row]), DirectX::XMLoadFloat3(&height_map_data[idx]));
		  }


		  // Calculating the normals for both vertex. Doing the average between its 4 normals from its 4 neighbors.
		  DirectX::XMVECTOR tmp_normal;
		  tmp_normal = DirectX::XMVectorAdd(DirectX::XMVector3Normalize(DirectX::XMVector3Normalize(DirectX::XMVector3Cross(right, up))), DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up, left)));
		  tmp_normal = DirectX::XMVectorAdd(tmp_normal, DirectX::XMVector3Normalize(DirectX::XMVector3Cross(left, down)));
		  tmp_normal = DirectX::XMVectorAdd(tmp_normal, DirectX::XMVector3Normalize(DirectX::XMVector3Cross(down, right)));
		  XMStoreFloat3(&normal, tmp_normal);

		  vertex_data_[idx].position = height_map_data[idx];
		  vertex_data_[idx].normal = normal;
		  vertex_data_[idx].uv = { 1.0f, 1.0f };
		  vertex_data_[idx].color = { 0.3f, 0.3f, 0.3f, 1.0f };
	  }
  }

  // ELEMENTS

  index = 0;
  int32 map_index = 0;
  int32 direction = -1;

  for (int32 y = 0; y < num_squares_per_col; y++) {
	  direction *= -1;
	  for (int32 x = 0; x < num_points_per_row; x++) {

		  if (direction > 0) { // Going to the right direction. X+
							   // 1.
			  vertex_index_[index] = y * num_points_per_row + map_index;
			  index++;
			  // 2.
			  vertex_index_[index] = (y + 1) * num_points_per_row + map_index;
			  index++;
		  }
		  else { // X-
				 // 2.
			  vertex_index_[index] = (y + 1) * num_points_per_row + map_index;
			  index++;
			  // 1.
			  vertex_index_[index] = y * num_points_per_row + map_index;
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
  vertex_description.ByteWidth = sizeof(VertexData) * num_vertices_;

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
  index_description.ByteWidth = sizeof(uint32) * num_indices_;

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



/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

bool CoreGeometry::createVertexBuffer() {
  // Creamos un buffer para subir la informacion de los vertices a la grafica.
  D3D11_BUFFER_DESC vertex_description;
  ZeroMemory(&vertex_description, sizeof(D3D11_BUFFER_DESC));

  vertex_description.Usage = D3D11_USAGE_DEFAULT;
  vertex_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  vertex_description.ByteWidth = sizeof(VertexData) * num_vertices_;

  D3D11_SUBRESOURCE_DATA vertex_data;
  ZeroMemory(&vertex_data, sizeof(D3D11_SUBRESOURCE_DATA));
  vertex_data.pSysMem = vertex_data_.data();

  auto* device = Core::instance().d3d_.device();

  if (FAILED(device->CreateBuffer(&vertex_description, &vertex_data, &vertex_buffer_))) {
    MessageBox(NULL, "ERROR - Vertex buffer not created", "ERROR", MB_OK);
    return false;
  }
  return true;
}


bool CoreGeometry::createIndexBuffer() {
  // Creamos un buffer para subir la informacion de los indices a la grafica.
  D3D11_BUFFER_DESC index_description;
  ZeroMemory(&index_description, sizeof(D3D11_BUFFER_DESC));

  index_description.Usage = D3D11_USAGE_DEFAULT;
  index_description.BindFlags = D3D11_BIND_INDEX_BUFFER;
  index_description.ByteWidth = sizeof(uint32) * num_indices_;

  D3D11_SUBRESOURCE_DATA index_data;
  ZeroMemory(&index_data, sizeof(D3D11_SUBRESOURCE_DATA));
  index_data.pSysMem = vertex_index_.data();

  auto* device = Core::instance().d3d_.device();

  if (FAILED(device->CreateBuffer(&index_description, &index_data, &vertex_index_buffer_))) {
    MessageBox(NULL, "ERROR - Vertex buffer not created", "ERROR", MB_OK);
    return false;
  }
  return true;
}

bool CoreGeometry::createMatrixBuffer() {
  // Creamos un buffer para almacenar las matrices.
  D3D11_BUFFER_DESC matrix_description;
  ZeroMemory(&matrix_description, sizeof(D3D11_BUFFER_DESC));

  matrix_description.Usage = D3D11_USAGE_DYNAMIC;
  matrix_description.ByteWidth = sizeof(DirectX::XMFLOAT4X4) * 3;
  matrix_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  matrix_description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  auto* device = Core::instance().d3d_.device();

  if (FAILED(device->CreateBuffer(&matrix_description, NULL, &matrix_buffer_))) {
    MessageBox(NULL, "ERROR - Matrix buffer not created", "ERROR", MB_OK);
    return false;
  }
  return true;
}



}; /* SLX */
