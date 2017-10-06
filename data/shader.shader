cbuffer MatrixBuffer {
	matrix model_matrix;
	matrix view_matrix;
	matrix projection_matrix;
};

struct VertexInput
{
	float4 position : POSITION;
};

struct PixelInput
{
	float4 position : SV_POSITION;
};

PixelInput VShader(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, model_matrix);
	output.position = mul(output.position, view_matrix);
	output.position = mul(output.position, projection_matrix);

	return output;
}

Texture2D texture_shader;
SamplerState sampler_type;

float4 PShader(PixelInput pixel_input) : SV_TARGET
{
	float4 final_color = { 1.0, 0.0, 0.0, 1.0 };

	return final_color;
}