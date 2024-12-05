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
#include "TestTilemap.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "MoveMetal.h"

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
	CreateTilemaps();
	CreateMoveMetal();

	//Tilemap* testTilemap = new TestTilemap;
	//testTilemap->AddComponent<Collider>();
	//AddObject(testTilemap, LAYER::GROUND);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::GROUND);
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

void DomiScene::CreateTilemaps()
{
	// 까시 리스트
	UCHAR thornList[] = { 27, 28, 29, 30, 31, 32, 37, 38, 39, 40, 41, 42, 46, 47, 48, 49, 50, 51, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 82, 83, 84, 85, 86, 87 };
	for (UCHAR id : thornList)
		m_thornIds.insert(id);

	// 바닥 타일맵
	groundTilemap = new Tilemap;
	AddObject(groundTilemap, LAYER::GROUND);

	groundTilemap->SetTileSize(42);
	groundTilemap->LoadMapLevel(L"Stage1", nullptr, &m_thornIds);
	groundTilemap->SetScreenBottomPos({ 0, 2 });
	groundTilemap->CalculateCollider(LAYER::GROUND);

	// 가시 타일맵
	thornTilemap = new Tilemap;
	AddObject(thornTilemap, LAYER::GROUND);

	thornTilemap->SetTileSize(42);
	thornTilemap->LoadMapLevel(L"Stage1", &m_thornIds, nullptr);
	thornTilemap->SetScreenBottomPos({ 0, 2 });
	thornTilemap->CalculateCollider(LAYER::GROUND);

	// 팔레트
	Texture* groundTex = GET_SINGLE(ResourceManager)->TextureLoad(L"groundTile", L"Texture\\groundTile.bmp");
	TilePalette* groundPalette = new TilePalette(groundTex, Vec2{ 64, 64 } / 3.0f);
	groundTilemap->SetPalette(groundPalette);
	thornTilemap->SetPalette(groundPalette);
}

void DomiScene::CreateMoveMetal()
{
	Vec2 metals[] = {
		{100, 100},
		{500, 100},
	};

	srand((unsigned int)clock());

	for (Vec2& pos : metals)
	{
		// 움직이는 철
		MoveMetal* metalBlock = new MoveMetal;
		AddObject(metalBlock, LAYER::GROUND);

		metalBlock->SetPos(pos);
		metalBlock->SetMoveRange(100);
		metalBlock->SetDelay((rand() % 100) / 100.0f);
	}
}

void DomiScene::Update()
{
	Scene::Update();
	GET_SINGLE(CameraManager)->SetPos({ pPlayer->GetPos().x - (SCREEN_WIDTH / 2.f), 0.0f});

	// 테스트임
	if (GET_KEYDOWN(KEY_TYPE::R)) {
		groundTilemap->SetMapSize({ 0,0 }); // 일단 다 없앵
		groundTilemap->ClearCollder(); // 일단 다 없앵

		groundTilemap->LoadMapLevel(L"Stage1", nullptr, &m_thornIds);
		groundTilemap->SetScreenBottomPos({ 0, 2 });
		groundTilemap->CalculateCollider(LAYER::GROUND);


		///////////////////
		thornTilemap->SetMapSize({ 0,0 }); // 일단 다 없앵
		thornTilemap->ClearCollder(); // 일단 다 없앵

		thornTilemap->LoadMapLevel(L"Stage1", &m_thornIds, nullptr);
		thornTilemap->SetScreenBottomPos({ 0, 2 });
		thornTilemap->CalculateCollider(LAYER::GROUND);
	}
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
