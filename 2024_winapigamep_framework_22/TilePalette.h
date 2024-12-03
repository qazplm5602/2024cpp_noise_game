#pragma once
class Texture;

struct TileTexData {
	Texture* tex;
	Vec2 start;
	Vec2& size;
};

class TilePalette
{
public:
	TilePalette(Texture* pTex, const Vec2& size);

	TileTexData GetTileTexutre(const UCHAR& type) {
		Vec2 blockCount = m_texSize / m_tileSize;

		Vec2 start = {
			//(type - 1) /* 0�� ���� Ÿ���̶� 1 ���� ������ */ * m_tileSize.x,
			((type - 1) % (int)blockCount.x) * m_tileSize.x,
			((type - 1) / (int)blockCount.x) * m_tileSize.y
		};

		return TileTexData{
			m_tilesTex,
			start,
			m_tileSize
		};
	}

private:
	//map<UCHAR, Texture*> m_textures;
	Texture* m_tilesTex;
	Vec2 m_tileSize; // �� �� ������
	Vec2 m_texSize; // �ؽ��� ������ (�ؽ��� ù �ε� �� �ҷ���)
};