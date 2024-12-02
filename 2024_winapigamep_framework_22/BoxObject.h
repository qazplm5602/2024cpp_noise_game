#pragma once
#include "Object.h"
class BoxObject : public Object
{
public:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;
};

