#include "pch.h"
#include "TestTilemap.h"
#include "TilePalette.h"
#include "ResourceManager.h"

TestTilemap::TestTilemap() {
	SetTileSize(64);
	SetMapSize({ 5, 3 });
	SetPos(GetScreenBottomPos({ 0, 0 }));
	
	TilePalette* palette = new TilePalette(GET_SINGLE(ResourceManager)->TextureLoad(L"test-tilemap", L"Texture\\test-tilemap.bmp"), { 64, 64 });
	SetPalette(palette);

	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
			SetTile({ i, 0 }, 1);
		else if (i == 4)
			SetTile({ i, 0 }, 3);
		else
			SetTile({ i, 0 }, 2);
	}
}