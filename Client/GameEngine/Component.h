#pragma once
#include "Object.h"

enum class COMPONENT_TYPE {

	TRANSFORM,
	MESHRENDER,
	CAMERA,
	LIGHT,
	MONOBEHAVIOUR,
	END,
};

enum {


	MONOBEHAVIOUR_EXCLUSION_COUNT = static_cast<UINT32>(COMPONENT_TYPE::END) - 1,
	COMPONENT_TYPE_COUNT = COMPONENT_TYPE::END,

};

class Component : public Object
{
public:
	Component(COMPONENT_TYPE Type);
	void SetGameObject(shared_ptr<class GameObject> object) { mGameObject = object; }
	COMPONENT_TYPE GetComponentType() { return mComponentType; }

public:
	virtual void Initialize()=0;
	virtual void LateInitialize()=0;
	virtual void Update()=0;
	virtual void LateUpdate()=0;
	virtual void FinalUpdate()=0;
	virtual void Render()=0;
protected:
	COMPONENT_TYPE mComponentType;
	weak_ptr<class GameObject> mGameObject;

};

