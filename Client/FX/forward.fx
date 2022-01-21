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
	float2 Tex     : TEXCOORD;
	float4 pos  : SV_POSITION;
	float3 viewPos : POSITION;
	float3 viewNormal : NORMAL;
	float3 viewTangent : TANGENT;
	float3 viewBinormal : BINORMAL;
	
};

VertexOut VS(VertexIn vin) 
{
	VertexOut vout = (VertexOut)0;
	vout.pos = mul(float4(vin.pos, 1.0f), g_TransformParmas.g_matWVP);
	vout.pos.z = 0.f;
	vout.viewPos = mul(float4(vin.pos, 1.f), g_TransformParmas.g_matWV).xyz;
	vout.viewNormal = normalize(mul(float4(vin.normal, 0.f), g_TransformParmas.g_matWV).xyz);
	vout.viewTangent = normalize(mul(float4(vin.tangent, 0.f), g_TransformParmas.g_matWV).xyz);
	vout.viewBinormal = normalize(cross(vout.viewTangent, vout.viewNormal));
	vout.Tex = vin.Tex;
	

	return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 color = float4(1.f, 1.f, 1.f,1.f);
	
	

	float3 viewNormal = pin.viewNormal;

	if (g_Tex_On.g_tex_0_on)
	{
		color = g_tex_0.Sample(samLinear, pin.Tex);
	}
	
	if (g_Tex_On.g_tex_1_on)
	{
		float3 tangentSpaceNormal = g_tex_1.Sample(samLinear, pin.Tex);

		tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.f;

		float3x3 matTBN = { pin.viewTangent, pin.viewBinormal, pin.viewNormal };
		viewNormal = normalize(mul(tangentSpaceNormal, matTBN));
	}


	LightColor totalColor = (LightColor)0.f;

	
	for (int i = 0; i < g_lightParams.g_lightCount; ++i)
	{
		 LightColor color = CalculateLightColor(i, viewNormal, pin.viewPos);
		 totalColor.diffuse += color.diffuse;
		 totalColor.ambient += color.ambient;
		 totalColor.specular += color.specular;
		//color = float4(1.f, 0.f, 1.f, 1.f);
		 //totalColor = (LightColor)1.f;
	}

	color.xyz = (totalColor.diffuse.xyz * color.xyz)
		+ totalColor.ambient.xyz * color.xyz
		+ totalColor.specular.xyz;

	/*color = texColor * color;*/


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