#include "pch.h"
#include "TextRenderer.h"
#include "Core.h"
#include "GDISelector.h"
#include "RectObject.h"

TextRenderer::TextRenderer()
	: m_font(FONT_TYPE::SPOQA_REGULAR)
	, m_text(L"")
	, m_size(28)
	, m_color(0)
	, m_align(TA_LEFT)
{

}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::LateUpdate()
{
}

void TextRenderer::Render(HDC _hdc)
{
	RECT rect;
	RectObject* owner = dynamic_cast<RectObject*>(GetOwner());
	assert(owner != nullptr);
	
	owner->GetRect(&rect);

	wstring fontName = GET_SINGLE(Core)->GetFont(m_font);
	HFONT hFont = CreateFont(m_size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, fontName.c_str());

	GDISelector gdi(_hdc, hFont);

	int x = rect.left, y = rect.top;

	if (m_align & TA_CENTER) {
		x = (rect.left + rect.right) / 2.0f;
	}
	if (m_align & TA_RIGHT) {
		x = rect.right;
	}
	if (m_align & TA_BOTTOM) {
		y = rect.bottom;
	}
	if (m_align & TA_LEFT) {
		x = rect.left;
	}


	UINT lastAlign = SetTextAlign(_hdc, m_align);
	COLORREF lastColor = SetTextColor(_hdc, m_color);
	TextOut(_hdc, x, y, m_text.c_str(), wcslen(m_text.c_str()));

	SetTextAlign(_hdc, lastAlign);
	SetTextColor(_hdc, lastColor);

	DeleteObject(hFont);
}
