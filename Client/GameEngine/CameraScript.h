#pragma once
#include "MonoBehaviour.h"
class CameraScript : public MonoBehaviour
{
public:
	CameraScript();
	virtual ~CameraScript();

    virtual void Initialize();
    virtual void LateInitialize();
    virtual void Update();
    virtual void LateUpdate();
    virtual void FinalUpdate();
    virtual void Render();
private:
	float		_speed = 10.f;



};

