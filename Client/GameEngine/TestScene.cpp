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
#include "Light.h"
#include "ResourceManager.h"
#include "SceneManager.h"

void TestScene::LoadObject()
{
	//
	//          큐브
	// 
	// 
	

	SceneManager::GetInstance()->SetLayerName(0, L"Default");
	SceneManager::GetInstance()->SetLayerName(1, L"UI"); 

	{

		shared_ptr<GameObject> Cube = make_shared<GameObject>();
		mGameObjectVector.push_back(Cube);

		shared_ptr<Transform>  CubeTransform = make_shared<Transform>();
		CubeTransform->SetTranslate(XMFLOAT3(-5.f, -2.f, 5.f));
		CubeTransform->SetRotateX(0.0f);
		CubeTransform->SetRotateY(0.f);
		CubeTransform->SetRotateZ(0.f);
		CubeTransform->SetScale(XMFLOAT3(1.f, 1.f, 1.f));

		Cube->AddComponent(CubeTransform);

		shared_ptr<MeshRender> CubeMeshRender = make_shared<MeshRender>();
		Cube->AddComponent(CubeMeshRender);

		shared_ptr<Material>   CubeMaretial = make_shared<Material>();
		CubeMeshRender->SetMaterial(CubeMaretial);

		CubeMeshRender->SetMesh(ResourceManager::GetInstance()->LoadCubeMesh());



		shared_ptr<Shader> CubeShader = ResourceManager::GetInstance()->Get<Shader>(L"Forward");
		mlightShader = CubeShader;
		CubeMaretial->SetShader(CubeShader);

		shared_ptr<Texture>    CubeTexture = ResourceManager::GetInstance()->Load<Texture>(L"Leather", L"../Texture/Leather.jpg");
		shared_ptr<Texture>    CubeNomslTexture = ResourceManager::GetInstance()->Load<Texture>(L"Leather_Normal", L"../Texture/Leather_Normal.jpg");

		CubeMaretial->SetTexture(CubeTexture, 0);
		CubeMaretial->SetTexture(CubeNomslTexture, 1);

	}

	{
		/// <summary>
		/// 오브젝트2
		/// </summary>
		shared_ptr<GameObject> Cube2 = make_shared<GameObject>();
		mGameObjectVector.push_back(Cube2);
		Cube2->SetCheckFrustum(false);
		shared_ptr<Transform>  CubeTransform2 = make_shared<Transform>();
		CubeTransform2->SetTranslate(XMFLOAT3(0.f, 0.f, 0.f));
		CubeTransform2->SetRotateX(0.0f);
		CubeTransform2->SetRotateY(0.f);
		CubeTransform2->SetRotateZ(0.f);
		CubeTransform2->SetScale(XMFLOAT3(10.f, 10.f, 10.f));

		Cube2->AddComponent(CubeTransform2);

		shared_ptr<MeshRender> CubeMeshRender2 = make_shared<MeshRender>();
		Cube2->AddComponent(CubeMeshRender2);

		shared_ptr<Material>   CubeMaretial2 = make_shared<Material>();
		CubeMeshRender2->SetMaterial(CubeMaretial2);

		CubeMeshRender2->SetMesh(ResourceManager::GetInstance()->LoadSphereMesh());

		shared_ptr<Shader> skyshader = ResourceManager::GetInstance()->Get<Shader>(L"Skybox");
		CubeMaretial2->SetShader(skyshader);

		shared_ptr<Texture>    CubeTexture2 = ResourceManager::GetInstance()->Load<Texture>(L"Sky01", L"../Texture/Sky01.jpg");
		CubeMaretial2->SetTexture(CubeTexture2, 0);


	}


	//빛

	{
		shared_ptr<GameObject> lightobject = make_shared<GameObject>();
		mLightVector.push_back(lightobject);
		shared_ptr<Light> LightComponent = make_shared<Light>();
		LightComponent->SetLightDirection({ 1.f,-1.f,0.f });
		LightComponent->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		LightComponent->SetDiffuse({ 0.5f,0.5f,0.5f });
		LightComponent->SetAmbient({ 0.1f,0.1f,0.1f });
		LightComponent->SetSpecular({ 0.5f,0.5f,0.5f });
		lightobject->AddComponent(LightComponent);

	}


	//
	//          카메라
	//

	//메인 카메라
	{

		shared_ptr<GameObject> CameraObj = make_shared<GameObject>();
		mGameObjectVector.push_back(CameraObj);
		CameraObj->SetName(L"Main_Camera");
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

		UINT8 layerIndex = SceneManager::GetInstance()->LayerNameToIndex(L"UI");
		CameraObj->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, true);
	}

	//직교투영 카메라
	{

		shared_ptr<GameObject> CameraObj = make_shared<GameObject>();
		mGameObjectVector.push_back(CameraObj);
		CameraObj->SetName(L"Orthographic_Camera");
		shared_ptr<Transform>  CameraTransform = make_shared<Transform>();
		CameraTransform->SetTranslate(XMFLOAT3(0.f, 0.f, 0.f));
		CameraTransform->SetRotateX(0.0f);
		CameraTransform->SetRotateY(0.f);
		CameraTransform->SetRotateZ(0.f);
		CameraTransform->SetScale(XMFLOAT3(1.f, 1.f, 1.f));


		CameraObj->AddComponent(CameraTransform);
		

		shared_ptr<Camera> CameraComponent = make_shared<Camera>();
		CameraObj->AddComponent(CameraComponent);

		CameraObj->GetCamera()->SetCameraType(PROJECTION_TYPE::ORTHOGRAPHIC);
		UINT8 layerIndex = SceneManager::GetInstance()->LayerNameToIndex(L"UI");
		CameraObj->GetCamera()->SetCullingMaskAll();
		CameraObj->GetCamera()->SetCullingMaskLayerOnOff(layerIndex, false);

	}

	//UI
	{

		shared_ptr<GameObject> Cube2 = make_shared<GameObject>();
		Cube2->SetLayerIndex(SceneManager::GetInstance()->LayerNameToIndex(L"UI"));
		mGameObjectVector.push_back(Cube2);
		Cube2->SetCheckFrustum(false);
		shared_ptr<Transform>  CubeTransform2 = make_shared<Transform>();
		CubeTransform2->SetTranslate(XMFLOAT3(-400.f, 0.f, 500.f));
		CubeTransform2->SetRotateX(0.0f);
		CubeTransform2->SetRotateY(0.f);
		CubeTransform2->SetRotateZ(0.f);
		CubeTransform2->SetScale(XMFLOAT3(100.f, 100.f, 100.f));

		Cube2->AddComponent(CubeTransform2);

		shared_ptr<MeshRender> CubeMeshRender2 = make_shared<MeshRender>();
		Cube2->AddComponent(CubeMeshRender2);

		shared_ptr<Material>   CubeMaretial2 = make_shared<Material>();
		CubeMeshRender2->SetMaterial(CubeMaretial2);

		CubeMeshRender2->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());

		shared_ptr<Shader> skyshader = ResourceManager::GetInstance()->Get<Shader>(L"Forward");
		CubeMaretial2->SetShader(skyshader);

		shared_ptr<Texture>    CubeTexture2 = ResourceManager::GetInstance()->Load<Texture>(L"Leather", L"../Texture/Leather.jpg");
		CubeMaretial2->SetTexture(CubeTexture2, 0);

	}

}
