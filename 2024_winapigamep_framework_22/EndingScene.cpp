#include "pch.h"
#include "EndingScene.h"
#include "SolidColorRenderer.h"
#include "RectObject.h"
#include "TimeManager.h"
#include "ImageRect.h"
#include "TextRenderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "StatisticManager.h"

void EndingScene::Init()
{
	// 배경 색상
	RectObject* background = new RectObject;
	background->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });

	SolidColorRenderer* colorRender = background->GetOrAddComponent<SolidColorRenderer>();
	colorRender->SetColor(BRUSH_TYPE::BLACK);

	AddObject(background, LAYER::BACKGROUND);


	// 로고
	ImageRect* rLogo = new ImageRect(L"logo", L"Texture\\LOGO.bmp");
	rLogo->SetAnchor(RectAnchor::Center);
	rLogo->SetPos({ 0.f, -100.f });
	rLogo->SetSize(Vec2(450, 450));
	AddObject(rLogo, LAYER::UI);
	m_rectList.push_back(rLogo);

	RectObject* thanksPlayTextRect = new RectObject;
	TextRenderer* thanksPlayText = thanksPlayTextRect->GetOrAddComponent<TextRenderer>();
	thanksPlayText->SetText(L"플레이 해 주셔서 감사합니다.");
	thanksPlayText->SetAlign(TA_CENTER);
	thanksPlayText->SetSize(50);
	thanksPlayText->SetColor(RGB(255,255,255));
	thanksPlayText->SetFont(FONT_TYPE::SPOQA_BOLD);
	
	thanksPlayTextRect->SetPos({ 0, 100 });
	thanksPlayTextRect->SetAnchor(RectAnchor::Center);

	AddObject(thanksPlayTextRect, LAYER::UI);
	m_rectList.push_back(thanksPlayTextRect);
	
	CreateCreater();
	CreateStatistics();
	CreateTeam();

	m_originPos.resize(m_rectList.size());
	for (size_t i = 0; i < m_rectList.size(); i++)
	{
		m_originPos[i] = m_rectList[i]->GetPos();
	}
}

void EndingScene::Update()
{
	m_downY += m_speed * fDT;

	for (size_t i = 0; i < m_rectList.size(); i++) {
		m_rectList[i]->SetPos({ m_originPos[i].x, m_originPos[i].y - m_downY });
	}

	// 테스트 버튼
	if (GET_KEYDOWN(KEY_TYPE::R)) {
		Release();
		EndingScene::Init();
		m_downY = 500.0f;
	}
	
	if (m_downY > 1000) {
		GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}
}

void EndingScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}

void EndingScene::CreateCreater()
{
	RectObject* titleRect = new RectObject;
	TextRenderer* titleText = titleRect->GetOrAddComponent<TextRenderer>();
	titleText->SetText(L"만든 사람들");
	titleText->SetAlign(TA_CENTER);
	titleText->SetSize(40);
	titleText->SetColor(RGB(255, 255, 255));
	titleText->SetFont(FONT_TYPE::SPOQA_MEDIUM);

	titleRect->SetPos({ 0, 200 });
	titleRect->SetAnchor(RectAnchor::Center);

	AddObject(titleRect, LAYER::UI);
	m_rectList.push_back(titleRect);

	wstring nameList[] = {
		L"권도현",
		L"박영준",
		L"김민성"
	};

	for (UCHAR i = 0; i < 3; i++)
	{
		RectObject* domiRect = new RectObject;
		TextRenderer* domiText = domiRect->GetOrAddComponent<TextRenderer>();
		domiText->SetText(nameList[i]);
		domiText->SetAlign(TA_CENTER);
		domiText->SetSize(25);
		domiText->SetColor(RGB(100, 100, 100));
		domiText->SetFont(FONT_TYPE::SPOQA_REGULAR);

		domiRect->SetPos({ 0, 250 + (25 * i)});
		domiRect->SetAnchor(RectAnchor::Center);

		AddObject(domiRect, LAYER::UI);
		m_rectList.push_back(domiRect);
	}
}

void EndingScene::CreateStatistics()
{
	RectObject* titleRect = new RectObject;
	TextRenderer* titleText = titleRect->GetOrAddComponent<TextRenderer>();
	titleText->SetText(L"게임을 하면서 일어났던 일");
	titleText->SetAlign(TA_CENTER);
	titleText->SetSize(40);
	titleText->SetColor(RGB(255, 255, 255));
	titleText->SetFont(FONT_TYPE::SPOQA_MEDIUM);

	titleRect->SetPos({ 0, 400 });
	titleRect->SetAnchor(RectAnchor::Center);

	AddObject(titleRect, LAYER::UI);
	m_rectList.push_back(titleRect);

	StatisticManager* statisticManager = GET_SINGLE(StatisticManager);

	time_t takenTime = time(NULL) - statisticManager->GetStartTime();
	time_t takenMin = takenTime / 60;
	time_t takenSec = takenTime % 60;

	wstring nameList[] = {
		L"클러어까지 걸린 시간: " + std::to_wstring(takenMin) + L"분 " + std::to_wstring(takenSec) + L"초",
		L"총 점프 횟수: "+ NumberToStringComma(statisticManager->GetJumpCount()) + L"번",
		L"떨어진 횟수: " + NumberToStringComma(statisticManager->GetFallCount()) + L"번",
		L"가시에 닿은 횟수: "+ NumberToStringComma(statisticManager->GetDetectThorn()) + L"번",
	};

	for (UCHAR i = 0; i < 4; i++)
	{
		RectObject* domiRect = new RectObject;
		TextRenderer* domiText = domiRect->GetOrAddComponent<TextRenderer>();
		domiText->SetText(nameList[i]);
		domiText->SetAlign(TA_CENTER);
		domiText->SetSize(25);
		domiText->SetColor(RGB(100, 100, 100));
		domiText->SetFont(FONT_TYPE::SPOQA_REGULAR);

		domiRect->SetPos({ 0, 450 + (25 * i) });
		domiRect->SetAnchor(RectAnchor::Center);

		AddObject(domiRect, LAYER::UI);
		m_rectList.push_back(domiRect);
	}
}

void EndingScene::CreateTeam()
{
	RectObject* domiRect = new RectObject;
	TextRenderer* domiText = domiRect->GetOrAddComponent<TextRenderer>();
	domiText->SetText(L"2024 게임프로그래밍 2학기 작품");
	domiText->SetAlign(TA_CENTER);
	domiText->SetSize(32);
	domiText->SetColor(RGB(100, 100, 100));
	domiText->SetFont(FONT_TYPE::SPOQA_MEDIUM);

	domiRect->SetPos({ 0, 700 });
	domiRect->SetAnchor(RectAnchor::Center);

	AddObject(domiRect, LAYER::UI);
	m_rectList.push_back(domiRect);
	

	domiRect = new RectObject;
	domiText = domiRect->GetOrAddComponent<TextRenderer>();
	domiText->SetText(L"도자캣팀");
	domiText->SetAlign(TA_CENTER);
	domiText->SetSize(40);
	domiText->SetColor(RGB(255, 255, 255));
	domiText->SetFont(FONT_TYPE::SPOQA_BOLD);

	domiRect->SetPos({ 0, 730 });
	domiRect->SetAnchor(RectAnchor::Center);

	AddObject(domiRect, LAYER::UI);
	m_rectList.push_back(domiRect);
}

wstring EndingScene::NumberToStringComma(int value)
{
	wstring domi = std::to_wstring(value);
	
	for (int i = domi.size() - 3; i > 0; i -= 3) {
		domi.insert(i, L",");
	}

	return domi;
}
