#pragma once
#include "Object.h"
#include "Component.h"

class GameObject :public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
public:
	void Initialize();
	void LateInitialize();
	void Update();
	void LateUpdate();
	void FinalUpdate();
	void Render();
public:
	void AddComponent(shared_ptr<Component> component);
	
public:
	shared_ptr<class Transform> GetTransform();
	shared_ptr<class MeshRender> GetMeshRender();
	

protected:
	array<shared_ptr<Component>, MONOBEHAVIOUR_EXCLUSION_COUNT> mComponentArray;
	vector<shared_ptr<Component>> mScriptVector;

};

