#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "MeshRender.h"
#include "Shader.h"
#include "Material.h"
#include "CameraScript.h"
#include "Camera.h"
#include "Texture.h"
void TestScene::LoadObject()
{
	//
	//          큐브
	//

	shared_ptr<GameObject> Cube = make_shared<GameObject>();
	mGameObjectVector.push_back(Cube);

	shared_ptr<Transform>  CubeTransform = make_shared<Transform>();
	CubeTransform->SetTranslate(XMFLOAT3(0.f, 0.f, 5.f));
	CubeTransform->SetRotateX(0.0f);
	CubeTransform->SetRotateY(0.f);
	CubeTransform->SetRotateZ(0.f);
	CubeTransform->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));

	Cube->AddComponent(CubeTransform);

	shared_ptr<MeshRender> CubeMeshRender = make_shared<MeshRender>();
	Cube->AddComponent(CubeMeshRender);

	shared_ptr<Material>   CubeMaretial   =  make_shared<Material>();
	CubeMeshRender->SetMaterial(CubeMaretial);

	shared_ptr<Mesh>	   CubeMesh = make_shared<Mesh>();
	CubeMeshRender->SetMesh(CubeMesh);

	vector<Vertex> vertices(24);
	vertices = {

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT3(-1.0f, +1.0f, -1.0f),XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT3(+1.0f, +1.0f, -1.0f),XMFLOAT2(1.0f,0.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT3(+1.0f, -1.0f, -1.0f),XMFLOAT2(1.0f,1.0f)},

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT3(-1.0f, -1.0f, +1.0f),XMFLOAT2(1.0f,1.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT3(+1.0f, -1.0f, +1.0f),XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f),XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT3(-1.0f, +1.0f, +1.0f),XMFLOAT2(1.0f,0.0f)},

		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT3(-1.0f, +1.0f, -1.0f),XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT3(-1.0f, +1.0f, +1.0f),XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f),XMFLOAT2(1.0f,0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT3(+1.0f, +1.0f, -1.0f),XMFLOAT2(1.0f,1.0f)},

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT2(1.0f,1.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT3(+1.0f, -1.0f, -1.0f),XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT3(+1.0f, -1.0f, +1.0f),XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT3(-1.0f, -1.0f, +1.0f),XMFLOAT2(1.0f,0.0f)},

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), XMFLOAT3(-1.0f, -1.0f, +1.0f),XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), XMFLOAT3(-1.0f, +1.0f, +1.0f),XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), XMFLOAT3(-1.0f, +1.0f, -1.0f),XMFLOAT2(1.0f,0.0f)},
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f),XMFLOAT2(1.0f,1.0f)},

		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), XMFLOAT3(+1.0f, -1.0f, -1.0f),XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), XMFLOAT3(+1.0f, +1.0f, -1.0f),XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), XMFLOAT3(+1.0f, +1.0f, +1.0f),XMFLOAT2(1.0f,0.0f)},
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), XMFLOAT3(+1.0f, -1.0f, +1.0f),XMFLOAT2(1.0f,1.0f)},

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

	CubeMesh->CreateVertexBuffer(vertices);
	CubeMesh->CreateIndexBuffer(indices);

	shared_ptr<Shader>	   CubeShader = make_shared<Shader>(L"..\\FX\\default.fx", "DefaultTech");
	CubeMaretial->SetShader(CubeShader);

	shared_ptr<Texture>    CubeTexture = make_shared<Texture>();
	CubeMaretial->SetTexture(CubeTexture);
	CubeTexture->CreateTexture(L"../Texture/veigar.jpg", 0);
	


	//
	//          큐브 끝
	//


	//
	//          카메라
	//


	shared_ptr<GameObject> CameraObj = make_shared<GameObject>();
	mGameObjectVector.push_back(CameraObj);

	shared_ptr<Transform>  CameraTransform = make_shared<Transform>();
	CameraTransform->SetTranslate(XMFLOAT3(0.f, 0.f, -5.f));
	CameraTransform->SetRotateX(0.0f);
	CameraTransform->SetRotateY(0.f);
	CameraTransform->SetRotateZ(0.f);
	CameraTransform->SetScale(XMFLOAT3(1.f, 1.f, 1.f));

	CameraObj->AddComponent(CameraTransform);
	shared_ptr<CameraScript> camerascript = make_shared<CameraScript>();
	CameraObj->AddComponent(camerascript);

	shared_ptr<Camera> CameraComponent = make_shared<Camera>();
	CameraObj->AddComponent(CameraComponent);


}
