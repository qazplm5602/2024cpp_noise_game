#include "pch.h"
#include "TextRenderer.h"
#include "Core.h"
#include "GDISelector.h"
#include "RectObject.h"

TextRenderer::TextRenderer()
	: m_font(FONT_TYPE::SPOQA)
	, m_text(L"")
	, m_size(28)
	, m_color(0)
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

	//SetTextAlign(_hdc, TA_RIGHT);
	TextOut(_hdc, rect.left, rect.top, m_text.c_str(), wcslen(m_text.c_str()));

	DeleteObject(hFont);
}
