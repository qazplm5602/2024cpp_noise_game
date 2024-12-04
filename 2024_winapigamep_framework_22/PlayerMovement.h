#pragma once
#include "Component.h"
class Rigidbody;
class PlayerMovement :
    public Component
{
public:
    PlayerMovement();
    ~PlayerMovement();
public:
    void HandleJump();
public:
    void LateUpdate() override;
    void Render(HDC _hdc) override;
private:
    float fJumpTime = 0;
    float BASEJUMPDURATION = .25f;
    Rigidbody* rb;
};

