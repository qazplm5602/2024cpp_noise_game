#pragma once
#include "Scene.h"

class ProgressBar;
class DomiScene :
	public Scene
{
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	void CreateMicGuage();

	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

private:
	ProgressBar* m_progreeBar;
	float m_nowPeek;
};

