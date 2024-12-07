#pragma once
#include "Tilemap.h"
class FinishFlag : public Tilemap
{
public:
	FinishFlag();

public:
	virtual void EnterCollision(Collider* _other);

	bool HasFinish() {
		return m_finish;
	}

private:
	bool m_finish = false;
};

