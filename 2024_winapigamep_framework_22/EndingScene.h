#pragma once
#include "Scene.h"

class RectObject;
class EndingScene : public Scene
{
	virtual void Init() override;
	virtual void Update();
	virtual void Render(HDC _hdc);

private:
	void CreateCreater();
	void CreateStatistics();
	void CreateTeam();

private:
	float m_speed = 30;
	float m_downY = -620.0f;

	vector<RectObject*> m_rectList;
	vector<Vec2> m_originPos;
};

