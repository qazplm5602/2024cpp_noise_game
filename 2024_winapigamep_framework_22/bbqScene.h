#pragma once
#include "Scene.h"

class ProgressBar;
class bbqScene :
    public Scene
{
	// Scene을(를) 통해 상속됨
public:
	virtual void Init() override;
	virtual void Update() override;

	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

private:
	ProgressBar* m_progreeBar;
	float m_nowPeek;

	HDC m_hAlphaDC;
	HBITMAP m_hAlphaBit;

	bool b_isHolding;
	int peakVolume_clamped;

	float f_lastT;
};

