/** Copyright Julio Picardo 2017-18, all rights reserved.
*
*  @project Wolfy3D
*  @authors Julio Marcelo Picardo <juliomarcelopicardo@gmail.com>
*
*/

#include "Wolfy3D/globals.h"
#include "core/geo.h"
#include "core/core.h"
#include <string>
#include <fstream>

namespace W3D {

  
/*******************************************************************************
***                        Constructor and destructor                        ***
*******************************************************************************/

Geo::Geo() {
  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
  vertex_buffer_ = nullptr;
  vertex_index_buffer_ = nullptr;
  name_ = "";
  type_ = kType_None;
}

Geo::~Geo() {
  vertex_index_.clear();
  vertex_data_.clear();
  if (vertex_buffer_) { vertex_buffer_->Release(); }
  if (vertex_index_buffer_) { vertex_index_buffer_->Release(); }
}

/*******************************************************************************
***                               Public methods                             ***
*******************************************************************************/

bool Geo::initTriangle(const DirectX::XMFLOAT2 size, const DirectX::XMFLOAT4 color) {

  num_vertices_ = 3;
  num_indices_ = 3;
  float32 half_width = size.x * 0.5f;
  float32 half_height = size.y * 0.5f;

  // Vertices info.
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  vertex_data_[0] = { { 0.0f, half_height, 0.0f },      // Position
                      { 0.0f, 0.0f, 1.0f },             // Normal
                      { 0.5f, 0.0f },                   // UV / TexCoord
                      color };                          // Color
  vertex_data_[1] = { { half_width, -half_height, 0.0f },
                      { 0.0f, 0.0f, 1.0f },
                      { 1.0f, 1.0f },
                      color };
  vertex_data_[2] = { { -half_width, -half_height, 0.0f },
                      { 0.0f, 0.0f, 1.0f },
                      { 0.0f, 1.0f },
                      color };
  
  vertex_index_[0] = 0;
  vertex_index_[1] = 2;
  vertex_index_[2] = 1;
  
  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }
  
  type_ = kType_Triangle;
  info_.triangle.size = { size.x, size.y };
  name_ = "Triangle";

  return true;
}

bool Geo::initQuad(const DirectX::XMFLOAT2 size, const DirectX::XMFLOAT4 color) {

  num_vertices_ = 4;
  num_indices_ = 6;
  float32 half_width = size.x * 0.5f;
  float32 half_height = size.y * 0.5f;

  // Vertices info.
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  /*
        0         1
          *******
          |     |
          |     |
          *******
        3         2
  */


  vertex_data_[0] = { { -half_width, half_height, 0.0f },       // Position
                      { 0.0f, 0.0f, 1.0f },                     // Normal
                      { 0.0f, 0.0f },                           // UV / TexCoord
                        color };                                // Color
  vertex_data_[1] = { { half_width, half_height, 0.0f },
                      { 0.0f, 0.0f, 1.0f },
                      { 1.0f, 0.0f },
                        color };
  vertex_data_[2] = { { half_width, -half_height, 0.0f },
                      { 0.0f, 0.0f, 1.0f },
                      { 1.0f, 1.0f },
                        color };
  vertex_data_[3] = { { -half_width, -half_height, 0.0f },
                      { 0.0f, 0.0f, 1.0f },
                      { 0.0f, 1.0f },
                        color };

  vertex_index_[0] = 0;
  vertex_index_[1] = 2;
  vertex_index_[2] = 1;
  vertex_index_[3] = 0;
  vertex_index_[4] = 3;
  vertex_index_[5] = 2;

  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }

  // Factory info.
  type_ = kType_Quad;
  info_.quad.size = { size.x, size.y };
  name_ = "Quad";

  return true;
}

