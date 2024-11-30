#include "pch.h"
#include "DeviceSettingScene.h"
#include "RectObject.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "ProgressBar.h"
#include "ImageRect.h"

DeviceSettingScene::DeviceSettingScene()
{

}

DeviceSettingScene::~DeviceSettingScene()
{

}

void DeviceSettingScene::Init()
{
	// 뒤로가기
	RectObject* backIcon = new RectObject();
	backIcon->SetAnchor(RectAnchor::BottomLeft);
	backIcon->SetPos(Vec2(30, 30));
	backIcon->SetSize(Vec2(30, 30));
	AddObject(backIcon, LAYER::UI);

	backIcon->AddComponent<ImageRenderer>();
	ImageRenderer* backImage = backIcon->GetComponent<ImageRenderer>();
	backImage->SetTexture(L"escKey", L"Texture\\esc-key.bmp");

	// 뒤로가기 텍스트
	RectObject* backTextBox = new RectObject();
	backTextBox->SetAnchor(RectAnchor::BottomLeft);
	backTextBox->SetPos(Vec2(68, 25));
	backTextBox->SetSize(Vec2(30, 30));
	AddObject(backTextBox, LAYER::UI);

	backTextBox->AddComponent<TextRenderer>();
	TextRenderer* backText = backTextBox->GetComponent<TextRenderer>();

	backText->SetSize(20);
	backText->SetText(L"뒤로가기");

	// 설정하기
	RectObject* enterIcon = new RectObject();
	enterIcon->SetAnchor(RectAnchor::BottomRight);
	enterIcon->SetPos(Vec2(30, 30));
	enterIcon->SetSize(Vec2(30, 30));
	AddObject(enterIcon, LAYER::UI);

	enterIcon->AddComponent<ImageRenderer>();
	ImageRenderer* enterImage = enterIcon->GetComponent<ImageRenderer>();
	enterImage->SetTexture(L"enterKey", L"Texture\\enter-key.bmp");

	// 설정하기 텍스트
	RectObject* enterTextBox = new RectObject();
	enterTextBox->SetAnchor(RectAnchor::BottomRight);
	enterTextBox->SetPos(Vec2(68, 25));
	enterTextBox->SetSize(Vec2(30, 30));
	AddObject(enterTextBox, LAYER::UI);

	enterTextBox->AddComponent<TextRenderer>();
	TextRenderer* enterText = enterTextBox->GetComponent<TextRenderer>();

	enterText->SetSize(20);
	enterText->SetText(L"설정하기");
	enterText->SetAlign(TA_RIGHT);

	// 제목
	RectObject* titleRect = new RectObject;
	titleRect->SetAnchor(RectAnchor::CenterTop);
	titleRect->SetPos(Vec2(0, 15));
	AddObject(titleRect, LAYER::UI);

	titleRect->AddComponent<TextRenderer>();
	TextRenderer* titleText = titleRect->GetComponent<TextRenderer>();
	
	titleText->SetText(L"마이크 선택");
	titleText->SetFont(FONT_TYPE::SPOQA_BOLD);
	titleText->SetSize(45);
	titleText->SetAlign(TA_CENTER);

	// 마이크 사진
	RectObject* micImageRect = new RectObject;
	micImageRect->SetAnchor(RectAnchor::Center);
	micImageRect->SetSize(Vec2(100, 100));
	micImageRect->SetPos(Vec2(0.0f, CENTER_MARGIN_TOP));
	AddObject(micImageRect, LAYER::UI);

	micImageRect->AddComponent<ImageRenderer>();
	ImageRenderer* micImage = micImageRect->GetComponent<ImageRenderer>();

	micImage->SetTexture(L"mic-icon", L"Texture\\mic-icon.bmp");

	// 마이크 음량 / 바
	CreateMicSection();
	
	// 장치 박스
	CreateDeviceSection();
}

