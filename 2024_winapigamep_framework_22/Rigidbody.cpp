#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"

Rigidbody::Rigidbody() : m_fGravity(0.001f), m_fMass(1.0f), m_fDrag(0.0f),
m_vVelocity(Vec2(0, 0)), m_bUseGravity(true), m_bIsKinematic(false)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::LateUpdate()
{
    if (m_bIsKinematic) return;


    if (m_bUseGravity)
    {
        m_vForce.y += m_fGravity * m_fMass;
    }

    ApplyForce();

    m_vVelocity.x *= (1 - m_fDrag);
    m_vVelocity.y *= (1 - m_fDrag);

    Object* Owner = GetOwner();
    Vec2 currPos = Owner->GetPos();
    Owner->SetPos(currPos + m_vVelocity);

    //std::cout << m_vVelocity.x << m_vVelocity.y << endl;

    m_vForce = Vec2(0, 0);
}

void Rigidbody::Render(HDC _hdc)
{
}

void Rigidbody::ApplyForce()
{
	if (m_fMass <= 0) return; // 질량이 0 이하인 경우 계산 불가
	Vec2 acceleration = Vec2(m_vForce.x / m_fMass, m_vForce.y / m_fMass); // a = F / m
	m_vVelocity = m_vVelocity + acceleration; // v = v + a
}
