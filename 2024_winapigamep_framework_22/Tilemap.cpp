#include "pch.h"
#include "Tilemap.h"
#include "Object.h"

Tilemap::Tilemap()
	: m_palette(nullptr)
{
}

void Tilemap::Update()
{
}

void Tilemap::Render(HDC _hdc)
{
}

void Tilemap::SetTile(Vec2 pos, UCHAR tileType)
{
}

void Tilemap::SetPalette(TilePalette* palette)
{
}
