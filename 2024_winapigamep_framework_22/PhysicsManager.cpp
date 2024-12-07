#include "pch.h"
#include "PhysicsManager.h"
#include "Object.h"
#include "Collider.h"

BoxCastHit PhysicsManager::BoxCast(const Object* pOriginObj, const Vec2& size, const Vec2& direction, float distance, const vector<Object*>& objects)
{
    Vec2 origin = pOriginObj->GetPos();
    BoxCastHit closestHit = { nullptr, distance, Vec2(0, 0) };

    for (Object* obj : objects)
    {
        if (obj == pOriginObj || obj->GetIsDead()) continue;

        if (obj->GetComponent<Collider>() == nullptr)
            continue;
        if (obj->GetComponent<Collider>()->IsTrigger())
            continue;

        // 충돌 판정
        if (IsBoxIntersecting(origin, size, direction, distance, obj))
        {
            Vec2 intersectionPoint;
            float intersectionDistance;

            // 충돌 지점 및 거리 계산
            if (CalculateIntersection(origin, size, direction, distance, obj, intersectionPoint, intersectionDistance))
            {
                if (intersectionDistance < closestHit.distance)
                {
                    closestHit.hitObject = obj;
                    closestHit.distance = intersectionDistance;
                    closestHit.hitPoint = intersectionPoint;
                }
            }
        }
    }
    return closestHit;
}

bool PhysicsManager::IsBoxIntersecting(const Vec2& origin, const Vec2& size, const Vec2& direction, float distance, Object* other)
{
    Collider* collider = other->GetComponent<Collider>();
    Vec2 otherPos = other->GetPos() + collider->GetOffSetPos();
    Vec2 otherSize = collider->GetSize();

    Vec2 boxMin = origin + direction * distance - size / 2;
    Vec2 boxMax = origin + direction * distance + size / 2;

    Vec2 otherMin = otherPos - otherSize / 2;
    Vec2 otherMax = otherPos + otherSize / 2;

    return !(boxMax.x < otherMin.x || boxMin.x > otherMax.x ||
        boxMax.y < otherMin.y || boxMin.y > otherMax.y);
}

bool PhysicsManager::IsBoxIntersecting(const Collider* owner, const Collider* other)
{
    Vec2 vLeftPos = owner->GetLatedUpatedPos();
    Vec2 vRightPos = other->GetLatedUpatedPos();
    Vec2 vLeftSize = owner->GetSize();
    Vec2 vRightSize = other->GetSize();

    RECT leftRt = RECT_MAKE(vLeftPos.x, vLeftPos.y, vLeftSize.x, vLeftSize.y);
    RECT rightRt = RECT_MAKE(vRightPos.x, vRightPos.y, vRightSize.x, vRightSize.y);
    RECT buf;
    return ::IntersectRect(&buf, &leftRt, &rightRt);
}

bool PhysicsManager::CalculateIntersection(const Vec2& origin, const Vec2& size, const Vec2& direction, float distance, Object* other, Vec2& hitPoint, float& hitDistance)
{
    Collider* collider = other->GetComponent<Collider>();
    Vec2 otherPos = other->GetPos() + collider->GetOffSetPos();
    Vec2 otherSize = collider->GetSize();

    Vec2 otherMin = otherPos - otherSize / 2;
    Vec2 otherMax = otherPos + otherSize / 2;

    Vec2 endPoint = origin + direction * distance;

    if (endPoint.x >= otherMin.x && endPoint.x <= otherMax.x &&
        endPoint.y >= otherMin.y && endPoint.y <= otherMax.y)
    {
        hitPoint = endPoint;
        hitDistance = (endPoint - origin).Length();
        return true;
    }

    return false;
}



