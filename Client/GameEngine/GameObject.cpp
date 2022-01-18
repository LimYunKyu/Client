#include "pch.h"
#include "GameObject.h"
#include "MonoBehaviour.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Light.h"
#include "Camera.h"

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

void GameObject::FinalUpdate()
{
	for (auto& component : mComponentArray)
	{
		if (component)
			component->FinalUpdate();
	}

	for (auto& script : mScriptVector)
	{
		script->FinalUpdate();
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



shared_ptr<class Transform> GameObject::GetTransform()
{
	int idx = static_cast<int>(COMPONENT_TYPE::TRANSFORM);
	shared_ptr<Component> component = mComponentArray[idx];
	return static_pointer_cast<Transform>(component);
}

shared_ptr<class MeshRender> GameObject::GetMeshRender()
{
	int idx = static_cast<int>(COMPONENT_TYPE::MESHRENDER);
	shared_ptr<Component> component = mComponentArray[idx];
	return static_pointer_cast<MeshRender>(component);
}

shared_ptr<class Light> GameObject::GetLight()
{
	int idx = static_cast<int>(COMPONENT_TYPE::LIGHT);
	shared_ptr<Component> component = mComponentArray[idx];
	return static_pointer_cast<Light>(component);
}

shared_ptr<class Camera> GameObject::GetCamera()
{
	int idx = static_cast<int>(COMPONENT_TYPE::CAMERA);
	shared_ptr<Component> component = mComponentArray[idx];

	if (component != nullptr)
	{
		return static_pointer_cast<Camera>(component);
	}
	else
	{
		return nullptr;
	}

	

}


