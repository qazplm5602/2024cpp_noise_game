#include "pch.h"
#include "ThornTileMap.h"
#include"Collider.h"
#include"Object.h"
#include <cmath>

ThornTileMap::ThornTileMap() {
    // 생성자

}

ThornTileMap::~ThornTileMap() {
    // 소멸자
}

void ThornTileMap::EnterCollision(Collider* _other) {
    // 충돌한 객체가 플레이어인지 확인
  
        // 플레이어와 타일 중심의 위치를 계산
        Vec2 playerPos = _other->GetOwner()->GetPos();   // 플레이어 위치
        Vec2 tileCenterPos = this->GetPos(); // 타일 중심 위치

        // 입사 벡터 계산
        Vec2 incidentVec = playerPos - tileCenterPos;

        // 벡터 정규화
        float magnitude = std::sqrt(incidentVec.x * incidentVec.x + incidentVec.y * incidentVec.y);
        if (magnitude != 0) {
            incidentVec.x /= magnitude;
            incidentVec.y /= magnitude;
        }

        // 표면 법선 벡터 설정 (여기서는 예시로 위쪽 타일 면)
        Vec2 normalVec = { 0.0f, -1.0f }; // 표면 방향에 따라 조정 가능

        // 반사 벡터 계산
        float dotProduct = incidentVec.x * normalVec.x + incidentVec.y * normalVec.y;
        Vec2 reflectionVec = {
            incidentVec.x - 2 * dotProduct * normalVec.x,
            incidentVec.y - 2 * dotProduct * normalVec.y
        };

        // 반사 방향으로 플레이어를 날리기 위한 거리
        float knockbackDistance = 50.0f; // 반사 후 이동할 거리
        Vec2 knockbackPos = playerPos + reflectionVec * knockbackDistance;

        // 플레이어 위치 업데이트
        _other->GetOwner()->SetPos(knockbackPos);

}
