#include "pch.h"
#include "ColliderEventObserver.h"
#include "Collider.h"

ColliderEventObserver::ColliderEventObserver(Object* target)
{
	m_consumer = target;
	AddComponent<Collider>();
}

void ColliderEventObserver::Update()
{
}

void ColliderEventObserver::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void ColliderEventObserver::EnterCollision(Collider* _other)
{
	m_consumer->EnterCollision(_other);
}

void ColliderEventObserver::StayCollision(Collider* _other)
{
	m_consumer->StayCollision(_other);
}

void ColliderEventObserver::ExitCollision(Collider* _other)
{
	m_consumer->ExitCollision(_other);
}
