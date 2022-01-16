#pragma once
#include "Component.h"
class MeshRender :public Component
{
public:
	MeshRender();
public:
	virtual void Initialize();
	virtual void LateInitialize();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();
	virtual void Render();

public:
	shared_ptr<class Material> GetMaterial() { return mMaterial; }
	shared_ptr<class Mesh>	   GetMesh() { return mMesh; }

public:
	void SetMaterial(shared_ptr<class Material> material) { mMaterial = material; }
	void SetMesh(shared_ptr<class Mesh> mesh) { mMesh = mesh; }
private:
	shared_ptr<class Material> mMaterial;
	shared_ptr<class Mesh> mMesh;

};

