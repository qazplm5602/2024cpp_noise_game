#include "pch.h"
#include "SolidColorRenderer.h"
#include "RectObject.h"
#include "GDISelector.h"

void SolidColorRenderer::LateUpdate()
{
	if (m_init) {
		m_init = false;
		Init();
	}
}

void SolidColorRenderer::Render(HDC _hdc)
{
	GDISelector selector(_hdc, m_brushType);
	Rectangle(_hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
}

void SolidColorRenderer::Init()
{
	RectObject* owner = dynamic_cast<RectObject*>(GetOwner());
	assert(owner != nullptr);

	owner->GetRect(&m_rect);
	m_rect.left--;
	m_rect.top--;
	m_rect.right++;
	m_rect.bottom++;
}
