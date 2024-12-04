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


	// 콜라이더 관련
public:
	void CalculateCollider(LAYER layer);
	void ClearCollder();
private:
	bool FindFirstTilePos(vector<vector<UCHAR>>& tiles, Vec2& pos);
	// 콜라이더 관련 끝

protected:
	// 블럭이 왼쪽 위에서 되기 때무네 왼쪽 아래로 할 수 있는 포지션 구함 ㅅㄱ
	Vec2 GetScreenBottomPos(const Vec2& plus);

private:
	static vector<std::string> Split(std::string str, char Delimiter);

private:
	TilePalette* m_palette;
	vector<vector<UCHAR>> m_tiles;
	vector<ColliderEventObserver*> m_pColliders;
	
	float m_tileSize; // 타일 하나 사이즈임
};

