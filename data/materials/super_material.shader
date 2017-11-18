/*
  CONSTANT BUFFERS
*/

cbuffer CustomConstantBuffer {
	matrix model_matrix;
	matrix view_matrix;
	matrix projection_matrix;
  unsigned int type;
  unsigned int num_textures;
  float timer;
  float time2;
};

/* 
  INPUT OUTPUT STRUCTS
*/
struct VertexInfo {
	float4 vPosition : POSITION; 
	float4 vNormal : NORMAL;
	float2 vTexCoord : TEXCOORD;
	float4 vColor : COLOR;
};

struct PixelInfo {
  /* 
  SV_POSITION Tiene que ser por fuerza un vec4, porque indicara la posicion
  del vertice, al igual que se hacia en el vertex shader de glsl que habia 
  que retornar un vec4 para que la recogiera el shader de fragmento.    
  */
	float4 Position : SV_POSITION; 
	float4 Normal : NORMAL;
	float2 TexCoord : TEXCOORD;
	float4 Color : COLOR;
  float4 MapColor : MAPCOLOR;
};

/*
  VERTEX SHADER
*/

// All textures will use the same sampler
SamplerState sampler_type : register(s0);
// Textures
Texture2D texture_ : register(t0);
Texture2D texture_materialmap : register(t1);
Texture2D texture_grass : register(t2);
Texture2D texture_moss : register(t3);
Texture2D texture_asphalt : register(t4);

PixelInfo VertexShaderFunction(VertexInfo vertex_info) {
	PixelInfo pixel_info;

  // Calculamos la posicion
  pixel_info.Position = vertex_info.vPosition;
  pixel_info.Position.w = 1.0f;
	pixel_info.Position = mul(vertex_info.vPosition, model_matrix);
	pixel_info.Position = mul(pixel_info.Position, view_matrix);
	pixel_info.Position = mul(pixel_info.Position, projection_matrix);
  
  // Calculamos la normal aplicandole las transformaciones del objeto.
  pixel_info.Normal = vertex_info.vNormal;
  pixel_info.Normal.w = 0.0f;
  pixel_info.Normal = mul(pixel_info.Normal, model_matrix);
  pixel_info.Normal = normalize(pixel_info.Normal);

  // UV
	pixel_info.TexCoord = vertex_info.vTexCoord;

  // Color
	pixel_info.Color = vertex_info.vColor;

  // Map Color
  pixel_info.MapColor = texture_materialmap.SampleLevel(sampler_type, pixel_info.TexCoord, 0);

	return pixel_info;
}


// EJEMPLO PARA TESTEAR LUCES.
struct Light {
  float4 dir;
  float4 color;
  float intensity;
};


float4 CalculateLightColor(float4 normal) {
  // Calculamos el color difuso de la luz.
  Light light;
  light.dir = float4(1.0f, 1.0f, -1.0f, 0.0f);
  light.dir.x = sin(timer * 0.001f);
  light.dir.z = cos(timer * 0.001f);
  light.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
  light.intensity = 0.9f;
  float diffuse = max(dot(normalize(normal), light.dir), 0.0);
  return diffuse * light.color * light.intensity;
}


#define DIFFUSE 0
#define ONE_TEXTURE 1
#define NORMALS 2
#define ASSIGNMENT 3

float4 PixelShaderFunction(PixelInfo pixel_info) : SV_TARGET {
  
  float4 color = pixel_info.Color * CalculateLightColor(pixel_info.Normal);

  switch (type) {

    case DIFFUSE:{}break;
  
    case ONE_TEXTURE: {
      color *= texture_.Sample(sampler_type, pixel_info.TexCoord);
    }break;
  
    case NORMALS: {
      color = pixel_info.Normal;
    }break;

    case ASSIGNMENT: {
      float uv_scale = 30.0f;
      float4 matmap_color = pixel_info.MapColor;
      float4 grass_color = texture_grass.Sample(sampler_type, pixel_info.TexCoord * uv_scale);
      float4 moss_color = texture_moss.Sample(sampler_type, pixel_info.TexCoord * uv_scale);
      float4 asphalt_color = texture_asphalt.Sample(sampler_type, pixel_info.TexCoord * uv_scale);

      grass_color *= matmap_color.g;
      moss_color *= matmap_color.r;
      asphalt_color *= matmap_color.b;
      
      color *= (grass_color + moss_color + asphalt_color);
    }break;
  }

  return color;
}