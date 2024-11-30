#include "pch.h"
#include "DeviceSettingScene.h"
#include "RectObject.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"

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
	backImage->SetTexture(L"volumeIn", L"Texture\\volumeIn.bmp");

	RectObject* backTextBox = new RectObject();
	backTextBox->SetAnchor(RectAnchor::BottomLeft);
	backTextBox->SetPos(Vec2(30, 30));
	backTextBox->SetSize(Vec2(30, 30));
	AddObject(backTextBox, LAYER::UI);

	backTextBox->AddComponent<TextRenderer>();
	TextRenderer* backText = backTextBox->GetComponent<TextRenderer>();

	backText->SetSize(20);
	backText->SetText(L"뒤로가기");

	// 설정하기

}