bool Geo::initCube(const DirectX::XMFLOAT3 size, const DirectX::XMFLOAT4 color) {
 
  num_vertices_ = 24;
  num_indices_ = 36;

  // Vertices info.
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  DirectX::XMFLOAT3 h_size = { size.x * 0.5f, size.y * 0.5f, size.z * 0.5f };
  DirectX::XMFLOAT3 normal_x = { 1.0f, 0.0f, 0.0f };
  DirectX::XMFLOAT3 normal_y = { 0.0f, 1.0f, 0.0f };
  DirectX::XMFLOAT3 normal_z = { 0.0f, 0.0f, 1.0f };
  DirectX::XMFLOAT3 normal_x_neg = { -1.0f, 0.0f, 0.0f };
  DirectX::XMFLOAT3 normal_y_neg = { 0.0f, -1.0f, 0.0f };
  DirectX::XMFLOAT3 normal_z_neg = { 0.0f, 0.0f, -1.0f };
  DirectX::XMFLOAT2 uv_top_l = { 0.0f, 0.0f };
  DirectX::XMFLOAT2 uv_top_r = { 1.0f, 0.0f };
  DirectX::XMFLOAT2 uv_bot_r = { 1.0f, 1.0f };
  DirectX::XMFLOAT2 uv_bot_l = { 0.0f, 1.0f };

  // FACE Z + 
  vertex_data_[0] = { { -h_size.x, h_size.y, h_size.z }, normal_z, uv_top_l, color };
  vertex_data_[1] = { { h_size.x, h_size.y, h_size.z }, normal_z, uv_top_r, color };
  vertex_data_[2] = { { h_size.x, -h_size.y, h_size.z }, normal_z, uv_bot_r, color };
  vertex_data_[3] = { { -h_size.x, -h_size.y, h_size.z }, normal_z, uv_bot_l, color };

  // FACE X+
  vertex_data_[4] = { { h_size.x, h_size.y, h_size.z }, normal_x, uv_top_l, color };
  vertex_data_[5] = { { h_size.x, h_size.y, -h_size.z }, normal_x, uv_top_r, color };
  vertex_data_[6] = { { h_size.x, -h_size.y, -h_size.z }, normal_x, uv_bot_r, color };
  vertex_data_[7] = { { h_size.x, -h_size.y, h_size.z }, normal_x, uv_bot_l, color };

  // FACE Z -
  vertex_data_[8] = { { h_size.x, h_size.y, -h_size.z }, normal_z_neg, uv_top_l, color };
  vertex_data_[9] = { { -h_size.x, h_size.y, -h_size.z }, normal_z_neg, uv_top_r, color };
  vertex_data_[10] = { { -h_size.x, -h_size.y, -h_size.z }, normal_z_neg, uv_bot_r, color };
  vertex_data_[11] = { { h_size.x, -h_size.y, -h_size.z }, normal_z_neg, uv_bot_l, color };

  // FACE X- 
  vertex_data_[12] = { { -h_size.x, h_size.y, -h_size.z }, normal_x_neg, uv_top_l, color };
  vertex_data_[13] = { { -h_size.x, h_size.y, h_size.z }, normal_x_neg, uv_top_r, color };
  vertex_data_[14] = { { -h_size.x, -h_size.y, h_size.z }, normal_x_neg, uv_bot_r, color };
  vertex_data_[15] = { { -h_size.x, -h_size.y, -h_size.z }, normal_x_neg, uv_bot_l, color };

  // FACE Y -
  vertex_data_[16] = { { -h_size.x, -h_size.y, h_size.z }, normal_y_neg, uv_top_l, color };
  vertex_data_[17] = { { h_size.x, -h_size.y, h_size.z }, normal_y_neg, uv_top_r, color };
  vertex_data_[18] = { { h_size.x, -h_size.y, -h_size.z }, normal_y_neg, uv_bot_r, color };
  vertex_data_[19] = { { -h_size.x, -h_size.y, -h_size.z }, normal_y_neg, uv_bot_l, color };

  // FACE Y +
  vertex_data_[20] = { { -h_size.x, h_size.y, -h_size.z }, normal_y, uv_top_l, color };
  vertex_data_[21] = { { h_size.x, h_size.y, -h_size.z }, normal_y, uv_top_r, color };
  vertex_data_[22] = { { h_size.x, h_size.y, h_size.z }, normal_y, uv_bot_r, color };
  vertex_data_[23] = { { -h_size.x, h_size.y, h_size.z }, normal_y, uv_bot_l, color };

  vertex_index_[0] = 0;
  vertex_index_[1] = 2;
  vertex_index_[2] = 1;
  vertex_index_[3] = 0;
  vertex_index_[4] = 3;
  vertex_index_[5] = 2;

  vertex_index_[6] = 4;
  vertex_index_[7] = 6;
  vertex_index_[8] = 5;
  vertex_index_[9] = 4;
  vertex_index_[10] = 7;
  vertex_index_[11] = 6;

  vertex_index_[12] = 8;
  vertex_index_[13] = 10;
  vertex_index_[14] = 9;
  vertex_index_[15] = 8;
  vertex_index_[16] = 11;
  vertex_index_[17] = 10;

  vertex_index_[18] = 12;
  vertex_index_[19] = 14;
  vertex_index_[20] = 13;
  vertex_index_[21] = 12;
  vertex_index_[22] = 15;
  vertex_index_[23] = 14;
  
  vertex_index_[24] = 16;
  vertex_index_[25] = 18;
  vertex_index_[26] = 17;
  vertex_index_[27] = 16;
  vertex_index_[28] = 19;
  vertex_index_[29] = 18;

  vertex_index_[30] = 20;
  vertex_index_[31] = 22;
  vertex_index_[32] = 21;
  vertex_index_[33] = 20;
  vertex_index_[34] = 23;
  vertex_index_[35] = 22;

  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }

  // Factory info.
  type_ = kType_Cube;
  info_.cube.size = { size.x, size.y, size.z };
  name_ = "Cube";

  return true;
}

