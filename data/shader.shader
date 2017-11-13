/*
  CONSTANT BUFFERS
*/

cbuffer CustomConstantBuffer {
	matrix model_matrix;
	matrix view_matrix;
	matrix projection_matrix;
  unsigned int type;
  float timer;
  float time2;
  float time3;
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
};

/*
  VERTEX SHADER
*/

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

	return output;
}

Texture2D texture_ : register(t0);
Texture2D texture_2 : register(t1);
SamplerState sampler_type;

// EJEMPLO PARA TESTEAR LUCES.
struct Light {
  float4 dir;
  float4 color;
  float intensity;
};

#define DIFFUSE 0
#define ONE_TEXTURE 1
#define NORMALS 2

float4 CalculateLightColor(float4 normal) {
  // Calculamos el color difuso de la luz.
  Light light;
  light.dir = float4(1.0f, 1.0f, -1.0f, 0.0f);
  //light.dir.x = sin(timer * 0.001f);
  //light.dir.y = cos(timer * 0.001f);
  light.color = float4(1.0f, 1.0f, 1.0f, 1.0f);
  light.intensity = 0.9f;
  float diffuse = max(dot(normalize(normal), light.dir), 0.0);
  return diffuse * light.color * light.intensity;
}

float4 PShader(PixelInput pixel_input) : SV_TARGET {
  
  float4 color_result = pixel_input.Color * CalculateLightColor(pixel_input.Normal);

  switch (type) {

    case DIFFUSE:{}break;
  
    case ONE_TEXTURE: {
      /* TESTEANDO PONER DOS TEXTURAS A LA VEZ*/
      if (pixel_input.TexCoord.x > 0.5f) {
        color_result *= texture_2.Sample(sampler_type, pixel_input.TexCoord);
      }
      else {
        color_result *= texture_.Sample(sampler_type, pixel_input.TexCoord);
      }
    }break;
  
    case NORMALS: {
      color_result = pixel_input.Normal;
    }break;

  }

  return color_result;
}