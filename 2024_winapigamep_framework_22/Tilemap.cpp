#include "pch.h"
#include "Tilemap.h"
#include "Object.h"
#include "CameraManager.h"
#include "TilePalette.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "EventManager.h"
#include "ColliderEventObserver.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include <fstream>
#include <istream>
#include <sstream>

Tilemap::Tilemap()
	: m_palette(nullptr)
	, m_tileSize(50.0f)
{
	AddComponent<Collider>();
	//SetMapSize({40, 10});
	//for (auto i = 0; i < 10; i++)
	//{
	//	SetTile({ 0, i }, 1);
	//}

	//SetPos(GetScreenBottomPos({ 0.0f, 0.0f })); // test...
}

Tilemap::~Tilemap()
{
	if (m_palette != nullptr)
	{
		//delete m_palette;
		m_palette->SetUse(false);
		m_palette = nullptr;
	}
}

void Tilemap::Update()
{
}

void Tilemap::Render(HDC _hdc)
{
	const Vec2& globalPos = GetPos() - GET_CAM;
	Vec2 padding, pos;

	for (size_t y = 0; y < m_tiles.size(); y++)
	{
		for (size_t x = 0; x < m_tiles[y].size(); x++)
		{
			padding.x = m_tileSize * x - x /* 1px 공백 잇음 */;
			padding.y = m_tileSize * y - y;

			pos.x = x + globalPos.x + padding.x;
			pos.y = y + globalPos.y + padding.y;

			if (pos.x + m_tileSize / 2 < 0 || pos.x - m_tileSize / 2 > SCREEN_WIDTH
				|| pos.y + m_tileSize / 2 < 0 || pos.y - m_tileSize / 2 > SCREEN_HEIGHT
			) {
				continue; // 화면 범위 넘어서 안그려도 됨 ㅅㄱ
			}

			if (m_tiles[y][x] != 0) { // 타일맵이 있음
				TileTexData texData = m_palette->GetTileTexutre(m_tiles[y][x]);

				//RECT_RENDER(_hdc, pos.x, pos.y, m_tileSize, m_tileSize);
				::TransparentBlt(_hdc
					, (int)(pos.x - m_tileSize / 2)
					, (int)(pos.y - m_tileSize / 2)
					, m_tileSize, m_tileSize
					, texData.tex->GetTexDC()
					, texData.start.x, texData.start.y
					, texData.size.x, texData.size.y
					, RGB(255, 0, 255)
				);
			}

			//wstring text = std::to_wstring(x) + L", " + std::to_wstring(y);
			//SetTextAlign(_hdc, TA_CENTER);
			//TextOut(_hdc, x + globalPos.x + padding.x, y + globalPos.y + padding.y, text.c_str(), text.size());
		}
	}
}

void Tilemap::SetTile(Vec2 pos, UCHAR tileType)
{
	m_tiles[pos.y][pos.x] = tileType;
}

Vec2 Tilemap::GetScreenBottomPos(const Vec2& plus)
{
	return Vec2(-(plus.x * m_tileSize), -((m_tiles.size() * m_tileSize) - SCREEN_HEIGHT) + (plus.y * m_tileSize));
}

void Tilemap::LoadMapLevel(const wstring& fileName, const std::unordered_set<UCHAR>* includes, const std::unordered_set<UCHAR>* excludes)
{
	std::ifstream fin;

	wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	path += L"Map\\" + fileName + L".domi";

	fin.open(path);
	assert(!fin.fail()); // 파일 못불러옴

	std::string line;
	vector<vector<std::string>> list;
	bool hasInclude, hasExclude;

	while (!fin.eof())
	{
		std::getline(fin, line);
		list.push_back(Split(line, ' '));
	}

	SetMapSize({ (int)list[0].size(),  (int)list.size() });

	for (int y = 0; y < list.size(); y++)
	{
		for (int x = 0; x < list[y].size(); x++)
		{
			UCHAR tileType = stoi(list[y][x]);

			hasInclude = includes != nullptr && includes->contains(tileType);
			hasExclude = excludes != nullptr && excludes->contains(tileType);

			if ((includes == nullptr && excludes == nullptr) || (hasInclude) || (includes == nullptr && !hasExclude))
				SetTile({ x, y }, tileType);
		}
	}
}

