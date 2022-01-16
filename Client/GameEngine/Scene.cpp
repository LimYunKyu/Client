#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
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

}

void Scene::Render()
{
	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->Render();
	}
}

void Scene::LoadObject()
{
}
