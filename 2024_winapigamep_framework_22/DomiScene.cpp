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
#include "MoveThorn.h"
#include "ThornTileMap.h"
#include "ImageLoop.h"
#include "SolidColorRenderer.h"

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
	//textRender->SetText(L"�׽�Ʈ ��������");
	//textRender->SetColor(RGB(0,0,0));
	//textRender->SetAlign(TA_BOTTOM);

	//AddObject(testRect2, LAYER::UI);

	pPlayer = new Player;
	pPlayer->SetPos({ 0.0f ,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	pPlayer->GetComponent<Collider>()->SetOffSetPos(Vec2(0, 2));
	AddObject(pPlayer, LAYER::PLAYER);

	//Object* pGround = new Enemy;
	//pGround->SetPos({ SCREEN_WIDTH / 2.f,700.f });
	//pGround->SetSize({ (float)SCREEN_WIDTH, 100.f });
	//AddObject(pGround, LAYER::GROUND);
	//pGround->GetComponent<Collider>()->SetSize(pGround->GetSize());

	//Object* pBox = new BoxObject;
	//pBox->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	//pBox->SetSize({ 80.f, 80.f });
	//AddObject(pBox, LAYER::DEFAULT);

	CreateMicGuage();
	CreateTilemaps();
	CreateMoveMetal();
	CreateBackground();


	//Tilemap* testTilemap = new TestTilemap;
	//testTilemap->AddComponent<Collider>();
	//AddObject(testTilemap, LAYER::GROUND);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::GROUND);
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

	// ��
	m_progreeBar = new ProgressBar();
	AddObject(m_progreeBar, LAYER::UI);

	m_progreeBar->SetPos(Vec2(-300.0f + (300 / 2.0f) + (64.0f / 2) + 30.0f, (64.0f / 2)));
	m_progreeBar->SetSize(Vec2(300, 20));
	m_progreeBar->SetAnchor(RectAnchor::CenterBottom);
	m_progreeBar->SetValue(0.0f);

	// ����ũ ����
	wstring micDeviceId = GET_SINGLE(MicrophoneManager)->GetDefaultDeviceId();
	GET_SINGLE(MicrophoneManager)->SelectDevice(micDeviceId);
}

void DomiScene::CreateTilemaps()
{
	// ��� ����Ʈ
	UCHAR thornList[] = { 27, 28, 29, 30, 31, 32, 37, 38, 39, 40, 41, 42, 46, 47, 48, 49, 50, 51, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 82, 83, 84, 85, 86, 87 };
	for (UCHAR id : thornList)
		m_thornIds.insert(id);

	// �ٴ� Ÿ�ϸ�
	groundTilemap = new Tilemap;
	AddObject(groundTilemap, LAYER::GROUND);

	groundTilemap->SetTileSize(42);
	groundTilemap->LoadMapLevel(L"Stage1", nullptr, &m_thornIds);
	groundTilemap->SetScreenBottomPos({ 0, 2 });
	groundTilemap->CalculateCollider(LAYER::GROUND);

	// ���� Ÿ�ϸ�
	thornTilemap = new ThornTileMap;
	AddObject(thornTilemap, LAYER::GROUND);

	thornTilemap->SetTileSize(42);
	thornTilemap->LoadMapLevel(L"Stage1", &m_thornIds, nullptr);
	thornTilemap->SetScreenBottomPos({ 0, 2 });
	thornTilemap->CalculateCollider(LAYER::GROUND);

	// �ȷ�Ʈ
	Texture* groundTex = GET_SINGLE(ResourceManager)->TextureLoad(L"groundTile", L"Texture\\groundTile.bmp");
	TilePalette* groundPalette = new TilePalette(groundTex, Vec2{ 64, 64 } / 3.0f);
	groundTilemap->SetPalette(groundPalette);
	thornTilemap->SetPalette(groundPalette);
}

void DomiScene::CreateMoveMetal()
{
	Vec2 metals[] = {
		{5400, 150},
		{5200, 350},
		{6000, 350},
	};
	float ranges[] = {
		400,
		100,
		100
	};
	bool spawnThorn[] = {
		false,
		false,
		true
	};
	float delay;

	srand((unsigned int)clock());

	for (size_t i = 0; i < sizeof(metals) / sizeof(Vec2); i++)
	{
		delay = (rand() % 200) / 100.0f;

		// �����̴� ö
		MoveMetal* metalBlock = new MoveMetal;
		AddObject(metalBlock, LAYER::GROUND);

		metalBlock->SetPos(metals[i]);
		metalBlock->SetMoveRange(ranges[i]);
		metalBlock->SetDelay(delay);

		if (spawnThorn[i]) {
			MoveThorn* moveThorn = new MoveThorn;
			AddObject(moveThorn, LAYER::GROUND);

			moveThorn->SetPos(metals[i] - Vec2(0.0f, metalBlock->GetTileSize() * 1));
			moveThorn->SetMoveRange(100);
			moveThorn->SetDelay(delay);
		}
	}
}

void DomiScene::CreateBackground()
{
	// 배경 색상
	RectObject* background = new RectObject;
	background->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });

	SolidColorRenderer* colorRender = background->GetOrAddComponent<SolidColorRenderer>();
	colorRender->SetColor(BRUSH_TYPE::WHITE_BLUE);

	AddObject(background, LAYER::BACKGROUND);

	// 움직이는거

	vector<ImageLoopData> list = {
		//{L"background-1", 0.0f, {SCREEN_WIDTH, SCREEN_HEIGHT}, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}},
		{ L"background-moon-2", 0.2f, { 7, 11 }, { SCREEN_WIDTH - 300, 200 } },
		{ L"background-cloud-3", 0.3f, { 1274, 281 }, { SCREEN_WIDTH / 2, 200 } },
		//{ L"background-cloud-4", 0.3f, {1280, 689}, {SCREEN_WIDTH / 2, SCREEN_HEIGHT - (689 / 2)} },
		//{ L"background-cloud-5", 0.4f, {1280, 562}, {SCREEN_WIDTH / 2, SCREEN_HEIGHT - (562 / 2)} }
	};

	for (auto& v : list) {
		wstring path = L"Texture\\";
		path += v.texFileName;
		path += L".bmp";
		
		Texture* tex = GET_SINGLE(ResourceManager)->TextureLoad(v.texFileName, path);
		ImageLoop* imageLoop = new ImageLoop();
		AddObject(imageLoop, LAYER::BACKGROUND);

		imageLoop->SetSize(v.size);
		imageLoop->SetPos(v.pos);
		imageLoop->SetTexture(tex);
		imageLoop->SetDuration(v.duration);
	}
}

void DomiScene::Update()
{
	Scene::Update();
	GET_SINGLE(CameraManager)->SetPos({ pPlayer->GetPos().x - (SCREEN_WIDTH / 2.f), 0.0f});

	// �׽�Ʈ��
	if (GET_KEYDOWN(KEY_TYPE::R)) {
		//pPlayer->SetPos({ 5000, 0 });

		groundTilemap->SetMapSize({ 0,0 }); // �ϴ� �� ����
		groundTilemap->ClearCollder(); // �ϴ� �� ����

		groundTilemap->LoadMapLevel(L"Stage1", nullptr, &m_thornIds);
		groundTilemap->SetScreenBottomPos({ 0, 2 });
		groundTilemap->CalculateCollider(LAYER::GROUND);


		///////////////////
		thornTilemap->SetMapSize({ 0,0 }); // �ϴ� �� ����
		thornTilemap->ClearCollder(); // �ϴ� �� ����

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
