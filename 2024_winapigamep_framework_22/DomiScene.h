#pragma once
#include "Scene.h"

class ProgressBar;
class Player;
class DomiScene :
	public Scene
{
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	void CreateMicGuage();

	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

private:
	ProgressBar* m_progreeBar;
	float m_nowPeek;

	Player* pPlayer;
};

