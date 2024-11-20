#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"

Rigidbody::Rigidbody() : m_fGravity(9.81f), m_fMass(1.0f), m_fDrag(0.0f),
m_vVelocity(Vec2(0, 0)), m_bUseGravity(true), m_bIsKinematic(false)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::LateUpdate()
{
    if (m_bIsKinematic) return;

    // 1. ���� �ӵ��� ��ȯ (F = m * a, a = F / m)
    ApplyForce();

    // 2. �߷� ����
    if (m_bUseGravity)
    {
        m_vForce.y -= m_fGravity * m_fMass;
    }

    // 3. ���� ���� (Drag)
    m_vVelocity.x *= (1 - m_fDrag);
    m_vVelocity.y *= (1 - m_fDrag);

    // 4. �ӵ� ������Ʈ
    //m_vVelocity = m_vVelocity + (m_vForce / m_fMass);

    // 5. ��ġ ������Ʈ
    Object* Owner = GetOwner();
    Vec2 currPos = Owner->GetPos();
    Owner->SetPos(currPos + m_vVelocity);

    // 6. �� �ʱ�ȭ (�� �����ӿ� �� ���� ����)
    m_vForce = Vec2(0, 0);
}

void Rigidbody::ApplyForce()
{
	if (m_fMass <= 0) return; // ������ 0 ������ ��� ��� �Ұ�
	Vec2 acceleration = Vec2(m_vForce.x / m_fMass, m_vForce.y / m_fMass); // a = F / m
	m_vVelocity = m_vVelocity + acceleration; // v = v + a
}
