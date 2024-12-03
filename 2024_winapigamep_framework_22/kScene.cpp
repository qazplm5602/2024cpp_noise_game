#include "pch.h"
#include "kScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "Collider.h"
void kScene::Init()
{
	Object* pObj = new Enemy;
	pObj->SetPos({ SCREEN_WIDTH / 2.f,150.f });
	pObj->SetSize({ 100.f,100.f });
	pObj->SetName(L"Enemy");
	AddObject(pObj, LAYER::ENEMY);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	pPlayer->AddComponent<Rigidbody>();
	pPlayer->GetComponent<Collider>()->SetOffSetPos(Vec2(0, 2));
	AddObject(pPlayer, LAYER::PLAYER);

	Object* pGround = new Enemy;
	pGround->SetPos({ SCREEN_WIDTH / 2.f - 100.f,700.f });
	pGround->SetSize({ (float)SCREEN_WIDTH, 100.f });
	AddObject(pGround, LAYER::GROUND);
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());

	Object* guk = new Enemy;
	guk->SetPos({ SCREEN_WIDTH * 1.f, 500.f });
	guk->SetSize({ (float)SCREEN_WIDTH, 100.f });
	AddObject(guk, LAYER::GROUND);
	guk->GetComponent<Collider>()->SetSize(guk->GetSize());

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_brgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
	pPlayer->SetSize({ 100.f, 100.f });
	pPlayer->AddComponent<Rigidbody>();
	pPlayer->GetComponent<Collider>()->SetOffSetPos(Vec2(0, 2));
	AddObject(pPlayer, LAYER::PLAYER);

	// FollowCamera ���� �� Ÿ�� ����
	FollowCamera* camera = new FollowCamera();
	camera->SetTarget(pPlayer);  // ī�޶� �÷��̾ Ÿ������ ����
	AddComponent(camera);        // ���� ī�޶� ������Ʈ �߰�
}

void kScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}
