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
	// ��� ����
	RectObject* background = new RectObject;
	background->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });

	SolidColorRenderer* colorRender = background->GetOrAddComponent<SolidColorRenderer>();
	colorRender->SetColor(BRUSH_TYPE::BLACK);

	AddObject(background, LAYER::BACKGROUND);


	// �ΰ�
	ImageRect* rLogo = new ImageRect(L"logo", L"Texture\\LOGO.bmp");
	rLogo->SetAnchor(RectAnchor::Center);
	rLogo->SetPos({ 0.f, -100.f });
	rLogo->SetSize(Vec2(450, 450));
	AddObject(rLogo, LAYER::UI);
	m_rectList.push_back(rLogo);

	RectObject* thanksPlayTextRect = new RectObject;
	TextRenderer* thanksPlayText = thanksPlayTextRect->GetOrAddComponent<TextRenderer>();
	thanksPlayText->SetText(L"�÷��� �� �ּż� �����մϴ�.");
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

	// �׽�Ʈ ��ư
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
	titleText->SetText(L"���� �����");
	titleText->SetAlign(TA_CENTER);
	titleText->SetSize(40);
	titleText->SetColor(RGB(255, 255, 255));
	titleText->SetFont(FONT_TYPE::SPOQA_MEDIUM);

	titleRect->SetPos({ 0, 200 });
	titleRect->SetAnchor(RectAnchor::Center);

	AddObject(titleRect, LAYER::UI);
	m_rectList.push_back(titleRect);

	wstring nameList[] = {
		L"�ǵ���",
		L"�ڿ���",
		L"��μ�"
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
	titleText->SetText(L"������ �ϸ鼭 �Ͼ�� ��");
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
		L"Ŭ������� �ɸ� �ð�: " + std::to_wstring(takenMin) + L"�� " + std::to_wstring(takenSec) + L"��",
		L"�� ���� Ƚ��: "+ NumberToStringComma(statisticManager->GetJumpCount()) + L"��",
		L"������ Ƚ��: " + NumberToStringComma(statisticManager->GetFallCount()) + L"��",
		L"���ÿ� ���� Ƚ��: "+ NumberToStringComma(statisticManager->GetDetectThorn()) + L"��",
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
	domiText->SetText(L"2024 �������α׷��� 2�б� ��ǰ");
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
	domiText->SetText(L"����Ĺ��");
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