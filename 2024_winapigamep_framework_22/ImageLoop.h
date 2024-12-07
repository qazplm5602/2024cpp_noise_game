#pragma once
#include "Object.h"

class Texture;
class ImageLoop : public Object
{
	virtual void Update() override;
	virtual void Render(HDC _hdc) override;

public:
	void SetTexture(Texture* value) {
		m_tex = value;
	}
	void SetDuration(const float& value) {
		m_duration = value;
	}

private:
	Texture* m_tex;
	float m_duration;
};