bool Geo::initSkyBoxCube(const DirectX::XMFLOAT3 size, const DirectX::XMFLOAT4 color) {
  
  num_vertices_ = 24;
  num_indices_ = 36;

  // Vertices info.
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  DirectX::XMFLOAT3 h_size = { size.x * 0.5f, size.y * 0.5f, size.z * 0.5f };
  DirectX::XMFLOAT3 normal_x = { 1.0f, 0.0f, 0.0f };
  DirectX::XMFLOAT3 normal_y = { 0.0f, 1.0f, 0.0f };
  DirectX::XMFLOAT3 normal_z = { 0.0f, 0.0f, 1.0f };
  DirectX::XMFLOAT3 normal_x_neg = { -1.0f, 0.0f, 0.0f };
  DirectX::XMFLOAT3 normal_y_neg = { 0.0f, -1.0f, 0.0f };
  DirectX::XMFLOAT3 normal_z_neg = { 0.0f, 0.0f, -1.0f };
  DirectX::XMFLOAT2 uv_top_l = { 0.0f, 0.0f };
  DirectX::XMFLOAT2 uv_top_r = { 1.0f, 0.0f };
  DirectX::XMFLOAT2 uv_bot_r = { 1.0f, 1.0f };
  DirectX::XMFLOAT2 uv_bot_l = { 0.0f, 1.0f };
  float32 uv_div = 1.0f / 3.0f;
  float32 uv_div2 = uv_div * 2.0f;

  // FACE Z + 
  vertex_data_[0] = { { -h_size.x, h_size.y, h_size.z }, normal_z_neg, { 0.25f, uv_div }, color };
  vertex_data_[1] = { { h_size.x, h_size.y, h_size.z }, normal_z_neg, { 0.50f, uv_div }, color };
  vertex_data_[2] = { { h_size.x, -h_size.y, h_size.z }, normal_z_neg, { 0.50f, uv_div2 }, color };
  vertex_data_[3] = { { -h_size.x, -h_size.y, h_size.z }, normal_z_neg, { 0.25f, uv_div2 }, color };

  // FACE X+
  vertex_data_[4] = { { h_size.x, h_size.y, h_size.z }, normal_x_neg, { 0.50f, uv_div }, color };
  vertex_data_[5] = { { h_size.x, h_size.y, -h_size.z }, normal_x_neg, { 0.75f, uv_div }, color };
  vertex_data_[6] = { { h_size.x, -h_size.y, -h_size.z }, normal_x_neg, { 0.75f, uv_div2 }, color };
  vertex_data_[7] = { { h_size.x, -h_size.y, h_size.z }, normal_x_neg, { 0.50f, uv_div2 }, color };

  // FACE Z -
  vertex_data_[8] = { { h_size.x, h_size.y, -h_size.z }, normal_z, { 0.75f, uv_div }, color };
  vertex_data_[9] = { { -h_size.x, h_size.y, -h_size.z }, normal_z, { 1.0f, uv_div }, color };
  vertex_data_[10] = { { -h_size.x, -h_size.y, -h_size.z }, normal_z, { 1.0f, uv_div2 }, color };
  vertex_data_[11] = { { h_size.x, -h_size.y, -h_size.z }, normal_z, { 0.75f, uv_div2 }, color };

  // FACE X- 
  vertex_data_[12] = { { -h_size.x, h_size.y, -h_size.z }, normal_x, { 0.0f, uv_div }, color };
  vertex_data_[13] = { { -h_size.x, h_size.y, h_size.z }, normal_x, { 0.25f, uv_div }, color };
  vertex_data_[14] = { { -h_size.x, -h_size.y, h_size.z }, normal_x, { 0.25f, uv_div2 }, color };
  vertex_data_[15] = { { -h_size.x, -h_size.y, -h_size.z }, normal_x, { 0.0f, uv_div2 }, color };

  // FACE Y -
  vertex_data_[16] = { { -h_size.x, -h_size.y, h_size.z }, normal_y, { 0.25f, uv_div2 }, color };
  vertex_data_[17] = { { h_size.x, -h_size.y, h_size.z }, normal_y, { 0.50f, uv_div2 }, color };
  vertex_data_[18] = { { h_size.x, -h_size.y, -h_size.z }, normal_y, { 0.50f, 1.0f }, color };
  vertex_data_[19] = { { -h_size.x, -h_size.y, -h_size.z }, normal_y, { 0.25f, 1.0f }, color };

  // FACE Y +
  vertex_data_[20] = { { -h_size.x, h_size.y, -h_size.z }, normal_y_neg, { 0.25f, 0.0f }, color };
  vertex_data_[21] = { { h_size.x, h_size.y, -h_size.z }, normal_y_neg, { 0.50f, 0.0f }, color };
  vertex_data_[22] = { { h_size.x, h_size.y, h_size.z }, normal_y_neg, { 0.50f, uv_div }, color };
  vertex_data_[23] = { { -h_size.x, h_size.y, h_size.z }, normal_y_neg, { 0.25f, uv_div  }, color };

  vertex_index_[0] = 0;
  vertex_index_[1] = 1;
  vertex_index_[2] = 2;
  vertex_index_[3] = 0;
  vertex_index_[4] = 2;
  vertex_index_[5] = 3;

  vertex_index_[6] = 4;
  vertex_index_[7] = 5;
  vertex_index_[8] = 6;
  vertex_index_[9] = 4;
  vertex_index_[10] = 6;
  vertex_index_[11] = 7;

  vertex_index_[12] = 8;
  vertex_index_[13] = 9;
  vertex_index_[14] = 10;
  vertex_index_[15] = 8;
  vertex_index_[16] = 10;
  vertex_index_[17] = 11;

  vertex_index_[18] = 12;
  vertex_index_[19] = 13;
  vertex_index_[20] = 14;
  vertex_index_[21] = 12;
  vertex_index_[22] = 14;
  vertex_index_[23] = 15;

  vertex_index_[24] = 16;
  vertex_index_[25] = 17;
  vertex_index_[26] = 18;
  vertex_index_[27] = 16;
  vertex_index_[28] = 18;
  vertex_index_[29] = 19;

  vertex_index_[30] = 20;
  vertex_index_[31] = 21;
  vertex_index_[32] = 22;
  vertex_index_[33] = 20;
  vertex_index_[34] = 22;
  vertex_index_[35] = 23;

  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }

  // Factory info.
  type_ = kType_Skybox;
  info_.skybox.size = { size.x, size.y, size.z };
  name_ = "Skybox";

  return true;
}

