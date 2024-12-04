#pragma once
#include "Object.h"
#include "TilePalette.h"

class ColliderEventObserver;
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
	void SetScreenBottomPos(const Vec2& plus) {
		SetPos(GetScreenBottomPos(plus));
	}
	void LoadMapLevel(const wstring& fileName, const UCHAR& includeFlag);


	// �ݶ��̴� ����
public:
	void CalculateCollider(LAYER layer);
	void ClearCollder();
private:
	bool FindFirstTilePos(vector<vector<UCHAR>>& tiles, Vec2& pos);
	// �ݶ��̴� ���� ��

protected:
	// ���� ���� ������ �Ǳ� ������ ���� �Ʒ��� �� �� �ִ� ������ ���� ����
	Vec2 GetScreenBottomPos(const Vec2& plus);

private:
	static vector<std::string> Split(std::string str, char Delimiter);

private:
	TilePalette* m_palette;
	vector<vector<UCHAR>> m_tiles;
	vector<ColliderEventObserver*> m_pColliders;
	
	float m_tileSize; // Ÿ�� �ϳ� ��������
};

