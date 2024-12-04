#pragma once
#include "Object.h"
class ColliderEventObserver : public Object
{
public:
	ColliderEventObserver(Object* target);

	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);

private:
	Object* m_consumer;
};

