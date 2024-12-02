#pragma once
#include "Object.h"
#include "TilePalette.h"
#include "Collider.h"

// template enum만 가능하게
class Tilemap : public Object
{
public:
	Tilemap();

	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

	void SetTile(Vec2 pos, UCHAR tileType);
	void SetPalette(TilePalette* palette) {
		m_palette = palette;
	}
private:
	TilePalette* m_palette;

	
};

