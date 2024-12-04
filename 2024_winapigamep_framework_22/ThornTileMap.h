#pragma once
#include"Tilemap.h"

class ThornTileMap : public Tilemap
{
public:
	ThornTileMap();
	virtual ~ThornTileMap();


public:
	virtual void EnterCollision(Collider* _other) override;

};

