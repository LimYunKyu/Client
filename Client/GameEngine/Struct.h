#pragma once
#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

struct WindowInfo {

	HWND		hwnd;
	FLOAT	ClientWidth;
	FLOAT	ClientHeight;
	bool		IsWindow;

};


struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
	XMFLOAT3 Normal;
	XMFLOAT3 Tangent;
	

};

enum class LIGHT_TYPE
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
};

struct LightColor
{
	XMVECTOR	diffuse;
	XMVECTOR	ambient;
	XMVECTOR	specular;
};

struct LightInfo
{
	LightColor	color;
	XMVECTOR		position;
	XMVECTOR		direction;
	INT32		lightType;
	float		range;
	float		angle;
	INT32		padding;
};

struct LightParams
{
	UINT32		lightCount;
	INT32	padding1;
	INT32	padding2;
	INT32	padding3;
	LightInfo	lights[50];
};



struct TransformParams
{
	XMMATRIX matWorld;
	XMMATRIX matView;
	XMMATRIX matProjection;
	XMMATRIX matWV;
	XMMATRIX matWVP;
};

struct TEXTURE_ON {
	int Tex0_On;
	int Tex1_On;
	int Tex2_On;
	int Tex3_On;
	int Tex4_On;


};

