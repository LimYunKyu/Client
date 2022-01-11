#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"



void SceneManager::Update()
{

	if (mCurrentScene.get() != nullptr)
		mCurrentScene->Update();

}

void SceneManager::Render()
{
	if (mCurrentScene.get() != nullptr)
		mCurrentScene->Render();
}

void SceneManager::SetScene(shared_ptr<class Scene> scene)
{
	mCurrentScene = scene;
	mCurrentScene->Initialize();

}
