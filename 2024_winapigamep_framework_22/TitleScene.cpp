#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "GameMath.h"
#include "MicrophoneManager.h"
#include "TimeManager.h"
#include "Core.h"
#include "ImageRect.h"
#include "TextRenderer.h"
#include "Button.h"

void TitleScene::Init()
{
	// 마이크 설정
	wstring micDeviceId = GET_SINGLE(MicrophoneManager)->GetDefaultDeviceId();
	GET_SINGLE(MicrophoneManager)->SelectDevice(micDeviceId);
	m_nowPeek = 0.0f;
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\GigaChad.wav", true);
	GET_SINGLE(ResourceManager)->LoadSound(L"Jump", L"Sound\\jump.wav", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Hit", L"Sound\\hitHurt.wav", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Respawn", L"Sound\\tone.wav", false);
	GET_SINGLE(ResourceManager)->Play(L"BGM");


	// ============= TitleScene SetUp =============
	{
		Core* core = GET_SINGLE(Core);
		m_hAlphaDC = ::CreateCompatibleDC(core->GetMainDC());
		m_hAlphaBit = ::CreateCompatibleBitmap(core->GetMainDC(), SCREEN_WIDTH, SCREEN_HEIGHT);

		ImageRect* rLogo = new ImageRect(L"logo", L"Texture\\LOGO.bmp");
		rLogo->SetAnchor(RectAnchor::Center);
		rLogo->SetPos({ 0.f, -100.f });
		rLogo->SetSize(Vec2(450, 450));
		AddObject(rLogo, LAYER::UI);

		{
			RectObject* rStart = new RectObject();
			rStart->SetAnchor(RectAnchor::Center);
			rStart->SetPos({ 0.f, 140.f });
			rStart->SetSize(Vec2(0, 0));
			TextRenderer* text = rStart->GetOrAddComponent<TextRenderer>();
			text->SetText(L"Shout to Start!");
			text->SetAlign(TA_CENTER);
			text->SetFont(FONT_TYPE::SPOQA_THIN);
			AddObject(rStart, LAYER::UI);
		}

		{
			Button* bSetting = new Button();
			bSetting->SetAnchor(RectAnchor::Center);
			bSetting->SetPos({ 0.f, 205.f });
			bSetting->SetSize(Vec2(700.f, 40.f));
			bSetting->Refresh();

			TextRenderer* text = bSetting->GetOrAddComponent<TextRenderer>();
			text->SetText(L"Setting");
			text->SetAlign(TA_CENTER);
			text->SetFont(FONT_TYPE::SPOQA_THIN);
			AddObject(bSetting, LAYER::UI);

			bSetting->OnClick.Add([]() {
				GET_SINGLE(SceneManager)->LoadScene(L"DeviceSettingScene");
				});

			bSetting->OnHover.Add([text]()
				{
					text->SetSize(32);
				});
			bSetting->ExitHover.Add([text]()
				{
					text->SetSize(28);
				});

			Button* bExit = new Button();
			bExit->SetAnchor(RectAnchor::Center);
			bExit->SetPos({ 0.f, 250.f });
			bExit->SetSize(Vec2(700.f, 40.f));
			bExit->Refresh();
			{

				TextRenderer* text = bExit->GetOrAddComponent<TextRenderer>();
				text->SetText(L"Exit");
				text->SetAlign(TA_CENTER);
				text->SetFont(FONT_TYPE::SPOQA_THIN);
				AddObject(bExit, LAYER::UI);
				bExit->OnHover.Add([text]()
					{
						text->SetSize(32);
					});
				bExit->ExitHover.Add([text]()
					{
						text->SetSize(28);
					});
			}

			bExit->OnClick.Add([]() {
				DestroyWindow(GET_SINGLE(Core)->GetHwnd());
				});

			

		}
	}
	// ============= TitleScene SetUp ============='


}

void TitleScene::Update()
{
	Scene::Update();
	if (peakVolume_clamped < 30)
	{
		b_isHolding = true;
		if (f_lastT > 1.f)
		{
			GET_SINGLE(SceneManager)->LoadScene(L"DomiScene");
		}
		f_lastT += fDT;
		//cout << f_lastT << " " << (f_lastT > 1.f);
	}
	else
	{
		f_lastT = 0;
		b_isHolding = false;
	}
}

void TitleScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
	float micPeek;
	GET_SINGLE(MicrophoneManager)->GetMicPeek(&micPeek);

	m_nowPeek = GameMath::Lerp<float>(m_nowPeek, micPeek, 10 * fDT);

	peakVolume_clamped = max((255 - static_cast<int>(GameMath::Lerp<float>(m_nowPeek, micPeek, 10 * fDT) * 500)), 0);

	Core* core = GET_SINGLE(Core);
	::SelectObject(m_hAlphaDC, m_hAlphaBit);
	::PatBlt(m_hAlphaDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);

	::BitBlt(m_hAlphaDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		core->GetBackDC(), 0, 0, SRCCOPY);
	::PatBlt(core->GetBackDC(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);
	::AlphaBlend(core->GetBackDC(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, m_hAlphaDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		{
			AC_SRC_OVER,
			0,
			(unsigned char)peakVolume_clamped,
			AC_SRC_OVER
		});
	::BitBlt(core->GetMainDC(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, core->GetBackDC(), 0, 0, SRCCOPY);
}

void TitleScene::Release()
{
	DeleteObject(m_hAlphaBit);
	DeleteObject(m_hAlphaDC);
}
