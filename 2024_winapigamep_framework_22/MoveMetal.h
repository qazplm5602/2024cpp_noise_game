#pragma once
#include "Tilemap.h"
class MoveMetal : public Tilemap
{
public:
	MoveMetal();
	virtual void Update() override;
	
	// y 움직이는건 대응 나중에 함 ㅅㄱ
	void SetMoveRange(const float& value) {
		m_xMoveRange = value;
	}
	void SetDelay(const float& value) {
		m_delay = value;
	}
	void SetSpeed(const float& value) {
		m_speed = value;
	}

private:
	void Init();

private:
	float m_xMoveRange;
	float m_originX;
	float m_delay;
	float m_speed;

	bool m_init;
	bool m_reverse;
};