void DeviceSettingScene::CreateMicSection()
{
	RectObject* micTextRect = new RectObject;
	micTextRect->SetAnchor(RectAnchor::Center);
	micTextRect->SetSize(Vec2(300, 0));
	micTextRect->SetPos(Vec2(0.0f, CENTER_MARGIN_TOP + 85.0f));
	AddObject(micTextRect, LAYER::UI);

	micTextRect->AddComponent<TextRenderer>();
	TextRenderer* micText = micTextRect->GetComponent<TextRenderer>();

	micText->SetText(L"마이크 음량");
	micText->SetFont(FONT_TYPE::SPOQA_LIGHT);
	micText->SetSize(20);

	// 바 바 바
	ProgressBar* micBar = new ProgressBar;
	micBar->SetAnchor(RectAnchor::Center);
	micBar->SetSize(Vec2(300, 10));
	micBar->SetPos(Vec2(0.0f, CENTER_MARGIN_TOP + 110.0f));
	micBar->SetValue(0.0f);
	AddObject(micBar, LAYER::UI);
}

void DeviceSettingScene::CreateDeviceSection()
{
	const float deviceBoxWidth = 300.0f;
	const float deviceBoxY = 183.0f;

	RectObject* micTextRect = new RectObject;
	micTextRect->SetAnchor(RectAnchor::Center);
	micTextRect->SetSize(Vec2(deviceBoxWidth, 0.0f));
	micTextRect->SetPos(Vec2(0.0, CENTER_MARGIN_TOP + 140.0f));
	AddObject(micTextRect, LAYER::UI);

	micTextRect->AddComponent<TextRenderer>();
	TextRenderer* micText = micTextRect->GetComponent<TextRenderer>();

	micText->SetText(L"마이크 장치");
	micText->SetFont(FONT_TYPE::SPOQA_LIGHT);
	micText->SetSize(20);

	RectObject* deviceBox = new RectObject;
	deviceBox->SetAnchor(RectAnchor::Center);
	deviceBox->SetSize(Vec2(deviceBoxWidth, 40.0f));
	deviceBox->SetPos(Vec2(0.0, CENTER_MARGIN_TOP + deviceBoxY));
	AddObject(deviceBox, LAYER::UI);

	deviceBox->AddComponent<ImageRenderer>();
	ImageRenderer* boxImage = deviceBox->GetComponent<ImageRenderer>();

	boxImage->SetTexture(L"mic-select-border", L"Texture\\mic-select-border.bmp");

	// 장치 이름
	RectObject* deviceTextRect = new RectObject;
	deviceTextRect->SetAnchor(RectAnchor::Center);
	deviceTextRect->SetSize(Vec2(deviceBoxWidth - 20.0f, 22.0f));
	deviceTextRect->SetPos(Vec2(0.0, CENTER_MARGIN_TOP + 183));
	AddObject(deviceTextRect, LAYER::UI);

	deviceTextRect->AddComponent<TextRenderer>();
	TextRenderer* deviceText = deviceTextRect->GetComponent<TextRenderer>();

	deviceText->SetText(L"ㅁㄴㅇㄹㄻㄴㅇㄻㄴㅇㄻㄴㅇㄻㄴㅇㄹ");
	deviceText->SetFont(FONT_TYPE::SPOQA_REGULAR);
	deviceText->SetSize(20);

	// 화살표
	ImageRect* arrowLeft = new ImageRect(L"arrow-left-key", L"Texture\\arrow-left-key.bmp");
	arrowLeft->SetAnchor(RectAnchor::Center);
	arrowLeft->SetSize(Vec2(40.0f, 40.0f));
	arrowLeft->SetPos(Vec2(-(deviceBoxWidth / 2.0f) - 35.0f, deviceBoxY + CENTER_MARGIN_TOP));

	AddObject(arrowLeft, LAYER::UI);

	ImageRect* arrowRight = new ImageRect(L"arrow-right-key", L"Texture\\arrow-right-key.bmp");
	arrowRight->SetAnchor(RectAnchor::Center);
	arrowRight->SetSize(Vec2(40.0f, 40.0f));
	arrowRight->SetPos(Vec2((deviceBoxWidth / 2.0f) + 35.0f, deviceBoxY + CENTER_MARGIN_TOP));
	AddObject(arrowRight, LAYER::UI);

}