bool Geo::initTerrain(const char * height_map_filename, 
                      const DirectX::XMFLOAT3 grid_size, 
                      const DirectX::XMFLOAT4 color) {

  DirectX::XMINT2 heightmap_size;
  std::vector<DirectX::XMFLOAT3> height_map_data;

  if (!parseTerrainImage(grid_size, height_map_filename, height_map_data, heightmap_size)) {
    return false;
  }

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
		  vertex_data_[idx].uv = { (float32)x / (float32)(num_points_per_row - 1), 
                               1.0f - (float32)y / (float32)(num_points_per_col - 1) };
		  vertex_data_[idx].color = color;
	  }
  }

  // ELEMENTS

  int32 index = 0;
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
  
  topology_ = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }

  // Factory info.
  type_ = kType_Terrain;
  info_.terrain.size = { grid_size.x, grid_size.y, grid_size.z };
  name_ = height_map_filename;

  return true;
}

bool Geo::initExtruded(const uint32 num_polygon_vertex,
                       const float32 base_radius,
                       const float32 top_radius,
                       const float32 height,
                       const DirectX::XMFLOAT4 color) {

  float32 angle = DirectX::XM_2PI / (float32)num_polygon_vertex;
  float half_height = height * 0.5f;
  uint32 index = 0, i = 0;

  DirectX::XMFLOAT3 base_center = { 0.0f, -half_height, 0.0f };
  DirectX::XMFLOAT3 top_center = { 0.0f, half_height, 0.0f };
  std::vector <DirectX::XMFLOAT3> base(num_polygon_vertex);
  std::vector <DirectX::XMFLOAT3> top(num_polygon_vertex);

  // Generate the regular poligons.
  for (i = 0; i < num_polygon_vertex; i++) {
    top[i] = { top_radius * DirectX::XMScalarCos(i * angle), half_height,
               top_radius * DirectX::XMScalarSin(i * angle) };

    base[i] = { base_radius * DirectX::XMScalarCos(i * angle), -half_height,
                base_radius * DirectX::XMScalarSin(i * angle) };
  }

  num_vertices_ = num_polygon_vertex * 2 + 2 + (num_polygon_vertex - 1) * 4;
  num_indices_ = num_polygon_vertex * 12;
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  // Fill the base.
  index = 0;
  vertex_data_[index] = { base_center, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }, color };
  index++;
  for (i = 0; i < num_polygon_vertex; i++) {
    vertex_data_[index] = { base[i] ,{ 0.0f, -1.0f, 0.0f },{ 1.0f, 1.0f }, color };
    index++;
  }
  // Fill the top.
  vertex_data_[index] = { top_center,{ 0.0f, 1.0f, 0.0f },{ 1.0f, 1.0f }, color };
  index++;
  for (i = 0; i < num_polygon_vertex; i++) {
    vertex_data_[index] = { top[i] ,{ 0.0f, 1.0f, 0.0f },{ 1.0f, 1.0f }, color };
    index++;
  }
  // Fill the sides.
  DirectX::XMFLOAT3 normal;
  DirectX::XMVECTOR n1, n2, vertical, horizontal; 
  for (i = 0; i < num_polygon_vertex - 1; i++) {

    // 1
    if (i == 0) { 
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[num_polygon_vertex - 1]), DirectX::XMLoadFloat3(&top[i]));
    }
    else {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i - 1]), DirectX::XMLoadFloat3(&top[i]));
    }
    vertical = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i]), DirectX::XMLoadFloat3(&base[i]));
    n1 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i]), DirectX::XMLoadFloat3(&top[i + 1]));
    n2 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    DirectX::XMStoreFloat3(&normal, DirectX::XMVector3Normalize(DirectX::XMVectorAdd(n1, n2)));
    vertex_data_[index] = { top[i] , normal ,{ 0.0f, 0.0f }, color };
    index++;

    // 2
    if (i == 0) {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[num_polygon_vertex - 1]), DirectX::XMLoadFloat3(&base[i]));
    }
    else {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i - 1]), DirectX::XMLoadFloat3(&base[i]));
    }
    vertical = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i]), DirectX::XMLoadFloat3(&base[i]));
    n1 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i]), DirectX::XMLoadFloat3(&base[i + 1]));
    n2 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    DirectX::XMStoreFloat3(&normal, DirectX::XMVector3Normalize(DirectX::XMVectorAdd(n1, n2)));
    vertex_data_[index] = { base[i] , normal ,{ 0.0f, 1.0f }, color };
    index++;

    // 3 
    horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i]), DirectX::XMLoadFloat3(&top[i + 1]));
    vertical = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i + 1]), DirectX::XMLoadFloat3(&base[i + 1]));
    n1 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    if (i + 2 == num_polygon_vertex) {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i + 1]), DirectX::XMLoadFloat3(&top[0]));
    }
    else {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i + 1]), DirectX::XMLoadFloat3(&top[i + 2]));
    }
    n2 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    DirectX::XMStoreFloat3(&normal, DirectX::XMVector3Normalize(DirectX::XMVectorAdd(n1, n2)));
    vertex_data_[index] = { top[i + 1] , normal ,{ 1.0f, 0.0f }, color };
    index++;

    // 4
    horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i]), DirectX::XMLoadFloat3(&base[i + 1]));
    vertical = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top[i + 1]), DirectX::XMLoadFloat3(&base[i + 1]));
    n1 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    if (i + 2 == num_polygon_vertex) {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i + 1]), DirectX::XMLoadFloat3(&base[0]));
    }
    else {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i + 1]), DirectX::XMLoadFloat3(&base[i + 2]));
    }
    n2 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    DirectX::XMStoreFloat3(&normal, DirectX::XMVector3Normalize(DirectX::XMVectorAdd(n1, n2)));
    vertex_data_[index] = { base[i + 1] , normal ,{ 1.0f, 1.0f }, color };
    index++;
  }

  // Base elements
  index = 0;
  for (i = 0; i < num_polygon_vertex - 1; i++) {
    vertex_index_[index] = 0; // base center
    index++;
    vertex_index_[index] = i + 1;
    index++;
    vertex_index_[index] = i + 2;
    index++;
  }
  // To connect the last one with the first one
  vertex_index_[index] = 0; // base center
  index++;
  vertex_index_[index] = num_polygon_vertex;
  index++;
  vertex_index_[index] = 1;
  index++;

  // Top elements
  for (i = 0; i < num_polygon_vertex - 1; i++) {
    vertex_index_[index] = num_polygon_vertex + 1; // top center
    index++;
    vertex_index_[index] = i + num_polygon_vertex + 3;
    index++;
    vertex_index_[index] = i + num_polygon_vertex + 2;
    index++;
  }
  // To connect the last one with the first one
  vertex_index_[index] = num_polygon_vertex + 1; // top center
  index++;
  vertex_index_[index] = num_polygon_vertex + 2;
  index++;
  vertex_index_[index] = i + num_polygon_vertex + 2;
  index++;

  // Sides elements
  uint32 first_element_number = num_polygon_vertex * 2 + 2;
  for (i = 0; i < num_polygon_vertex - 1; i++) {
    vertex_index_[index] = i * 4 + first_element_number;
    index++;
    vertex_index_[index] = i * 4 + first_element_number + 2;
    index++;
    vertex_index_[index] = i * 4 + first_element_number + 1;
    index++;
    vertex_index_[index] = i * 4 + first_element_number + 1; 
    index++;
    vertex_index_[index] = i * 4 + first_element_number + 2;
    index++;
    vertex_index_[index] = i * 4 + first_element_number + 3;
    index++;
  }
  vertex_index_[index] = i * 4 + first_element_number - 2;
  index++;
  vertex_index_[index] = first_element_number;
  index++;
  vertex_index_[index] = i * 4 + first_element_number - 1;
  index++;
  vertex_index_[index] = i * 4 + first_element_number - 1;
  index++;
  vertex_index_[index] = first_element_number;
  index++;
  vertex_index_[index] = first_element_number + 1;
  index++;

  topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }

  // Factory info.
  type_ = kType_Extruded;
  info_.extruded.base_radius = base_radius;
  info_.extruded.top_radius = top_radius;
  info_.extruded.height = height;
  info_.extruded.num_polygon_vertex = num_polygon_vertex;
  name_ = "Extruded";

  return true;
}

