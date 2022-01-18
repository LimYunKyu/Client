#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Light.h"
#include "Shader.h"
#include "Camera.h"

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

	for (auto& gameObject : mGameObjectVector)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render();
	}
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
	mShader->PushLightData(lightparams);


}
