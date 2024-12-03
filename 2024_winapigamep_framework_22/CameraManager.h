#pragma once
class CameraManager
{
	DECLARE_SINGLE(CameraManager);
	
public:
	void SetPos(const Vec2& value) {
		m_pos = value;
	}
	const Vec2& GetPos() {
		return m_pos;
	}
	
private:
	Vec2 m_pos;
};

