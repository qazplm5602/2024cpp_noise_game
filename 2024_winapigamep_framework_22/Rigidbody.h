#pragma once
#include "Component.h"



class Rigidbody : public Component
{
public:
    Rigidbody();
    ~Rigidbody();
public:
    void LateUpdate() override;
    void Render(HDC _hdc) override;
    void LateFixedUpdate(float fixedTimeStep);
public:
    // Gravity 관련
    void SetGravityScale(float fGravity) { m_fGravity = fGravity; }
    const float& GetGravityScale() const { return m_fGravity; }

    // Kinematic 관련
    void SetKinematic(bool bIsKinematic) { m_bIsKinematic = bIsKinematic; }
    const bool& GetKinematic() const { return m_bIsKinematic; }

    // Velocity 관련
    void SetVelocity(Vec2 vVel) { m_vVelocity = vVel; }
    const Vec2& GetVelocity() const { return m_vVelocity; }

    // Mass 관련
    void SetMass(float fMass) { if (fMass > 0.0f) m_fMass = fMass; }
    const float& GetMass() const { return m_fMass; }

    // Drag 관련
    void SetDrag(float fDrag) { if (fDrag >= 0.0f) m_fDrag = fDrag; }
    const float& GetDrag() const { return m_fDrag; }

    // Gravity 사용 여부 관련
    void SetUseGravity(bool bUseGravity) { m_bUseGravity = bUseGravity; }
    const bool& GetUseGravity() const { return m_bUseGravity; }

    void SetIsGrounded(bool bIsGround) { m_bIsGrounded = bIsGround; }
    const bool& IsGrounded() const { return m_bIsGrounded; }

    void PreventOverlapMove(Object* obj, LAYER layerMask);

    void AddForce(Vec2 force);
    void AddImpulse(Vec2 force);

private:
    void ApplyForce();

private:
    // Variables //
    float accumulatedTime;

    float m_fGravity;
    float m_fMass;
    float m_fDrag;

    Vec2 m_vForce;
    Vec2 m_vImpulse;
    Vec2 m_vVelocity;
    
    bool m_bUseGravity;
    bool m_bIsKinematic;
    bool m_bIsGrounded;
};

