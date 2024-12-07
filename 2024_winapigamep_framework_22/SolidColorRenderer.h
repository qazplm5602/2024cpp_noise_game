#pragma once
#include "Component.h"
class SolidColorRenderer : public Component
{
public:
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
	void Init();

	void SetColor(const BRUSH_TYPE& type) {
		m_brushType = type;
	}

private:
	BRUSH_TYPE m_brushType;
	RECT m_rect;
	
	bool m_init = true;
};

