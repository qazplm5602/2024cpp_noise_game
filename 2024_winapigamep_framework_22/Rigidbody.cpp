#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"
#include "TimeManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collider.h"

Rigidbody::Rigidbody() : m_fGravity(9.81f), m_fMass(1.0f), m_fDrag(0.0f),
m_vVelocity(Vec2(0, 0)), m_bUseGravity(true), m_bIsKinematic(false), m_bIsGrounded(false)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::LateUpdate()
{
    if (m_bIsKinematic) return;

    Object* Owner = GetOwner();
    Vec2 currPos = Owner->GetPos();


    //m_vVelocity.x *= (1 - m_fDrag);
    //m_vVelocity.y *= (1 - m_fDrag);

    BoxCastHit hit = PhysicsManager::BoxCast(Owner, Owner->GetSize(), Vec2(0.f, 1.f), Owner->GetComponent<Collider>()->GetSize().y / 2 + 0.12f, GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::GROUND));

    SetIsGrounded(hit.hitObject != nullptr);
    /*m_bIsGrounded = true;*/
    if (m_bUseGravity && !IsGrounded())
    {
        AddForce(Vec2(0.f, m_fGravity * m_fMass * 100));
    }


    if (m_bIsGrounded)
    {
        m_vVelocity.y = min(m_vVelocity.y, 0);
        //cout << "IsGround : " << m_bIsGrounded << " VelY : " << m_vVelocity.y << endl;
        Owner->SetPos(currPos + Vec2(0.f, 0.f) * (hit.distance - Owner->GetComponent<Collider>()->GetSize().y / 2));
    }

    ApplyForce();
    Owner->SetPos(currPos + m_vVelocity * fDT);
    
    //PreventOverlapMove(Owner, GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::GROUND), m_vVelocity, fDT);
    //Owner->SetPos(currPos + m_vVelocity * fDT);

    //std::cout << m_vVelocity.x << m_vVelocity.y << endl;


    
}

void Rigidbody::Render(HDC _hdc)
{
}

void Rigidbody::PreventOverlapMove(Object* obj, const vector<Object*>& objects, Vec2& velocity, float deltaTime)
{
    Vec2 direction = velocity.GetNormalized();
    float distance = velocity.Length() * deltaTime;

    BoxCastHit hit = PhysicsManager::BoxCast(obj, obj->GetSize(), direction, distance, objects);

    if (IsGrounded())
    {
        // if collide, it moves to hit point

        // 속도 수정 (벽/바닥 기준으로 멈춤) 
        if (abs(direction.x) > 0.0f) velocity.x = 0;
        if (abs(direction.y) > 0.0f) velocity.y = 0;
    }
    else
    {
        // 충돌하지 않는 경우 자유 이동
        obj->SetPos(obj->GetPos() + velocity * deltaTime);
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
    Vec2 acceleration = m_vForce / m_fMass;
    m_vVelocity += acceleration * fDT;
    m_vForce = Vec2(0, 0);

    m_vVelocity += m_vImpulse / m_fMass;
    m_vImpulse = Vec2(0, 0);
}   