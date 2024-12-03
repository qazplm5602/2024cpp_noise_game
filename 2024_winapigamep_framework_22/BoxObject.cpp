#include "pch.h"
#include "BoxObject.h"
#include "CameraManager.h"

void BoxObject::Update()
{
}

void BoxObject::Render(HDC _hdc)
{
	const Vec2& camPos = GET_CAM;
	const Vec2& pos = GetPos() - camPos;
	const Vec2& size = GetSize();

	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
}
