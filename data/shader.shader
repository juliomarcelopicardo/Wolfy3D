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
struct VertexInput {
	float4 vPosition : POSITION; 
	float4 vNormal : NORMAL;
	float2 vTexCoord : TEXCOORD;
	float4 vColor : COLOR;
};

struct PixelInput {
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

Texture2D texture_ : register(t0);
Texture2D texture_materialmap : register(t1);
Texture2D texture_grass : register(t2);
Texture2D texture_moss : register(t3);
Texture2D texture_asphalt : register(t4);
SamplerState sampler_type;

PixelInput VShader(VertexInput input) {
	PixelInput output;

  // Calculamos la posicion
  output.Position = input.vPosition;
  output.Position.w = 1.0f;
	output.Position = mul(input.vPosition, model_matrix);
	output.Position = mul(output.Position, view_matrix);
	output.Position = mul(output.Position, projection_matrix);
  
  // Calculamos la normal aplicandole las transformaciones del objeto.
  output.Normal = input.vNormal;
  output.Normal.w = 0.0f;
  output.Normal = mul(output.Normal, model_matrix);
  output.Normal = normalize(output.Normal);

  // UV
	output.TexCoord = input.vTexCoord;

  // Color
	output.Color = input.vColor;

  // Map Color
  output.MapColor = texture_materialmap.SampleLevel(sampler_type, output.TexCoord, 0);

	return output;
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
#define ASSESMENT 3

float4 PShader(PixelInput pixel_input) : SV_TARGET {
  
  float4 color_result = pixel_input.Color * CalculateLightColor(pixel_input.Normal);

  switch (type) {

    case DIFFUSE:{}break;
  
    case ONE_TEXTURE: {
      color_result *= texture_.Sample(sampler_type, pixel_input.TexCoord);
    }break;
  
    case NORMALS: {
      color_result = pixel_input.Normal;
    }break;

    case ASSESMENT: {

      //float4 matmap_color = texture_materialmap.Sample(sampler_type, pixel_input.TexCoord);
      float4 matmap_color = pixel_input.MapColor;
      float4 grass_color = texture_grass.Sample(sampler_type, pixel_input.TexCoord * 10.0f);
      float4 moss_color = texture_moss.Sample(sampler_type, pixel_input.TexCoord * 10.0f);
      float4 asphalt_color = texture_asphalt.Sample(sampler_type, pixel_input.TexCoord * 10.0f);

      grass_color *= matmap_color.g;
      moss_color *= matmap_color.r;
      asphalt_color *= matmap_color.b;
      
      color_result *= (grass_color + moss_color + asphalt_color);
      //color_result = matmap_color;
    }break;
  }

  return color_result;
}