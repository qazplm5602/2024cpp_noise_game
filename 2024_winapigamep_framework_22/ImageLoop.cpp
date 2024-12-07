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

	Vec2 originPos = GetPos();
	Vec2 pos = GetPos() - camPos;

	Vec2 nowPos = pos;
	while (nowPos.x - size.x / 2.0f < SCREEN_WIDTH) {
		if (nowPos.x + size.x / 2.0f > 0)
			::TransparentBlt(_hdc,
				(int)(nowPos.x - size.x / 2.0f), (int)(nowPos.y - size.y / 2.0f),
				size.x, size.y,
				m_tex->GetTexDC(),
				0, 0,
				m_tex->GetWidth(), m_tex->GetHeight(),
				RGB(255, 0, 255)
			);

		nowPos.x += originPos.x + (size.x / 2.0f);
	}

	//::TransparentBlt(_hdc,
	//	(int)(pos.x - size.x / 2.0f), (int)(pos.y - size.y / 2.0f),
	//	size.x, size.y,
	//	m_tex->GetTexDC(),
	//	0, 0,
	//	m_tex->GetWidth(), m_tex->GetHeight(),
	//	RGB(255, 0, 255)
	//);

	// ¶Ë¶Ë¶Ë
}
