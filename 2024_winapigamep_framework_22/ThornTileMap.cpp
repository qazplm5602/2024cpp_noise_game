#include "pch.h"
#include "ThornTileMap.h"
#include"Collider.h"
#include"Object.h"
#include <cmath>

ThornTileMap::ThornTileMap() {
    // ������

}

ThornTileMap::~ThornTileMap() {
    // �Ҹ���
}

void ThornTileMap::EnterCollision(Collider* _other) {
    // �浹�� ��ü�� �÷��̾����� Ȯ��
  
        // �÷��̾�� Ÿ�� �߽��� ��ġ�� ���
        Vec2 playerPos = _other->GetOwner()->GetPos();   // �÷��̾� ��ġ
        Vec2 tileCenterPos = this->GetPos(); // Ÿ�� �߽� ��ġ

        // �Ի� ���� ���
        Vec2 incidentVec = playerPos - tileCenterPos;

        // ���� ����ȭ
        float magnitude = std::sqrt(incidentVec.x * incidentVec.x + incidentVec.y * incidentVec.y);
        if (magnitude != 0) {
            incidentVec.x /= magnitude;
            incidentVec.y /= magnitude;
        }

        // ǥ�� ���� ���� ���� (���⼭�� ���÷� ���� Ÿ�� ��)
        Vec2 normalVec = { 0.0f, -1.0f }; // ǥ�� ���⿡ ���� ���� ����

        // �ݻ� ���� ���
        float dotProduct = incidentVec.x * normalVec.x + incidentVec.y * normalVec.y;
        Vec2 reflectionVec = {
            incidentVec.x - 2 * dotProduct * normalVec.x,
            incidentVec.y - 2 * dotProduct * normalVec.y
        };

        // �ݻ� �������� �÷��̾ ������ ���� �Ÿ�
        float knockbackDistance = 50.0f; // �ݻ� �� �̵��� �Ÿ�
        Vec2 knockbackPos = playerPos + reflectionVec * knockbackDistance;

        // �÷��̾� ��ġ ������Ʈ
        _other->GetOwner()->SetPos(knockbackPos);

}
