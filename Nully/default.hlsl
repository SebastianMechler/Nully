cbuffer VS_CONSTANT_BUFFER : register(cb0)
{
	float4x4 world;
	float4x4 view;
	float4x4 projection;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PS_INPUT VS_Main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	//output.position = input.position;//mul(float4(input.position, 1), mvp);
	//output.position = mul(float4(input.position.xyz, 1), mvp);
	output.position = mul(mul(mul(float4(input.position.xyz, 1), world), view), projection);
	output.color = input.color;

	return output;
}

float4 PS_Main(PS_INPUT input) : SV_TARGET
{
  return float4(input.color.xyz, 1);
}