#include "pch.h"
#include "MoveMetal.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "ColliderEventObserver.h"

MoveMetal::MoveMetal() : m_speed(50.0f)
{
	SetTileSize(42);

	// �ȷ�Ʈ
	Texture* groundTex = GET_SINGLE(ResourceManager)->TextureLoad(L"groundTile", L"Texture\\groundTile.bmp");
	TilePalette* groundPalette = new TilePalette(groundTex, Vec2{ 64, 64 } / 3.0f);
	SetPalette(groundPalette);
	SetMapSize({ 4 , 2 });

	// ö ö ö
	SetTile({ 0, 0 }, 7);
	SetTile({ 1, 0 }, 8);
	SetTile({ 2, 0 }, 8);
	SetTile({ 3, 0 }, 9);
	SetTile({ 0, 1 }, 7 + 9 * 2);
	SetTile({ 1, 1 }, 8 + 9 * 2);
	SetTile({ 2, 1 }, 8 + 9 * 2);
	SetTile({ 3, 1 }, 9 + 9 * 2);
}

void MoveMetal::Init()
{
	m_originX = GetPos().x;
	CalculateCollider(LAYER::GROUND);
}

void MoveMetal::Update()
{
	if (!m_init) {
		Init();
		m_init = true;
	}

	if (m_delay > 0.0f) {
		m_delay -= fDT;
		return;
	}

	Vec2 pos = GetPos();
	if (m_reverse) {
		if (m_originX >= pos.x) {
			m_reverse = false;
			return;
		}
		pos.x -= m_speed * fDT;
	}
	else {
		if (m_originX + m_xMoveRange <= pos.x) {
			m_reverse = true;
			return;
		}
		pos.x += m_speed * fDT;
	}
	
	SetPos(pos);

	
	for (ColliderEventObserver* colliderOb : GetColliders()) {
		pos = colliderOb->GetPos();
		pos.x += m_speed * fDT * (m_reverse ? -1 : 1);
		
		colliderOb->SetPos(pos);
	}
}