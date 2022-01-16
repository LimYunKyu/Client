#include "params.fx"
#include "utils.fx"

struct VertexIn
{
	
	float3 pos    : POSITION;
	float3 normal : NORMAL;
	float2 Tex    : TEXCOORD;
	
};

struct VertexOut
{
	float2 Tex     : TEXCOORD;
	float4 pos  : SV_POSITION;
	float3 viewPos : POSITION;
	float3 viewNormal : NORMAL;
	
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout = (VertexOut)0;
	vout.pos = mul(float4(vin.pos, 1.0f), g_TransformParmas.g_matWVP);
	vout.Tex = vin.Tex;
	

	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 color = float4(1.0f,1.0f,1.0f,1.0f);
	float4 texColor = float4(1.0f, 1.0f, 1.0f, 1.0f);


	if (g_Tex_On.g_tex_0_on)
	{
	   texColor = g_tex_0.Sample(samLinear, pin.Tex) * color;
	   color = texColor;
	}
	

	return texColor;
}

technique11 DefaultTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}