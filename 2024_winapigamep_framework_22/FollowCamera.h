#pragma once
#include "Component.h"

class Object;

class FollowCamera : public Component {
public:
    FollowCamera();
    virtual ~FollowCamera();

    void Update();
    virtual void LateUpdate() override;
    virtual void Render(HDC _hdc) override;
    virtual float Clamp(float value, float min, float max);

    void SetTarget(Object* target); // 타겟 설정

private:
    Object* m_Target; // 카메라가 따라갈 타겟 객체(플레이어)
    Vec2 m_Offset;    // 카메라 오프셋 (추가)


};

// 맵 크기 상수 선언
constexpr int MAX_MAP_WIDTH = 3000;  // 맵의 최대 너비
constexpr int MAX_MAP_HEIGHT = 2000; // 맵의 최대 높이
