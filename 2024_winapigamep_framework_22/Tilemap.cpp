#include "pch.h"
#include "Tilemap.h"
#include "Object.h"
#include "CameraManager.h"

Tilemap::Tilemap()
	: m_palette(nullptr)
	, m_tileSize(50.0f)
{

	SetMapSize({40, 10});
	for (auto i = 0; i < 10; i++)
	{
		SetTile({ 0, i }, 1);
	}

	SetPos(GetScreenBottomPos({ 0.0f, 0.0f })); // test...
}

void Tilemap::Update()
{
}

void Tilemap::Render(HDC _hdc)
{
	const Vec2& pos = GetPos() - GET_CAM;
	Vec2 padding;

	for (size_t y = 0; y < m_tiles.size(); y++)
	{
		for (size_t x = 0; x < m_tiles[y].size(); x++)
		{
			padding.x = m_tileSize * x;
			padding.y = m_tileSize * y;
			
			RECT_RENDER(_hdc, x + pos.x + padding.x, y + pos.y + padding.y, m_tileSize, m_tileSize);


			wstring text = std::to_wstring(x) + L", " + std::to_wstring(y);
			SetTextAlign(_hdc, TA_CENTER);
			TextOut(_hdc, x + pos.x + padding.x, y + pos.y + padding.y, text.c_str(), text.size());
		}
	}
}

void Tilemap::SetTile(Vec2 pos, UCHAR tileType)
{
	m_tiles[pos.y][pos.x] = tileType;
}

Vec2 Tilemap::GetScreenBottomPos(const Vec2& plus)
{
	return Vec2(-(plus.x * m_tileSize), -((m_tiles.size() * m_tileSize) - SCREEN_HEIGHT) + (plus.y * m_tileSize));
}
