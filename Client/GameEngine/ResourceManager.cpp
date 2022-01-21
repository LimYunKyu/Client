#include "pch.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"

shared_ptr<Mesh> ResourceManager::LoadRectangleMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Rectangle");
	if (findMesh)
		return findMesh;

	float w2 = 0.5f;
	float h2 = 0.5f;

	vector<Vertex> vec(4);
	vec =
	{
		{ XMFLOAT3(-1.0f, -1.0f, 0.f),XMFLOAT2(0.0f,1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, 0.f),XMFLOAT2(0.0f,0.0f),XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(+1.0f, +1.0f, 0.f),XMFLOAT2(1.0f,0.0f),XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(+1.0f, -1.0f, 0.f),XMFLOAT2(1.0f,1.0f),XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
	};



	vector<UINT32> idx(6);

	// æ’∏È
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->CreateVertexBuffer(vec);
	mesh->CreateIndexBuffer(idx);
	Add(L"Rectangle", mesh);

	return mesh;
}

shared_ptr<Mesh> ResourceManager::LoadCubeMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Cube");
	if (findMesh)
		return findMesh;

	vector<Vertex> vertices(24);
	vertices = {

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT2(0.0f,1.0f),XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f),XMFLOAT2(0.0f,0.0f),XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f),XMFLOAT2(1.0f,0.0f),XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f),XMFLOAT2(1.0f,1.0f),XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f),XMFLOAT2(1.0f,1.0f),XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f),XMFLOAT2(0.0f,1.0f),XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f),XMFLOAT2(0.0f,0.0f),XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f),XMFLOAT2(1.0f,0.0f),XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},

		{ XMFLOAT3(-1.0f, +1.0f, -1.0f),XMFLOAT2(0.0f,1.0f),XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f),XMFLOAT2(0.0f,0.0f),XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f),XMFLOAT2(1.0f,0.0f),XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f),XMFLOAT2(1.0f,1.0f),XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f)},

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT2(1.0f,1.0f),XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f),XMFLOAT2(0.0f,1.0f),XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f),XMFLOAT2(0.0f,0.0f),XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f),XMFLOAT2(1.0f,0.0f),XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f)},

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f),XMFLOAT2(0.0f,1.0f),XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f),XMFLOAT2(0.0f,0.0f),XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f),XMFLOAT2(1.0f,0.0f),XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT2(1.0f,1.0f),XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f)},

		{ XMFLOAT3(+1.0f, -1.0f, -1.0f),XMFLOAT2(0.0f,1.0f),XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f),XMFLOAT2(0.0f,0.0f),XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f),XMFLOAT2(1.0f,0.0f),XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f),XMFLOAT2(1.0f,1.0f),XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f)},

	};

	vector<UINT32> indices;
	indices = {
		0, 1, 2,
		0, 2, 3,

		//back face
		4, 5, 6,
		4, 6, 7,

		// left face
		8, 9, 10,
		8, 10, 11,

		// right face
		12, 13, 14,
		12, 14, 15,

		// top face
		16, 17, 18,
		16, 18, 19,

		// bottom face
		20, 21, 22,
		20, 22, 23
	};

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->CreateVertexBuffer(vertices);
	mesh->CreateIndexBuffer(indices);
	Add(L"Cube", mesh);

	return mesh;


}

