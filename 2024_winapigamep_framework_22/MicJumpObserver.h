#pragma once
#include "Component.h"

class MicJumpObserver : public Component
{
public:
	MicJumpObserver();

	void Update(); // ���� ���� ������ update�� �ʿ���
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;

private:
	float m_lastPeek;
	float m_upDuration;
	float m_cumulativePower;
};

