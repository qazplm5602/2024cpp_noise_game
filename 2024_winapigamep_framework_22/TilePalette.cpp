#include "pch.h"
#include "TilePalette.h"
#include "ResourceManager.h"

void TilePalette::RegisterTile(const UCHAR type, const wstring& key, const wstring& path)
{
	m_textures[type] = GET_SINGLE(ResourceManager)->TextureLoad(key, path);
}
