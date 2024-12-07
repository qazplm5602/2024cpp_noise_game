#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"
#include "TimeManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"

// TODO: Make X axis move with boxCast, bug heppens when dt is way to high

Rigidbody::Rigidbody()
    : m_fGravity(9.81f), m_fMass(1.5f), m_fDrag(1.f),
    m_vVelocity(Vec2(0, 0)), m_bUseGravity(true), m_bIsKinematic(false), m_bIsGrounded(false)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::LateUpdate()
{
    Simulate(fDT);
    //float fixedTimeStep = 1.0f / 60.0f; // 60 updates per second
    //accumulatedTime += fDT;
    //while (accumulatedTime >= fixedTimeStep)
    //{
    //    LateFixedUpdate(fixedTimeStep);
    //    accumulatedTime -= fixedTimeStep;
    //}
}


void Rigidbody::Simulate(float fixedTimeStep)
{
    if (m_bIsKinematic) return;

    Object* Owner = GetOwner();
    Vec2 currPos = Owner->GetPos();

    BoxCastHit hit = PhysicsManager::BoxCast(Owner, Owner->GetSize(), Vec2(0.f, 1.f), Owner->GetComponent<Collider>()->GetSize().y / 2 + 0.12f, GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::GROUND));
    SetIsGrounded(hit.hitObject != nullptr);

    if (m_bUseGravity && !IsGrounded())
    {
        AddForce(Vec2(0.f, 125.f * m_fGravity * m_fMass));
    }

    if (IsGrounded())
    {
        m_vVelocity.y = min(m_vVelocity.y, 0);
        Owner->SetPos(currPos + Vec2(0.f, 0.f) * (hit.distance - Owner->GetComponent<Collider>()->GetSize().y / 2));

        float frictionCoefficient = 8.5f;
        Vec2 frictionForce = Vec2(-m_vVelocity.x, 0.0f) * frictionCoefficient;
        AddForce(frictionForce);
    }
    else {
        // ��������
        float airDragCoefficient = 7.f;
        m_vVelocity.x *= (1.0f - airDragCoefficient * fixedTimeStep);
    }

    ApplyForce(fixedTimeStep);

    Vec2 dragForce = m_vVelocity * -1 * m_fDrag;
    m_vVelocity += (dragForce / m_fMass) * fDT;

    cout << m_vVelocity.x << endl;

    Owner->SetPos(currPos + m_vVelocity * fixedTimeStep);


    //cout << m_vVelocity.y << endl;
    //m_vVelocity.x *= drag
    PreventOverlapMove(Owner, LAYER::GROUND);
}

void Rigidbody::Render(HDC _hdc)
{
}

/// <summary>
/// ���� �÷��̾ ��ġ�� ������ ���������� �ڵ�. ����� ������.
/// </summary>
/// <param name="owner">�񱳴�� 1</param>
/// <param name="layerMask">�˻��� ������Ʈ�� (���̾�� ������)</param>
void Rigidbody::PreventOverlapMove(Object* owner, LAYER layerMask)
{
    vector<Object*> objects = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(layerMask);
    Collider* cOwner = owner->GetComponent<Collider>();
    for (Object* obj : objects)
    {
        if (obj->GetIsDead() || obj->GetComponent<Collider>() == nullptr) continue;

        if (PhysicsManager::IsBoxIntersecting(cOwner, obj->GetComponent<Collider>()))
        {
            Vec2 ownerPos = owner->GetPos();
            Vec2 objPos = obj->GetPos();
            Vec2 ownerHalfSize = cOwner->GetSize() / 2.f;
            Vec2 objHalfSize = obj->GetComponent<Collider>()->GetSize() / 2.f;

            // Delta��
            float deltaX = ownerPos.x - objPos.x;
            float deltaY = ownerPos.y - objPos.y;

            // �̸��� ���ܿ��� �׷��� ������ڸ� �׳� �ΰ� ���� ����. ������ ������ �̰� �����ؾ���.
            float combinedHalfWidth = ownerHalfSize.x + objHalfSize.x;
            float combinedHalfHeight = ownerHalfSize.y + objHalfSize.y;

            // ���� ���� ũ�� ��ŭ ���� �⺻������ ������ ��������, ���߾ӿ� ��ģ �������� ������ ������, �� �Űܾ���
            // �׷��� ��Ÿ��ŭ ���ָ� ��Ȯ�� ��ġ ����. �ٵ� �̰� ���� ���� ���ؼ� �׸����� �׷�����
            float overlapX = combinedHalfWidth - abs(deltaX);
            float overlapY = combinedHalfHeight - abs(deltaY);

            if (overlapX > 0 && overlapY > 0)
            {
                if (overlapX < overlapY)
                {
                    overlapX = (deltaX > 0) ? overlapX : -overlapX;
                    owner->SetPos({ ownerPos.x + overlapX, ownerPos.y });
                }
                else
                {
                    // y�� �̵��� ������ �־ max minó���� ����. x�� �ؾ���. TODO�� ������
                    if (deltaY > 0)
                    {
                        m_vVelocity.y = max(m_vVelocity.y, 0);
                        owner->SetPos({ ownerPos.x, ownerPos.y + overlapY });
                    }
                    else
                    {
                        overlapY *= -1;
                        m_vVelocity.y = min(m_vVelocity.y, 0);
                        owner->SetPos({ ownerPos.x, ownerPos.y + overlapY });
                        // when overlapY is negative, idk but jsutbug heppens so blocked it
                        // �� fixed did * instead of *=
                    }
                }
            }
        }
    }
}

void Rigidbody::AddForce(Vec2 force)
{
    m_vForce += force;
}

void Rigidbody::AddImpulse(Vec2 force)
{
    m_vImpulse += force;
}

void Rigidbody::ApplyForce(float dt)
{
    if (m_fMass <= 0) return;

    m_vVelocity += m_vForce * dt / m_fMass;
    m_vForce = Vec2(0, 0);

    m_vVelocity += m_vImpulse / m_fMass;
    m_vImpulse = Vec2(0, 0);
}
