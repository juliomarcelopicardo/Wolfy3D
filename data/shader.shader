cbuffer MatrixBuffer {
	matrix model_matrix;
	matrix view_matrix;
	matrix projection_matrix;
};

struct VertexInput
{
	float4 vPosition : POSITION;
	float4 vNormal : NORMAL0;
	float2 vTexCoord : TEXCOORD0;
	float4 vColor : COLOR0;
};

struct PixelInput
{
	float4 Position : SV_POSITION;
	float4 Normal : NORMAL0;
	float2 TexCoord : TEXCOORD0;
	float4 Color : COLOR0;
};

PixelInput VShader(VertexInput input)
{
	PixelInput output;

	output.Position = mul(input.vPosition, model_matrix);
	output.Position = mul(output.Position, view_matrix);
	output.Position = mul(output.Position, projection_matrix);
	output.Color = input.vColor;
	output.Normal = input.vNormal;
	output.TexCoord = input.vTexCoord;

	return output;
}

Texture2D texture_shader;
SamplerState sampler_type;

float4 PShader(PixelInput pixel_input) : SV_TARGET
{
	float4 texture_color;
	texture_color = texture_shader.Sample(sampler_type, pixel_input.TexCoord);
  float4 grey_color = pixel_input.Normal;
  grey_color.y *= 0.1f;
  grey_color.x = grey_color.y;
  grey_color.z = grey_color.y;
	return grey_color;
}