#include "pch.h"
#include "TilePalette.h"
#include "ResourceManager.h"
#include "Texture.h"

TilePalette::TilePalette(Texture* pTex, const Vec2& size) : m_useCount(0)
{
	m_tilesTex = pTex;
	m_texSize.x = pTex->GetWidth();
	m_texSize.y = pTex->GetHeight();

	m_tileSize.x = size.x;
	m_tileSize.y = size.y;
}

void TilePalette::SetUse(bool value)
{
	m_useCount += value ? 1 : -1;

	if (!value && m_useCount == 0) {
		delete this;
	}
}