shared_ptr<Mesh> ResourceManager::LoadSphereMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Sphere");
	if (findMesh)
		return findMesh;

	float radius = 0.5f; // ±∏¿« π›¡ˆ∏ß
	UINT32 stackCount = 20; // ∞°∑Œ ∫–«“
	UINT32 sliceCount = 20; // ºº∑Œ ∫–«“

	XMVECTOR Nomalize;

	vector<Vertex> vec;

	Vertex v;

	// ∫œ±ÿ
	v.Pos = XMFLOAT3(0.0f, radius, 0.0f);
	Nomalize = { v.Pos.x,v.Pos.y,v.Pos.z };
	v.Tex = XMFLOAT2(0.5f, 0.0f);
	v.Normal = v.Pos;
	XMStoreFloat3(&(v.Normal), XMVector3Normalize(XMVECTOR(Nomalize)));
	v.Tangent = XMFLOAT3(1.0f, 0.0f, 1.0f);
	vec.push_back(v);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	// ∞Ì∏Æ∏∂¥Ÿ µπ∏Èº≠ ¡§¡°¿ª ∞ËªÍ«—¥Ÿ (∫œ±ÿ/≥≤±ÿ ¥‹¿œ¡°¿∫ ∞Ì∏Æ∞° X)
	for (UINT32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		// ∞Ì∏Æø° ¿ßƒ°«— ¡§¡°
		for (UINT32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			v.Pos.x = radius * sinf(phi) * cosf(theta);
			v.Pos.y = radius * cosf(phi);
			v.Pos.z = radius * sinf(phi) * sinf(theta);

			v.Tex = XMFLOAT2(deltaU * x, deltaV * y);

			v.Normal = v.Pos;
			Nomalize = { v.Pos.x,v.Pos.y,v.Pos.z };
			XMStoreFloat3(&(v.Normal), XMVector3Normalize(XMVECTOR(Nomalize)));

			v.Tangent.x = -radius * sinf(phi) * sinf(theta);
			v.Tangent.y = 0.0f;
			v.Tangent.z = radius * sinf(phi) * cosf(theta);
			Nomalize = { v.Tangent.x,v.Tangent.y,v.Tangent.z };
			XMStoreFloat3(&(v.Tangent), XMVector3Normalize(XMVECTOR(Nomalize)));;

			vec.push_back(v);
		}
	}

	// ≥≤±ÿ
	v.Pos = XMFLOAT3(0.0f, -radius, 0.0f);
	v.Tex = XMFLOAT2(0.5f, 1.0f);
	v.Normal = v.Pos;
	Nomalize = { v.Pos.x,v.Pos.y,v.Pos.z };
	XMStoreFloat3(&(v.Normal), XMVector3Normalize(XMVECTOR(Nomalize)));
	v.Tangent = XMFLOAT3(1.0f, 0.0f, 0.0f);
	vec.push_back(v);

	vector<UINT32> idx(36);

	// ∫œ±ÿ ¿Œµ¶Ω∫
	for (UINT32 i = 0; i <= sliceCount; ++i)
	{
		//  [0]
		//   |  \
		//  [i+1]-[i+2]
		idx.push_back(0);
		idx.push_back(i + 2);
		idx.push_back(i + 1);
	}

	// ∏ˆ≈Î ¿Œµ¶Ω∫
	UINT32 ringVertexCount = sliceCount + 1;
	for (UINT32 y = 0; y < stackCount - 2; ++y)
	{
		for (UINT32 x = 0; x < sliceCount; ++x)
		{
			//  [y, x]-[y, x+1]
			//  |		/
			//  [y+1, x]
			idx.push_back(1 + (y)*ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			//		 [y, x+1]
			//		 /	  |
			//  [y+1, x]-[y+1, x+1]
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	// ≥≤±ÿ ¿Œµ¶Ω∫
	UINT32 bottomIndex = static_cast<UINT32>(vec.size()) - 1;
	UINT32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (UINT32 i = 0; i < sliceCount; ++i)
	{
		//  [last+i]-[last+i+1]
		//  |      /
		//  [bottom]
		idx.push_back(bottomIndex);
		idx.push_back(lastRingStartIndex + i);
		idx.push_back(lastRingStartIndex + i + 1);
	}

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->CreateVertexBuffer(vec);
	mesh->CreateIndexBuffer(idx);
	Add(L"Sphere", mesh);

	return mesh;
}

shared_ptr<Texture> ResourceManager::CreateTexture(const wstring& name, DXGI_FORMAT format, UINT32 width, UINT32 height, XMFLOAT4 clearColor, D3D11_BIND_FLAG flag)
{
	shared_ptr<Texture> texture = make_shared<Texture>();
	texture->CreateTexture(format, width, height, clearColor, flag);
	Add(name, texture);

	return texture;
}

shared_ptr<Texture> ResourceManager::CreateTextureFromResource(const wstring& name, ID3D11Texture2D* tex2D)
{
	shared_ptr<Texture> texture = make_shared<Texture>();
	texture->CreateTextureFromResource(tex2D);
	Add(name, texture);

	return texture;
}

void ResourceManager::Initialize()
{
	CreateDefaultShader();
}

void ResourceManager::CreateDefaultShader()
{


	{
		shared_ptr<Shader> shader = make_shared<Shader>(L"..\\FX\\forward.fx", "DefaultTech", SHADER_TYPE::FORWARD);
		Add<Shader>(L"Forward", shader);


	}

	{
		shared_ptr<Shader> shader = make_shared<Shader>(L"..\\FX\\skybox.fx", "DefaultTech", SHADER_TYPE::FORWARD, RASTERIZER_TYPE::CULL_NONE, DEPTH_STENCIL_TYPE::LESS_EQUAL);
		Add<Shader>(L"Skybox", shader);
	}

	{
		shared_ptr<Shader> shader = make_shared<Shader>(L"..\\FX\\deferred.fx", "DefaultTech", SHADER_TYPE::DEFERRED);
		Add<Shader>(L"Deferred", shader);
	}
}
