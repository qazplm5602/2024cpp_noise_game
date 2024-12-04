#pragma once
#include "Tilemap.h"
class TestTilemap : public Tilemap
{
public:
	TestTilemap();

	virtual void EnterCollision(Collider* _other) override;
	virtual void StayCollision(Collider* _other) override;
	virtual void ExitCollision(Collider* _other) override;
};

