#include "pch.h"
#include "ProgressBar.h"
#include "GDISelector.h"
#include "ImageRenderer.h"

ProgressBar::ProgressBar() : m_value(0.0f), m_background(0)
{
	AddComponent<ImageRenderer>();

	ImageRenderer* imageRender = GetComponent<ImageRenderer>();
	imageRender->SetTexture(L"volumeIn", L"Texture\\volumeIn.bmp");
}

void ProgressBar::Render(HDC _hdc)
{
	RECT rect;
	GetRect(&rect);

	ComponentRender(_hdc);
	
	GDISelector selector(_hdc, BRUSH_TYPE::GRAY);
	GDISelector selector2(_hdc, PEN_TYPE::HOLLOW);

	Rectangle(_hdc, rect.left + ((rect.right - rect.left) * ( m_value)), rect.top, rect.right + 1, rect.bottom + 1); // 테두리 채우려고 1 더함
}
