#include "pch.h"
#include "RectObject.h"

void RectObject::Update()
{
}

void RectObject::Render(HDC _hdc)
{
	// 디버그
    RECT rect;
    GetRect(&rect);
	Rectangle(_hdc, rect.left, rect.top, rect.right, rect.bottom);

	ComponentRender(_hdc);
}

void RectObject::GetRect(RECT* pRect)
{
    Vec2 pos = GetPos();
    Vec2 size = GetSize();

    switch (m_anchor)
    {
    case RectAnchor::TopRight:
        pRect->left = SCREEN_WIDTH - pos.x - size.x;
        pRect->right = SCREEN_WIDTH - pos.x;
        pRect->top = pos.y;
        pRect->bottom = pos.y + size.y;
        break;
    case RectAnchor::TopLeft:
        pRect->left = pos.x;
        pRect->right = pos.x + size.x;
        pRect->top = pos.y;
        pRect->bottom = pos.y + size.y;
        break;
    case RectAnchor::BottomLeft:
        pRect->left = pos.x;
        pRect->right = pos.x + size.x;
        pRect->top = SCREEN_HEIGHT - pos.y - size.y;
        pRect->bottom = SCREEN_HEIGHT - pos.y;
        break;
    case RectAnchor::BottomRight:
        pRect->left = SCREEN_WIDTH - pos.x - size.x;
        pRect->right = SCREEN_WIDTH - pos.x;
        pRect->top = SCREEN_HEIGHT - pos.y - size.y;
        pRect->bottom = SCREEN_HEIGHT - pos.y;
        break;
    case RectAnchor::Center:
        pRect->left = (SCREEN_WIDTH / 2) - (size.x / 2);
        pRect->right = (SCREEN_WIDTH / 2) + (size.x / 2);
        pRect->top = (SCREEN_HEIGHT / 2) - (size.y / 2);
        pRect->bottom = (SCREEN_HEIGHT / 2) + (size.y / 2);
        break;
    case RectAnchor::CenterLeft:
        pRect->left = pos.x;
        pRect->right = pos.x + size.x;
        pRect->top = (SCREEN_HEIGHT / 2) - (size.y / 2);
        pRect->bottom = (SCREEN_HEIGHT / 2) + (size.y / 2);
        break;
    case RectAnchor::CenterRight:
        pRect->left = SCREEN_WIDTH - pos.x - size.x;
        pRect->right = SCREEN_WIDTH - pos.x;
        pRect->top = (SCREEN_HEIGHT / 2) - (size.y / 2);
        pRect->bottom = (SCREEN_HEIGHT / 2) + (size.y / 2);
        break;
    case RectAnchor::CenterBottom:
        pRect->left = (SCREEN_WIDTH / 2) - (size.x / 2);
        pRect->right = (SCREEN_WIDTH / 2) + (size.x / 2);
        pRect->top = SCREEN_HEIGHT - pos.y - size.y;
        pRect->bottom = SCREEN_HEIGHT - pos.y;
        break;
    default:
        // 기본 처리
        pRect->left = pos.x;
        pRect->right = pos.x + size.x;
        pRect->top = pos.y;
        pRect->bottom = pos.y + size.y;
        break;
    }
}
