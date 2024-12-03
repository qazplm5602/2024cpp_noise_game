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

    void SetTarget(Object* target); // Ÿ�� ����

private:
    Object* m_Target; // ī�޶� ���� Ÿ�� ��ü(�÷��̾�)
    Vec2 m_Offset;    // ī�޶� ������ (�߰�)


};

// �� ũ�� ��� ����
constexpr int MAX_MAP_WIDTH = 3000;  // ���� �ִ� �ʺ�
constexpr int MAX_MAP_HEIGHT = 2000; // ���� �ִ� ����
