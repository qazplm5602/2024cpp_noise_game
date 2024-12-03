#include "pch.h"
#include "TestTilemap.h"
#include "TilePalette.h"
#include "ResourceManager.h"

TestTilemap::TestTilemap() {
	SetTileSize(64);
	SetMapSize({ 5, 3 });
	
	TilePalette* palette = new TilePalette(GET_SINGLE(ResourceManager)->TextureLoad(L"test-tilemap", L"Texture\\test-tilemap.bmp"), { 64, 64 });
	SetPalette(palette);

	LoadMapLevel(L"Stage1", -1);

	SetPos(GetScreenBottomPos({ 0.0f, 0.5f }));
	CalculateCollider();
}