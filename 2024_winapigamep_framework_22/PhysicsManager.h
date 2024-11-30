#pragma once
#include<Windows.h>
#include"Object.h"

struct BoxCastHit
{
    Object* hitObject; // �浹�� ��ü
    float distance;    // �浹 ���������� �Ÿ�
    Vec2 hitPoint;     // �浹 ����
};

class PhysicsManager
{
public:
    static BoxCastHit BoxCast(const Object* pOriginObj, const Vec2& size, const Vec2& direction, float distance, const vector<Object*>& objects);

private:
    static bool IsBoxIntersecting(const Vec2& origin, const Vec2& size, const Vec2& direction, float distance, Object* other);

    static bool CalculateIntersection(const Vec2& origin, const Vec2& size, const Vec2& direction, float distance, Object* other, Vec2& hitPoint, float& hitDistance);
};

