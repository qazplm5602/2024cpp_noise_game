#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;

	virtual void Render(HDC _hdc) override;
	virtual void Release() override;
private:
	float m_nowPeek;

	HDC m_hAlphaDC;
	HBITMAP m_hAlphaBit;

	bool b_isHolding;
	int peakVolume_clamped;

	float f_lastT;
};

