#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"

void TestScene::Initialize()
{
	
	
	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->Initialize();
	}

	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->LateInitialize();
	}



}

void TestScene::Update()
{
	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->Update();
	}
	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->LateUpdate();
	}
}

void TestScene::Render()
{
	for (auto& gameobject : mGameObjectVector)
	{
		gameobject->Render();
	}
	

}
