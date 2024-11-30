#pragma once
#include "Object.h"

enum class RectAnchor {
	TopRight,
	TopLeft,
	BottomLeft,
	BottomRight,
	Center,
	CenterLeft,
	CenterRight,
	CenterBottom,
	CenterTop
};

class RectObject : public Object
{
private:
	RectAnchor m_anchor;

	byte m_zIndex;

private:
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	void GetRect(RECT* pRect);
	void SetAnchor(RectAnchor anchor) {
		m_anchor = anchor;
	}
};

