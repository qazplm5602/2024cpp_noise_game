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
	//GDISelector selector2(_hdc, PEN_TYPE::HOLLOW);

	HPEN hPen = (HPEN)GetStockObject(NULL_PEN);
	HPEN oldPen = (HPEN)SelectObject(_hdc, hPen);

	Rectangle(_hdc, rect.left + ((rect.right - rect.left) * ( m_value)), rect.top, rect.right, rect.bottom);

	SelectObject(_hdc, oldPen);

	// 생성된 GDI 오브젝트 삭제
	DeleteObject(hPen);
}
