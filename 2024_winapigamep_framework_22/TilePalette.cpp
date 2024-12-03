#include "pch.h"
#include "TilePalette.h"
#include "ResourceManager.h"
#include "Texture.h"

TilePalette::TilePalette(Texture* pTex, const Vec2& size)
{
	m_tilesTex = pTex;
	m_texSize.x = pTex->GetWidth();
	m_texSize.y = pTex->GetHeight();

	m_tileSize.x = size.x;
	m_tileSize.y = size.y;
}