bool Geo::initPyramid(const uint32 num_base_vertex, 
                               const float32 base_radius, 
                               const float32 height, 
                               const DirectX::XMFLOAT4 color) {

  float32 angle = DirectX::XM_2PI / (float32)num_base_vertex;
  float half_height = height * 0.5f;
  uint32 index = 0, i = 0;

  DirectX::XMFLOAT3 base_center = { 0.0f, -half_height, 0.0f };
  DirectX::XMFLOAT3 top_center = { 0.0f, half_height, 0.0f };
  std::vector <DirectX::XMFLOAT3> base(num_base_vertex);

  // Generate the regular poligon.
  for (i = 0; i < num_base_vertex; i++) {
    base[i] = { base_radius * DirectX::XMScalarCos(i * angle), -half_height,
                base_radius * DirectX::XMScalarSin(i * angle) };
  }

  num_vertices_ = num_base_vertex * 2 + 2;
  num_indices_ = num_base_vertex * 6;
  vertex_data_.resize(num_vertices_);
  vertex_index_.resize(num_indices_);

  // Fill the base.
  index = 0;
  vertex_data_[index] = { base_center, { 0.0f, -1.0f, 0.0f },{ 1.0f, 1.0f }, color };
  index++;
  for (i = 0; i < num_base_vertex; i++) {
    vertex_data_[index] = { base[i] ,{ 0.0f, -1.0f, 0.0f },{ 1.0f, 1.0f }, color };
    index++;
  }

  // Fill the sides.
  vertex_data_[index] = { top_center,{ 0.0f, 1.0f, 0.0f },{ 1.0f, 1.0f }, color };
  index++;
  DirectX::XMFLOAT3 normal;
  DirectX::XMVECTOR n1, n2, vertical, horizontal;
  for (i = 0; i < num_base_vertex; i++) {
    if (i == 0) {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[num_base_vertex - 1]), DirectX::XMLoadFloat3(&base[i]));
    }
    else {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i - 1]), DirectX::XMLoadFloat3(&base[i]));
    }
    vertical = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&top_center), DirectX::XMLoadFloat3(&base[i]));
    n1 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    if (i == num_base_vertex - 1) {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i]), DirectX::XMLoadFloat3(&base[0]));
    }
    else {
      horizontal = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&base[i]), DirectX::XMLoadFloat3(&base[i + 1]));
    }
    n2 = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMVector3Normalize(horizontal), DirectX::XMVector3Normalize(vertical)));
    DirectX::XMStoreFloat3(&normal, DirectX::XMVector3Normalize(DirectX::XMVectorAdd(n2, n1)));
    vertex_data_[index] = { base[i] , normal ,{ 1.0f, 1.0f }, color };
    index++;
  }

  index = 0;
  // Base elements
  for (i = 0; i < num_base_vertex - 1; i++) {
    vertex_index_[index] = 0; // base center
    index++;
    vertex_index_[index] = i + 1;
    index++;
    vertex_index_[index] = i + 2;
    index++;
  }
  // To connect the last one with the first one
  vertex_index_[index] = 0; // base center
  index++;
  vertex_index_[index] = num_base_vertex;
  index++;
  vertex_index_[index] = 1;
  index++;

  // Sides elements
  for (i = 0; i < num_base_vertex - 1; i++) {
    vertex_index_[index] = num_base_vertex + 1; // top center
    index++;
    vertex_index_[index] = i + 2 + num_base_vertex + 1;
    index++;
    vertex_index_[index] = i + 1 + num_base_vertex + 1;
    index++;
  }
  // To connect the last one with the first one
  vertex_index_[index] = num_base_vertex + 1; // top center
  index++;
  vertex_index_[index] = num_base_vertex + 2;
  index++;
  vertex_index_[index] = num_base_vertex + num_base_vertex + 1;
  index++;
  

  topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }

  // Factory info.
  type_ = kType_Pyramid;
  info_.pyramid.base_radius = base_radius;
  info_.pyramid.height = height;
  info_.pyramid.num_polygon_vertex = num_base_vertex;
  name_ = "Pyramid";

  return true;
}