vector<std::string> Tilemap::Split(std::string str, char Delimiter) {
	std::istringstream iss(str);
	std::string buffer;

	vector<std::string> result;

	while (std::getline(iss, buffer, Delimiter)) {
		result.push_back(buffer);
	}

	return result;
}

void Tilemap::CalculateCollider(LAYER layer)
{
	vector<vector<UCHAR>> tiles = m_tiles; // 복사임

	int tileCount = 0;

	// 타일 갯수 세기
	for (vector<UCHAR>& xTiles : tiles)
		for (UCHAR& tile : xTiles)
			if (tile > 0)
				tileCount++;

	Vec2 tileMapPos = GetPos();

	Vec2 startPos;
	Vec2 endPos;
	bool isDown = false;
	bool fail = false;

	while (tileCount > 0) {
		if (tiles[startPos.y][startPos.x] == 0) { // 뭐야 타일이 없노
			if (FindFirstTilePos(tiles, startPos)) {
				endPos = startPos;
				isDown = false;
			}
			else break; // 타일이 없는듯ㄱ/???
		}

		fail = false;

		if (isDown) {
			endPos.y++;
		}
		else {
			endPos.x++;
		}

		if (tiles.size() <= endPos.y || tiles[endPos.y].size() <= endPos.x) {
			// 다시 복귀 ㄱㄱㄱ (넘음 넘음)
			fail = true;
		}

		// 0 스파이가 있는지 쳌
		if (!fail)
			for (size_t y = startPos.y; y <= endPos.y; y++)
			{
				for (size_t x = startPos.x; x <= endPos.x; x++)
				{
					if (tiles[y][x] == 0) {
						fail = true;
						break;
					}
				}

				if (fail) break;
			}

		// 더 확장~~~
		if (!fail) {
			continue;
		}

		////////////// 여기서 부터는 실패한거임
		if (!isDown) {
			endPos.x--;
			isDown = true; // 아직 기회 있음 ㅋㅋ
			continue;
		}
		else endPos.y--;
		//else {
		//	isDown = false;
		//}

		// 확정 ㄱㄱㄱㄱ
		ColliderEventObserver* observer = new ColliderEventObserver(this);
		observer->GetComponent<Collider>()->SetSize({ (endPos.x - startPos.x + 1) * m_tileSize , (endPos.y - startPos.y + 1) * m_tileSize });
		observer->SetPos((((startPos * m_tileSize) + (endPos * m_tileSize)) / 2.0f) + tileMapPos);
		//observer->GetComponent<Collider>()->SetSize({ 10, 10 });
		//observer->SetSize({ 10, 10 });
		//observer->SetPos(startPos * m_tileSize);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(observer, layer);

		m_pColliders.push_back(observer);

		// 된거는 0으로 다 바꿈
		for (size_t y = startPos.y; y <= endPos.y; y++)
			for (size_t x = startPos.x; x <= endPos.x; x++)
				tiles[y][x] = 0;

		tileCount -= (endPos.y - startPos.y + 1) * (endPos.x - startPos.x + 1);
	}
}

void Tilemap::ClearCollder()
{
	for (ColliderEventObserver* pObserver : m_pColliders)
		GET_SINGLE(EventManager)->DeleteObject(pObserver);

	m_pColliders.clear();
}

bool Tilemap::FindFirstTilePos(vector<vector<UCHAR>>& tiles, Vec2& pos)
{
	for (size_t y = 0; y < tiles.size(); y++)
	{
		for (size_t x = 0; x < tiles[y].size(); x++)
		{
			if (tiles[y][x] > 0) {
				pos.x = x;
				pos.y = y;
				return true;
			}
		}
	}

	return false;
}
