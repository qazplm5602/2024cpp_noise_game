#include "pch.h"
#include "ProgressBar.h"
#include "GDISelector.h"
#include "ImageRenderer.h"

ProgressBar::ProgressBar()
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

	Rectangle(_hdc, rect.left + ((rect.right - rect.left) * (1.0f - m_value)), rect.top, rect.right, rect.bottom);
}
