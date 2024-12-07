#include "pch.h"
#include "Button.h"
#include "RectObject.h"
#include "Delegate.h"
#include "InputManager.h"
#include "Core.h"
#include "GDISelector.h"
#include "CameraManager.h"

Button::Button() : b_isHover(false)
{
	rect = new RECT();
	GetRect(rect);
}

Button::~Button()
{
	delete rect;
}

void Button::Update()
{
	GetRect(rect);

	POINT mouseP = GET_MOUSEPOS;

	bool mPos_onBtn = rect->left <= mouseP.x && rect->right >= mouseP.x && rect->top <= mouseP.y && rect->bottom >= mouseP.y;

	if (mPos_onBtn && !b_isHover)//PtInRect({ 0,0,0,0 }), GET_MOUSEPOS);
	{
		OnHover();
		b_isHover = mPos_onBtn;
	}
	else if (!mPos_onBtn && b_isHover)
	{
		ExitHover();
		b_isHover = mPos_onBtn;
	}

	//cout << b_isHover << endl;
	//cout << mPos_onBtn << endl;
	if (b_isHover && GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		OnClick();
	}
}

void Button::Render(HDC _hdc)
{
	RectObject::Render(_hdc);
	/*PEN_TYPE ePen = PEN_TYPE::GREEN;
	GDISelector pen(_hdc, ePen);
	GDISelector brush(_hdc, BRUSH_TYPE::HOLLOW);
	const Vec2& camPos = GET_CAM;
	RECT_RENDER(_hdc, (rect->left + rect->right) / 2, (rect->top + rect->bottom)/2,
		GetSize().x, GetSize().y);*/
}

void Button::Refresh()
{
	GetRect(rect);
}
