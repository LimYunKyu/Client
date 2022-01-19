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

void SceneManager::SetLayerName(UINT8 index, const wstring& name)
{
	const wstring& prevName = _layerNames[index];
	_layerIndex.erase(prevName);

	_layerNames[index] = name;
	_layerIndex[name] = index;
}

UINT8 SceneManager::LayerNameToIndex(const wstring& name)
{
	auto findIt = _layerIndex.find(name);
	if (findIt == _layerIndex.end())
		return 0;

	return findIt->second;
}
