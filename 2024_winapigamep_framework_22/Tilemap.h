#pragma once
#include "Object.h"
#include "TilePalette.h"
#include "Collider.h"

// template enum�� �����ϰ�
class Tilemap : public Object
{
public:
	Tilemap();
	virtual ~Tilemap();

	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

	void SetMapSize(const Vec2& size) {
		m_tiles.resize(size.y, vector<UCHAR>());
		for (vector<UCHAR>& xTiles : m_tiles)
			xTiles.resize(size.x, 0);
	}
	void SetTile(Vec2 pos, UCHAR tileType);
	void SetPalette(TilePalette* palette) {
		m_palette = palette;
	}
	void SetTileSize(const float& size) {
		m_tileSize = size;
	}
	
protected:
	// ���� ���� ������ �Ǳ� ������ ���� �Ʒ��� �� �� �ִ� ������ ���� ����
	Vec2 GetScreenBottomPos(const Vec2& plus);
private:
	TilePalette* m_palette;
	vector<vector<UCHAR>> m_tiles;
	
	float m_tileSize; // Ÿ�� �ϳ� ��������
};

