#pragma once
#include "Component.h"


class Light :
    public Component
{
public:
    Light();
	~Light();
	void FinalUpdate() override;

public:
	const LightInfo& GetLightInfo() { return _lightInfo; }

	void SetLightDirection(const XMVECTOR& direction) { _lightInfo.direction = direction; }

	void SetDiffuse(const XMVECTOR& diffuse) { _lightInfo.color.diffuse = diffuse; }
	void SetAmbient(const XMVECTOR& ambient) { _lightInfo.color.ambient = ambient; }
	void SetSpecular(const XMVECTOR& specular) { _lightInfo.color.specular = specular; }

	void SetLightType(LIGHT_TYPE type) { _lightInfo.lightType = static_cast<INT32>(type); }
	void SetLightRange(float range) { _lightInfo.range = range; }
	void SetLightAngle(float angle) { _lightInfo.angle = angle; }

private:
	LightInfo _lightInfo = {};
};

