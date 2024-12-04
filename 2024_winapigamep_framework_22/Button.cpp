#include "pch.h"
#include "Button.h"
#include "RectObject.h"
#include "Delegate.h"
#include "InputManager.h"

Button::Button() : b_isHover(false)
{
	rect = new RECT();
	GetRect(rect);

	OnClick.Add([this]() {
		cout << "dick" << endl;
		});
}

Button::~Button()
{
	
}

void Button::Update()
{
	bool mPos_onBtn = PtInRect(rect, GET_MOUSEPOS);
	if (mPos_onBtn && !b_isHover)//PtInRect({ 0,0,0,0 }), GET_MOUSEPOS);
	{
		OnHover();
		b_isHover = !mPos_onBtn;
	}

	if (mPos_onBtn && b_isHover)
	{
		ExitHover();
		b_isHover = !mPos_onBtn;
	}

	cout << b_isHover << endl;
	if (b_isHover && GET_KEYDOWN(KEY_TYPE::LBUTTON))
	{
		OnClick();
	}
}

void Button::Refresh()
{
	GetRect(rect);
}
