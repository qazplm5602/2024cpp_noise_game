#pragma once
#include "RectObject.h"
class ProgressBar : public RectObject
{
public:
	ProgressBar();

private:
	virtual void Render(HDC _hdc) override;

public:
	void SetValue(const float& value) {
		m_value = value;
	}
	void SetBackgroundColor(const COLORREF& value) {
		m_background = value;
	}

private:
	float m_value;
	COLORREF m_background;
};

