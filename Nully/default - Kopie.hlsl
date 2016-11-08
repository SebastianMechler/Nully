cbuffer VS_CONSTANT_BUFFER : register(b0)
{
	matrix mvp;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 uv : TEXCOORD;
};

PS_INPUT VS_Main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.position = input.position;//mul(float4(input.position, 1), mvp);
	output.color = input.color;
	output.uv = input.uv;

	return output;
}

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
  return float4(1,1,1,1);
}