#pragma once
#include "Object.h"
#include "Component.h"

class Transform;
class MeshRenderer;
class Camera;
class Light;
class MonoBehaviour;

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
	void SetCheckFrustum(bool checkFrustum) { _checkFrustum = checkFrustum; }
	bool GetCheckFrustum() { return _checkFrustum; }
	
public:
	shared_ptr<class Transform> GetTransform();
	shared_ptr<class MeshRender> GetMeshRender();
	shared_ptr<class Light> GetLight();
	shared_ptr<class Camera> GetCamera();

	void SetLayerIndex(UINT8 layer) { _layerIndex = layer; }
	UINT8 GetLayerIndex() { return _layerIndex; }

protected:
	array<shared_ptr<Component>, MONOBEHAVIOUR_EXCLUSION_COUNT> mComponentArray;
	vector<shared_ptr<Component>> mScriptVector;
	bool _checkFrustum = true;

	UINT8 _layerIndex = 0;

};

