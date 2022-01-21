#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Light.h"
#include "Shader.h"
#include "Camera.h"
#include "RenderTargetGroup.h"
#include "GameEngine.h"
#include "MeshRender.h"
#include "Material.h"

void Scene::Initialize()
{
	LoadObject();

	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->Initialize();
	}

	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->LateInitialize();
	}

	
}

void Scene::Update()
{
	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->Update();
	}

	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->LateUpdate();
	}

	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->FinalUpdate();
	}

	int count = 0;
	for (auto& lightobject : mLightVector)
	{
		lightobject->FinalUpdate();
		lightparams.lights[count] = static_pointer_cast<Light>(lightobject->GetLight())->GetLightInfo();
		count++;
	}

	PushLightData();

}

void Scene::Render()
{

	/*for (auto& gameobject : mGameObjectVector)
	{
		gameobject->Render();
	}*/

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView();
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->ClearRenderTargetView();
	


	for (auto& gameObject : mGameObjectVector)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->SortGameObject();

		
		
		GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->OMSetRenderTargets();
		gameObject->GetCamera()->Render_Deferred();

		GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTargets();
		gameObject->GetCamera()->Render_Forward();

	}

	//GEngine->GetDeviceContext()->ClearDepthStencilView(_dsTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Scene::LoadObject()
{
}

void Scene::PushLightData()
{
	
	lightparams.lightCount = mLightVector.size();
	lightparams.padding1 = 0;
	lightparams.padding2 = 0;
	lightparams.padding3 = 0;
	

	for (auto& gameobject : mGameObjectVector)
	{
		if (gameobject->GetCamera())
			continue;
		gameobject->GetMeshRender()->GetMaterial()->GetShader()->PushLightData(lightparams);
	}


	
	//mlightShader->PushLightData(lightparams);


}
