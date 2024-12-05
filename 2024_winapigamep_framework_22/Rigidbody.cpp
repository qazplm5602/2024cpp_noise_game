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
    : m_fGravity(9.81f), m_fMass(1.5f), m_fDrag(0.0f),
    m_vVelocity(Vec2(0, 0)), m_bUseGravity(true), m_bIsKinematic(false), m_bIsGrounded(false)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::LateUpdate()
{
    float fixedTimeStep = 1.0f / 60.0f; // 60 updates per second
    accumulatedTime += fDT;
    while (accumulatedTime >= fixedTimeStep)
    {
        LateFixedUpdate(fixedTimeStep);
        accumulatedTime -= fixedTimeStep;
    }
}


void Rigidbody::LateFixedUpdate(float fixedTimeStep)
{
    if (m_bIsKinematic) return;

    Object* Owner = GetOwner();
    Vec2 currPos = Owner->GetPos();

    BoxCastHit hit = PhysicsManager::BoxCast(Owner, Owner->GetSize(), Vec2(0.f, 1.f), Owner->GetComponent<Collider>()->GetSize().y / 2 + 0.12f, GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::GROUND));
    SetIsGrounded(hit.hitObject != nullptr);

    if (m_bUseGravity && !IsGrounded())
    {
        AddForce(Vec2(0.f, 100.f * m_fGravity * m_fMass));
    }

    if (IsGrounded())
    {
        m_vVelocity.y = min(m_vVelocity.y, 0);
        Owner->SetPos(currPos + Vec2(0.f, 0.f) * (hit.distance - Owner->GetComponent<Collider>()->GetSize().y / 2));
    }

    ApplyForce();
    Owner->SetPos(currPos + m_vVelocity * fixedTimeStep);


    cout << m_vVelocity.y << endl;
    PreventOverlapMove(Owner, LAYER::GROUND);
}

void Rigidbody::Render(HDC _hdc)
{
}

/// <summary>
/// 벽과 플레이어가 겹치면 밖으러 빠져나오는 코드. 가까운 벽으로.
/// </summary>
/// <param name="owner">비교대상 1</param>
/// <param name="layerMask">검사할 오브젝트들 (레이어로 가져옴)</param>
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

            // Delta값
            float deltaX = ownerPos.x - objPos.x;
            float deltaY = ownerPos.y - objPos.y;

            // 이름을 못외워서 그런데 적어놓자면 그냥 두게 더한 값임. 밖으로 꺼낼때 이걸 연산해야함.
            float combinedHalfWidth = ownerHalfSize.x + objHalfSize.x;
            float combinedHalfHeight = ownerHalfSize.y + objHalfSize.y;

            // 둘의 반의 크기 만큼 빼면 기본적으로 밖으로 나가지만, 정중앙에 겹친 기준으로 밖으로 나가고, 또 옮겨야함
            // 그래서 델타만큼 빼주면 정확한 위치 가능. 근데 이거 말로 설명 못해서 그림까지 그려야함
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
                    // y축 이동은 보정이 있어서 max min처리가 있음. x도 해야함. TODO에 써있음
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
                        // ㄴ fixed did * instead of *=
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

void Rigidbody::ApplyForce()
{
    if (m_fMass <= 0) return;

    m_vVelocity += m_vForce * (1.0f / 60.0f) / m_fMass;
    m_vForce = Vec2(0, 0);

    m_vVelocity += m_vImpulse / m_fMass;
    m_vImpulse = Vec2(0, 0);
}
