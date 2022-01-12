#include "pch.h"
#include "GameObject.h"
#include "MonoBehaviour.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{


}

void GameObject::Initialize()
{

	for (auto& component : mComponentArray)
	{
		if(component)
		component->Initialize();
	}

	for (auto& script : mScriptVector)
	{
		script->Initialize();
	}


}

void GameObject::LateInitialize()
{
	for (auto& component : mComponentArray)
	{
		if (component)
		component->LateInitialize();
	}

	for (auto& script : mScriptVector)
	{
		script->LateInitialize();
	}
}

void GameObject::Update()
{
	for (auto& component : mComponentArray)
	{
		if (component)
			component->Update();
	}

	for (auto& script : mScriptVector)
	{
		script->Update();
	}

}

void GameObject::LateUpdate()
{
	for (auto& component : mComponentArray)
	{
		if (component)
			component->LateUpdate();
	}

	for (auto& script : mScriptVector)
	{
		script->LateUpdate();
	}
}

void GameObject::Render()
{
	for (auto& component : mComponentArray)
	{
		if (component)
			component->Render();
	}

	for (auto& script : mScriptVector)
	{
		script->Render();
	}
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	int type = static_cast<int>(component->GetComponentType());

	if (type < MONOBEHAVIOUR_EXCLUSION_COUNT)
	{
		mComponentArray[type] = component;
	}
	else
	{
		mScriptVector.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}


}


