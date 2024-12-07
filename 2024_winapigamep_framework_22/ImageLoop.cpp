#include "pch.h"
#include "ImageLoop.h"
#include "Texture.h"
#include "CameraManager.h"

void ImageLoop::Update()
{
}

void ImageLoop::Render(HDC _hdc)
{
	Vec2 size = GetSize();
	Vec2 camPos = GET_CAM;
	camPos *= m_duration;

	Vec2 pos = GetPos() - camPos;

	::TransparentBlt(_hdc,
		(int)(pos.x - size.x / 2.0f), (int)(pos.y - size.y / 2.0f),
		size.x, size.y,
		m_tex->GetTexDC(),
		0, 0,
		m_tex->GetWidth(), m_tex->GetHeight(),
		RGB(255, 0, 255)
	);

	///// 똥 [주의
	
	Vec2 xMinMax = { pos.x - size.x / 2.0f, pos.x + size.x / 2.0f };
	// 뒤로 연속
	while (xMinMax.x > 0) {
		xMinMax.x = xMinMax.x - size.x;
		
		::TransparentBlt(_hdc,
			(int)xMinMax.x, (int)(pos.y - size.y / 2.0f),
			size.x, size.y,
			m_tex->GetTexDC(),
			0, 0,
			m_tex->GetWidth(), m_tex->GetHeight(),
			RGB(255, 0, 255)
		);
	}
	// 앞 연속
	while (xMinMax.y < SCREEN_WIDTH) {
		xMinMax.y = xMinMax.y + size.x;

		::TransparentBlt(_hdc,
			(int)(xMinMax.y - size.x), (int)(pos.y - size.y / 2.0f),
			size.x, size.y,
			m_tex->GetTexDC(),
			0, 0,
			m_tex->GetWidth(), m_tex->GetHeight(),
			RGB(255, 0, 255)
		);
	}
}
