#pragma once
#include "Scene.h"
class TestScene :public Scene
{
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
	

};

