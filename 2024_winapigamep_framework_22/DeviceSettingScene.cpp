#include "pch.h"
#include "DeviceSettingScene.h"
#include "RectObject.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"
#include "ProgressBar.h"
#include "ImageRect.h"
#include "MicrophoneManager.h"
#include "InputManager.h"
#include "GameMath.h"
#include "TimeManager.h"

DeviceSettingScene::DeviceSettingScene()
	: m_deviceText(nullptr)
	, m_peekBar(nullptr)
	, m_currentDeviceIdx(-1)
	, m_lastPeek(0.0f)
	, m_lastDeviceId(L"")
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

	m_devices = GET_SINGLE(MicrophoneManager)->GetDevices();
	if (m_devices.size() > 0)
		m_currentDeviceIdx = 0;

	if (GET_SINGLE(MicrophoneManager)->IsConnected())
		m_lastDeviceId = GET_SINGLE(MicrophoneManager)->GetCurrentDeviceId();

	// 화면 함 함
	OnDeviceUpdate();
}

void DeviceSettingScene::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::LEFT)) {
		if (m_currentDeviceIdx - 1 >= 0) {
			m_currentDeviceIdx--;
		}
		else {
			m_currentDeviceIdx = m_devices.size() - 1;
		}
		OnDeviceUpdate();
	}
	
	if (GET_KEYDOWN(KEY_TYPE::RIGHT)) {
		if (m_currentDeviceIdx + 1 < m_devices.size()) {
			m_currentDeviceIdx++;
		}
		else if (m_devices.size() > 0) {
			m_currentDeviceIdx = 0;
		}
		OnDeviceUpdate();
	}

	if (GET_KEYDOWN(KEY_TYPE::ESC)) {
		if (m_lastDeviceId.empty()) {
			GET_SINGLE(MicrophoneManager)->ClearDevice();
		}
		else {
			GET_SINGLE(MicrophoneManager)->SelectDevice(m_lastDeviceId);
		}

		// 그냥 다른 씬으로 이동
	}

	if (GET_KEYDOWN(KEY_TYPE::ENTER) && GET_SINGLE(MicrophoneManager)->IsConnected()) {
		// 그냥 다른 씬으로 이동
	}
}

void DeviceSettingScene::OnDeviceUpdate() {
	if (m_currentDeviceIdx == -1) {
		m_deviceText->SetText(L"마이크 장치 없음");
		m_errorText->SetColor(RGB(255, 50, 50));
		return;
	}

	m_errorText->SetColor(RGB(255, 255, 255));
	m_peekBar->SetValue(0.0f);
	m_deviceText->SetText(m_devices[m_currentDeviceIdx].name);

	// 장치 바꿈
	GET_SINGLE(MicrophoneManager)->SelectDevice(m_devices[m_currentDeviceIdx].id);
}

void DeviceSettingScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);

	if (GET_SINGLE(MicrophoneManager)->IsConnected()) {
		float peek;
		GET_SINGLE(MicrophoneManager)->GetMicPeek(&peek);
		m_lastPeek = GameMath::Lerp<float>(m_lastPeek, peek, fDT * 20);

		m_peekBar->SetValue(m_lastPeek);
	}
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
	m_peekBar = new ProgressBar;
	m_peekBar->SetAnchor(RectAnchor::Center);
	m_peekBar->SetSize(Vec2(300, 10));
	m_peekBar->SetPos(Vec2(0.0f, CENTER_MARGIN_TOP + 110.0f));
	m_peekBar->SetValue(0.0f);
	AddObject(m_peekBar, LAYER::UI);
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
	m_deviceText = deviceTextRect->GetComponent<TextRenderer>();

	m_deviceText->SetText(L"ㅁㄴㅇㄹㄻㄴㅇㄻㄴㅇㄻㄴㅇㄻㄴㅇㄹ");
	m_deviceText->SetFont(FONT_TYPE::SPOQA_REGULAR);
	m_deviceText->SetSize(20);

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

	// 경고 텍스트
	RectObject* errorTextRect = new RectObject;
	errorTextRect->SetAnchor(RectAnchor::Center);
	errorTextRect->SetSize(Vec2(0, 0));
	errorTextRect->SetPos(Vec2(0.0, CENTER_MARGIN_TOP + 210));
	AddObject(errorTextRect, LAYER::UI);

	errorTextRect->AddComponent<TextRenderer>();
	m_errorText = errorTextRect->GetComponent<TextRenderer>();

	m_errorText->SetText(L"마이크 장치가 없으면 진행할 수 없습니다.");
	m_errorText->SetFont(FONT_TYPE::SPOQA_REGULAR);
	m_errorText->SetSize(17);
	m_errorText->SetColor(RGB(255,50,50));
	m_errorText->SetAlign(TA_CENTER);
}
