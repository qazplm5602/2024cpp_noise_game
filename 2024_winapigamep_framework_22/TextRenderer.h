#pragma once
#include "Component.h"
class TextRenderer : public Component
{
public:
	TextRenderer();
	virtual ~TextRenderer();

public:
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;

	void SetText(const wstring& value) {
		m_text = value;
	}
	void SetFont(FONT_TYPE type) {
		m_font = type;
	}
	void SetSize(int value) {
		m_size = value;
	}
	void SetColor(COLORREF value) {
		m_color = value;
	}
	void SetAlign(const UINT& value) {
		m_align = value;
	}

private:
	wstring m_text;
	FONT_TYPE m_font;
	int m_size;
	COLORREF m_color;
	UINT m_align;
};

