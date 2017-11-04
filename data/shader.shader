cbuffer CustomConstantBuffer {
	matrix model_matrix;
	matrix view_matrix;
	matrix projection_matrix;
  float timer;
  float time1;
  float time2;
  float time3;
};

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

Texture2D texture_shader;
SamplerState sampler_type;

// EJEMPLO PARA TESTEAR LUCES.
struct Light {
  float4 dir;
  float4 color;
  float intensity;
};

float4 PShader(PixelInput pixel_input) : SV_TARGET {

  // Calculamos el color de la textura.
	float4 texture_color;
	texture_color = texture_shader.Sample(sampler_type, pixel_input.TexCoord);

  // Calculamos el color difuso de la luz.
  Light light;
  light.dir = float4(1.0f, 1.0f, 0.0f, 0.0f);
  light.dir.x = sin(timer * 0.001f);
  light.dir.y = cos(timer * 0.001f);
  light.color = float4(1.0f, 1.0f, 0.0f, 1.0f);
  light.intensity = 0.7f;
  float diffuse = max(dot(normalize(pixel_input.Normal), light.dir), 0.0);
  float4 light_final_color = diffuse * light.color * light.intensity;
  
  // Retornamos el color final del pixel.
  return pixel_input.Color * light_final_color;
}