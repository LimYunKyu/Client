#include "params.fx"


struct VertexIn
{
	
	float3 pos    : POSITION;
	float2 Tex    : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
};

struct VertexOut
{
	float4 pos : SV_Position;
	float2 Tex : TEXCOORD;
	
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout = (VertexOut)0;

	float4 viewPos = mul(float4(vin.pos, 0), g_TransformParmas.g_matView);
	float4 clipSpacePos = mul(viewPos, g_TransformParmas.g_matProjection);
	
	vout.pos = clipSpacePos.xyww;
	vout.Tex = vin.Tex;

	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 color = float4(1.f, 1.f, 1.f,1.f);
	
	

	if (g_Tex_On.g_tex_0_on)
	{
		color = g_tex_0.Sample(samLinear, pin.Tex);
	}
	
	


	return color;
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