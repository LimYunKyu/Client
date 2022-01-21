#include "params.fx"
#include "utils.fx"

struct VertexIn
{
	
	float3 pos    : POSITION;
	float2 Tex    : TEXCOORD;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
};

struct VertexOut
{
	
	float4 pos  : SV_POSITION;
	float2 Tex     : TEXCOORD;
	float3 viewPos : POSITION;
	float3 viewNormal : NORMAL;
	float3 viewTangent : TANGENT;
	float3 viewBinormal : BINORMAL;
	
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout = (VertexOut)0;
	vout.pos = mul(float4(vin.pos, 1.0f), g_TransformParmas.g_matWVP);
	vout.Tex = vin.Tex;

	vout.viewPos = mul(float4(vin.pos, 1.f), g_TransformParmas.g_matWV).xyz;
	vout.viewNormal = normalize(mul(float4(vin.normal, 0.f), g_TransformParmas.g_matWV).xyz);
	vout.viewTangent = normalize(mul(float4(vin.tangent, 0.f), g_TransformParmas.g_matWV).xyz);
	vout.viewBinormal = normalize(cross(vout.viewTangent, vout.viewNormal));

	

	return vout;
}

struct PS_OUT
{
	float4 position : SV_Target0;
	float4 normal : SV_Target1;
	float4 color : SV_Target2;
};


PS_OUT PS(VertexOut pin) 
{
	PS_OUT output = (PS_OUT)0;

	float4 color = float4(0.f, 0.f, 0.f,0.f);
	


	if (g_Tex_On.g_tex_0_on)
	{
		color = g_tex_0.Sample(samLinear, pin.Tex);
	}
	
	float3 viewNormal = pin.viewNormal;
	if (g_Tex_On.g_tex_1_on)
	{
		float3 tangentSpaceNormal = g_tex_1.Sample(samLinear, pin.Tex).xyz;

		tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.f;

		float3x3 matTBN = { pin.viewTangent, pin.viewBinormal, pin.viewNormal };
		viewNormal = normalize(mul(tangentSpaceNormal, matTBN));
	}

	output.position =  float4(pin.viewPos.xyz, 0.f);
	output.normal =  float4(viewNormal.xyz, 0.f);
	output.color =  color;


	return output;
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