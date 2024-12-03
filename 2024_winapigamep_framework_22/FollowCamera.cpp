#include "pch.h"
#include "FollowCamera.h"
#include "Object.h"


FollowCamera::FollowCamera()
    : m_Target(nullptr) {}

FollowCamera::~FollowCamera() {}

void FollowCamera::Update() {
    // 타겟이 존재할 때 카메라의 위치를 타겟에 맞춰 조정
    if (m_Target) {
        Vec2 targetPos = m_Target->GetPos(); // 타겟의 현재 위치를 가져옴

        // 카메라 위치를 업데이트 (예: 화면 중앙에 타겟 배치)
        Vec2 cameraPos = targetPos - Vec2(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        // 카메라 경계 처리 (맵 크기를 초과하지 않도록)
        if (cameraPos.x < 0) cameraPos.x = 0;
        if (cameraPos.y < 0) cameraPos.y = 0;

        // 예시: 맵 크기가 3000x2000일 경우 제한
        if (cameraPos.x > 3000 - SCREEN_WIDTH) cameraPos.x = 3000 - SCREEN_WIDTH;
        if (cameraPos.y > 2000 - SCREEN_HEIGHT) cameraPos.y = 2000 - SCREEN_HEIGHT;

        // 최종적으로 카메라 위치를 반영
        m_Target->SetPos(cameraPos);
    }
}

void FollowCamera::LateUpdate() {
    if (m_Target) {
        Vec2 targetPos = m_Target->GetPos();
        Vec2 newCameraPos = targetPos + m_Offset;

        
        newCameraPos.x = Clamp(newCameraPos.x, 0.0f, MAX_MAP_WIDTH - SCREEN_WIDTH);
        newCameraPos.x = Clamp(newCameraPos.x, 0.0f, MAX_MAP_WIDTH - SCREEN_WIDTH);

        //GET_SINGLE(SceneManager)->SetCameraPos(newCameraPos);
    }
}

void FollowCamera::Render(HDC _hdc) {
   
}


void FollowCamera::SetTarget(Object* target) {
    m_Target = target;
}
