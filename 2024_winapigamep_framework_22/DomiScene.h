#pragma once
#include "Scene.h"
class DomiScene :
	public Scene
{
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
};

