#include "pch.h"
#include "Tilemap.h"
#include "Object.h"
#include "CameraManager.h"
#include "TilePalette.h"
#include "Texture.h"

Tilemap::Tilemap()
	: m_palette(nullptr)
	, m_tileSize(50.0f)
{

	//SetMapSize({40, 10});
	//for (auto i = 0; i < 10; i++)
	//{
	//	SetTile({ 0, i }, 1);
	//}

	//SetPos(GetScreenBottomPos({ 0.0f, 0.0f })); // test...
}

Tilemap::~Tilemap()
{
	if (m_palette != nullptr)
		delete m_palette;
}

void Tilemap::Update()
{
}

void Tilemap::Render(HDC _hdc)
{
	const Vec2& globalPos = GetPos() - GET_CAM;
	Vec2 padding, pos;

	for (size_t y = 0; y < m_tiles.size(); y++)
	{
		for (size_t x = 0; x < m_tiles[y].size(); x++)
		{
			padding.x = m_tileSize * x - x /* 1px °ø¹é ÀÕÀ½ */;
			padding.y = m_tileSize * y - y;

			pos.x = x + globalPos.x + padding.x;
			pos.y = y + globalPos.y + padding.y;

			if (m_tiles[y][x] != 0) { // Å¸ÀÏ¸ÊÀÌ ÀÖÀ½
				TileTexData texData = m_palette->GetTileTexutre(m_tiles[y][x]);

				//RECT_RENDER(_hdc, pos.x, pos.y, m_tileSize, m_tileSize);
				::TransparentBlt(_hdc
					, (int)(pos.x - m_tileSize / 2)
					, (int)(pos.y - m_tileSize / 2)
					, m_tileSize, m_tileSize
					, texData.tex->GetTexDC()
					, texData.start.x, texData.start.y
					, texData.size.x, texData.size.y
					, RGB(255, 0, 255)
				);
			}



			wstring text = std::to_wstring(x) + L", " + std::to_wstring(y);
			SetTextAlign(_hdc, TA_CENTER);
			TextOut(_hdc, x + globalPos.x + padding.x, y + globalPos.y + padding.y, text.c_str(), text.size());
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
