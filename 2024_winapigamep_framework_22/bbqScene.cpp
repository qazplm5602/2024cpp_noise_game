#include "pch.h"
#include "bbqScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "DomiScene.h"
#include "RectObject.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "ProgressBar.h"
#include "MicrophoneManager.h"
#include "GameMath.h"
#include "TimeManager.h"
#include "ImageRect.h"

void bbqScene::Init()
{
	m_nowPeek = 0.0f;

	Object* pObj = new Enemy;
	pObj->SetPos({ SCREEN_WIDTH / 2.f,150.f });
	pObj->SetSize({ 100.f,100.f });
	pObj->SetName(L"Enemy");
	AddObject(pObj, LAYER::ENEMY);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f - 600.f,600.f });
	pPlayer->SetSize({ 100.f,100.f });
	//pPlayer->AddComponent<Rigidbody>();
	pPlayer->GetComponent<Collider>()->SetOffSetPos(Vec2(0,2));
	AddObject(pPlayer, LAYER::PLAYER);

	{
		Object* pGround = new Enemy;
		pGround->SetPos({ SCREEN_WIDTH / 2.f - 600.f,700.f });
		pGround->SetSize({ (float)SCREEN_WIDTH / 8.f, 100.f });
		AddObject(pGround, LAYER::GROUND);
		pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	}
	{
		Object* pGround = new Enemy;
		pGround->SetPos({ SCREEN_WIDTH / 2.f - 300.f,700.f });
		pGround->SetSize({ (float)SCREEN_WIDTH / 8.f, 100.f });
		AddObject(pGround, LAYER::GROUND);
		pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	}
	{
		Object* pGround = new Enemy;
		pGround->SetPos({ SCREEN_WIDTH / 2.f,700.f });
		pGround->SetSize({ (float)SCREEN_WIDTH / 8.f, 100.f });
		AddObject(pGround, LAYER::GROUND);
		pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());
	}

	Object* guk = new Enemy;

	guk->SetPos({ SCREEN_WIDTH*1.f, 600.f });
	guk->SetSize({ (float)SCREEN_WIDTH/1.4f, 100.f });
	AddObject(guk, LAYER::GROUND);
	guk->GetComponent<Collider>()->SetSize(guk->GetSize());

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_brgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	RectObject* micIcon = new RectObject();
	AddObject(micIcon, LAYER::UI);

	micIcon->SetSize(Vec2(64, 64));
	micIcon->SetPos(Vec2(300.0f, 10.0f));
	micIcon->SetAnchor(RectAnchor::CenterBottom);

	micIcon->AddComponent<ImageRenderer>();

	ImageRenderer* imageRender = micIcon->GetComponent<ImageRenderer>();
	imageRender->SetTexture(L"mic-icon", L"Texture\\mic-icon.bmp");

	// 바
	m_progreeBar = new ProgressBar();
	AddObject(m_progreeBar, LAYER::UI);

	m_progreeBar->SetPos(Vec2(-300.0f + (300 / 2.0f) + (64.0f / 2) + 30.0f, (64.0f / 2)));
	m_progreeBar->SetSize(Vec2(300, 20));
	m_progreeBar->SetAnchor(RectAnchor::CenterBottom);
	m_progreeBar->SetValue(0.0f);

	ImageRect* rObj = new ImageRect(L"logo", L"Texture\\LOGO.bmp");
	rObj->SetAnchor(RectAnchor::Center);
	rObj->SetPos({ 0.f, -100.f });
	rObj->SetSize(Vec2(450, 450));
	AddObject(rObj, LAYER::UI);

	// 마이크 설정
	wstring micDeviceId = GET_SINGLE(MicrophoneManager)->GetDefaultDeviceId();
	GET_SINGLE(MicrophoneManager)->SelectDevice(micDeviceId);
}

void bbqScene::Update()
{
	Scene::Update();
	if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}

void bbqScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	float micPeek;
	GET_SINGLE(MicrophoneManager)->GetMicPeek(&micPeek);

	m_nowPeek = GameMath::Lerp<float>(m_nowPeek, micPeek, 10 * fDT);
	m_progreeBar->SetValue(m_nowPeek);
}
