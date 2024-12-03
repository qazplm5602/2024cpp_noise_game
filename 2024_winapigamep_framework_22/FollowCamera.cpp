#include "pch.h"
#include "FollowCamera.h"
#include "Object.h"


FollowCamera::FollowCamera()
    : m_Target(nullptr) {}

FollowCamera::~FollowCamera() {}

void FollowCamera::Update() {
    // Ÿ���� ������ �� ī�޶��� ��ġ�� Ÿ�ٿ� ���� ����
    if (m_Target) {
        Vec2 targetPos = m_Target->GetPos(); // Ÿ���� ���� ��ġ�� ������

        // ī�޶� ��ġ�� ������Ʈ (��: ȭ�� �߾ӿ� Ÿ�� ��ġ)
        Vec2 cameraPos = targetPos - Vec2(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        // ī�޶� ��� ó�� (�� ũ�⸦ �ʰ����� �ʵ���)
        if (cameraPos.x < 0) cameraPos.x = 0;
        if (cameraPos.y < 0) cameraPos.y = 0;

        // ����: �� ũ�Ⱑ 3000x2000�� ��� ����
        if (cameraPos.x > 3000 - SCREEN_WIDTH) cameraPos.x = 3000 - SCREEN_WIDTH;
        if (cameraPos.y > 2000 - SCREEN_HEIGHT) cameraPos.y = 2000 - SCREEN_HEIGHT;

        // ���������� ī�޶� ��ġ�� �ݿ�
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
