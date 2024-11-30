#pragma once
#include<Windows.h>
#include"Object.h"

struct BoxCastHit
{
    Object* hitObject; // 충돌한 객체
    float distance;    // 충돌 지점까지의 거리
    Vec2 hitPoint;     // 충돌 지점
};

class PhysicsManager
{
public:
    static BoxCastHit BoxCast(const Object* pOriginObj, const Vec2& size, const Vec2& direction, float distance, const vector<Object*>& objects);

private:
    static bool IsBoxIntersecting(const Vec2& origin, const Vec2& size, const Vec2& direction, float distance, Object* other);

    static bool CalculateIntersection(const Vec2& origin, const Vec2& size, const Vec2& direction, float distance, Object* other, Vec2& hitPoint, float& hitDistance);
};