bool Geo::initFromFile(const char * filename, const DirectX::XMFLOAT4 color) {

  std::ifstream file;
  file.open(filename);

  if (!file) {
    MessageBox(NULL, "ERROR - Geometry can't be initialized, error filename", "ERROR", MB_OK);
    return false;
  }
  
  // Looking for the mesh. Parsing the file line by line.
  std::string line;
  std::string number; // number extracted from a line.
  uint32 line_length = 0;
  uint32 id = 0; // position of the iterator of the line.

  // Get the number of vertices.


  while (!file.eof()) {
    std::getline(file, line);
    if (line.find("Mesh") != std::string::npos) {
      number = "";
      std::getline(file, line);
      std::getline(file, line);
      line_length = line.length();
      while (id < line_length && line[id] != ';') {
        if (line[id] != ' ' && line[id] != '\t') {
          number.push_back(line[id]);
        }
        id++;
      }
      num_vertices_ = std::stoi(number);
      vertex_data_.resize(num_vertices_);
      break;
    }
  }

  // Save the vertex positions.
  for (W3D::int32 i = 0; i < num_vertices_; ++i) {
    std::getline(file, line);
    line_length = line.length();
    number = "";
    id = 0;
    
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[i].position.x = std::stof(number);
    id++;
    number = "";
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[i].position.y = std::stof(number);
    id++;
    number = "";
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[i].position.z = std::stof(number);
    vertex_data_[i].uv = { 1.0f, 1.0f };
    vertex_data_[i].color = color;
  }

  // Get the number of elements.
  std::getline(file, line);
  line_length = line.length();
  number = "";
  id = 0;
  while (id < line_length && line[id] != ';') {
    if (line[id] != ' ' && line[id] != '\t') {
      number.push_back(line[id]);
    }
    id++;
  }
  // We obtain the number of triangles.
  num_indices_ = std::stoi(number) * 3;
  vertex_index_.resize(num_indices_);

  // Save the indices or elements.
  for (W3D::int32 i = 0; i < num_indices_; i += 3) {
    std::getline(file, line);
    line_length = line.length();

    id = line.find_first_of(';');
    id++;

    number = "";
    while (id < line_length && line[id] != ',') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_index_[i] = std::stoi(number);
    id++;
    number = "";
    while (id < line_length && line[id] != ',') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_index_[i + 1] = std::stoi(number);
    id++;
    number = "";
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_index_[i + 2] = std::stoi(number);
  }


  // Get the number of normals.
  std::vector<DirectX::XMFLOAT3> temp_normal;
  uint32 num_normals = 0;
  id = 0;
  while (!file.eof()) {
    std::getline(file, line);
    if (line.find("MeshNormals") != std::string::npos) {
      number = "";
      std::getline(file, line);
      std::getline(file, line);
      line_length = line.length();
      while (id < line_length && line[id] != ';') {
        if (line[id] != ' ' && line[id] != '\t') {
          number.push_back(line[id]);
        }
        id++;
      }
      num_normals = std::stoi(number);
      temp_normal.resize(num_normals);
      break;
    }
  }

  // Save the temp normals.
  for (uint32 i = 0; i < num_normals; ++i) {
    std::getline(file, line);
    line_length = line.length();
    number = "";
    id = 0;

    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    temp_normal[i].x = std::stof(number);
    id++;
    number = "";
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    temp_normal[i].y = std::stof(number);
    id++;
    number = "";
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    temp_normal[i].z = std::stof(number);
  }

  // Save the normals using the indices.
  std::getline(file, line);
  for (W3D::int32 i = 0; i < num_indices_; i += 3) {
    std::getline(file, line);
    line_length = line.length();

    id = line.find_first_of(';');
    id++;

    number = "";
    while (id < line_length && line[id] != ',') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[vertex_index_[i]].normal = temp_normal[std::stoi(number)];
    id++;
    number = "";
    while (id < line_length && line[id] != ',') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[vertex_index_[i + 1]].normal = temp_normal[std::stoi(number)];
    id++;
    number = "";
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[vertex_index_[i + 2]].normal = temp_normal[std::stoi(number)];
  }

  // Go to the uv section.
  while (!file.eof()) {
    std::getline(file, line);
    if (line.find("MeshTextureCoords") != std::string::npos) {
      std::getline(file, line);
      std::getline(file, line);
      break;
    }
  }

  // Save the vertex uv.
  for (W3D::int32 i = 0; i < num_vertices_; ++i) {
    std::getline(file, line);
    line_length = line.length();
    number = "";
    id = 0;

    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[i].uv.x = std::stof(number);
    id++;
    number = "";
    while (id < line_length && line[id] != ';') {
      if (line[id] != ' ' && line[id] != '\t') {
        number.push_back(line[id]);
      }
      id++;
    }
    vertex_data_[i].uv.y = std::stof(number);
  }


  topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

  if (!createVertexBuffer()) { return false; }
  if (!createIndexBuffer()) { return false; }

  type_ = kType_ExternalFile;
  name_ = filename;

  return true;
}



