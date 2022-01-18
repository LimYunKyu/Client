#include "pch.h"
#include "Light.h"
#include "GameObject.h"
#include "Transform.h"

Light::Light() : Component(COMPONENT_TYPE::LIGHT)
{
}

Light::~Light()
{
}

void Light::FinalUpdate()
{

	if (_lightInfo.lightType == static_cast<INT32>(LIGHT_TYPE::DIRECTIONAL_LIGHT))
		return;

	XMFLOAT3 Pos = mGameObject.lock()->GetTransform()->GetPosition();
	_lightInfo.position = { Pos.x,Pos.y,Pos.z,1.0f };

}
