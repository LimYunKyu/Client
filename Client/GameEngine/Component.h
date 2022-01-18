#pragma once
#include "Object.h"

enum class COMPONENT_TYPE {

	TRANSFORM,
	CAMERA,
	LIGHT,
	MESHRENDER,
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


protected:
	COMPONENT_TYPE mComponentType;
	weak_ptr<class GameObject> mGameObject;

};

