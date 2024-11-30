#pragma once
#include "Object.h"
#include "IMicJumpHandler.h"
class Texture;
class Player : public Object, public IMicJumpHandler
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	virtual void OnMicJump(const float& power) override;
private:
	void CreateProjectile();
	Texture* m_pTex;
};

