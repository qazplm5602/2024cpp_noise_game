#include "pch.h"
#include "DomiScene.h"
#include "RectObject.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "ProgressBar.h"
#include "MicrophoneManager.h"
#include "GameMath.h"
#include "TimeManager.h"
#include "Object.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Enemy.h"
#include "BoxObject.h"
#include "CameraManager.h"

void DomiScene::Init()
{
	//RectObject* testRect = new RectObject();

	//testRect->SetPos({20, 20});
	//testRect->SetSize({ 500, 100 });
	//testRect->SetAnchor(RectAnchor::Center);

	//testRect->AddComponent<ImageRenderer>();
	//testRect->GetComponent<ImageRenderer>()->SetTexture(L"planem", L"Texture\\planem.bmp");
	//AddObject(testRect, LAYER::UI);


	//RectObject* testRect2 = new RectObject();

	//testRect2->SetPos({ 20, 20 });
	//testRect2->SetSize({ 500, 100 });
	//testRect2->SetAnchor(RectAnchor::BottomRight);
	//testRect2->AddComponent<TextRenderer>();

	//TextRenderer* textRender = testRect2->GetComponent<TextRenderer>();
	//textRender->SetFont(FONT_TYPE::SPOQA_MEDIUM);
	//textRender->SetSize(100);
	//textRender->SetText(L"테스트 ㅁㄴㅇㄹ");
	//textRender->SetColor(RGB(0,0,0));
	//textRender->SetAlign(TA_BOTTOM);

	//AddObject(testRect2, LAYER::UI);

	pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	pPlayer->AddComponent<Rigidbody>();
	pPlayer->GetComponent<Collider>()->SetOffSetPos(Vec2(0, 2));
	AddObject(pPlayer, LAYER::PLAYER);

	Object* pGround = new Enemy;
	pGround->SetPos({ SCREEN_WIDTH / 2.f,700.f });
	pGround->SetSize({ (float)SCREEN_WIDTH, 100.f });
	AddObject(pGround, LAYER::GROUND);
	pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());

	Object* pBox = new BoxObject;
	pBox->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pBox->SetSize({ 80.f, 80.f });
	AddObject(pBox, LAYER::DEFAULT);

	CreateMicGuage();
}


void DomiScene::CreateMicGuage()
{
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

	// 마이크 설정
	wstring micDeviceId = GET_SINGLE(MicrophoneManager)->GetDefaultDeviceId();
	GET_SINGLE(MicrophoneManager)->SelectDevice(micDeviceId);
}

void DomiScene::Update()
{
	Scene::Update();
	GET_SINGLE(CameraManager)->SetPos({ pPlayer->GetPos().x - (SCREEN_WIDTH / 2.f), 0.0f});
}

void DomiScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	float micPeek;
	GET_SINGLE(MicrophoneManager)->GetMicPeek(&micPeek);
	//std::cout << micPeek << std::endl;

	m_nowPeek = GameMath::Lerp<float>(m_nowPeek, micPeek, 10 * fDT);
	m_progreeBar->SetValue(m_nowPeek);
}
