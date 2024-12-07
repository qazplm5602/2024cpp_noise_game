#include "pch.h"
#include "FinishFlag.h"
#include "SceneManager.h"

FinishFlag::FinishFlag()
{

}

void FinishFlag::EnterCollision(Collider* _other)
{
	m_finish = true;
}
