#pragma once
#include "Component.h"

class MicJumpObserver : public Component
{
public:
	MicJumpObserver();

	void Update(); // 물리 연산 때문에 update가 필요함
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;

private:
	float m_lastPeek;
	float m_upDuration;
	float m_cumulativePower;
};