/*******************************************************************************
***                              Private methods                             ***
*******************************************************************************/

bool Geo::createVertexBuffer() {
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


bool Geo::createIndexBuffer() {
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



bool Geo::parseTerrainImage(const DirectX::XMFLOAT3 terrain_size, 
                                     const char * filename, 
                                     std::vector<DirectX::XMFLOAT3>& vertices_output, 
                                     DirectX::XMINT2 & grid_rows_cols_output) {

  FILE* filePtr;
  int32 error;
  uint32 count;
  BITMAPFILEHEADER bitmapFileHeader;
  BITMAPINFOHEADER bitmapInfoHeader;
  int32 imageSize, i, j, k, index;
  uchar8* bitmapImage;
  uchar8 height;
  

  // Open the height map file in binary.
  if (fopen_s(&filePtr, filename, "rb")) {
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
  grid_rows_cols_output = { bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight };

  // Calculate the size of the bitmap image data.
  imageSize = grid_rows_cols_output.x * grid_rows_cols_output.y * 3;

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
  vertices_output.resize(grid_rows_cols_output.x * grid_rows_cols_output.y);

  // Read the image data into the height map.
  for (j = 0; j< grid_rows_cols_output.y; j++)
  {
    for (i = 0; i<grid_rows_cols_output.x; i++)
    {
      height = bitmapImage[k];

      index = (grid_rows_cols_output.y * j) + i;

      vertices_output[index].x = (float32)i / (float32)grid_rows_cols_output.x * terrain_size.x;
      vertices_output[index].y = terrain_size.y * (float32)height / 256.0f;
      vertices_output[index].z = (float32)j / (float32)grid_rows_cols_output.y * terrain_size.z;

      k += 3;
    }
  }

  // Release the bitmap image data.
  delete[] bitmapImage;
  bitmapImage = nullptr;
  return true;
}



}; /* W3D */
