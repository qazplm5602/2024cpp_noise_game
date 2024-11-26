#include "pch.h"
#include "DomiScene.h"
#include "RectObject.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"

void DomiScene::Init()
{
	RectObject* testRect = new RectObject();

	testRect->SetPos({20, 20});
	testRect->SetSize({ 500, 100 });
	testRect->SetAnchor(RectAnchor::Center);

	testRect->AddComponent<ImageRenderer>();
	testRect->GetComponent<ImageRenderer>()->SetTexture(L"planem", L"Texture\\planem.bmp");

	RectObject* testRect2 = new RectObject();

	testRect2->SetPos({ 20, 20 });
	testRect2->SetSize({ 500, 100 });
	testRect2->SetAnchor(RectAnchor::TopRight);

	testRect2->AddComponent<TextRenderer>();

	TextRenderer* textRender = testRect2->GetComponent<TextRenderer>();
	textRender->SetFont(FONT_TYPE::SPOQA);
	textRender->SetSize(100);
	textRender->SetText(L"Å×½ºÆ® ¤±¤¤¤·¤©");
	textRender->SetColor(RGB(0,0,0));


	AddObject(testRect, LAYER::UI);
	AddObject(testRect2, LAYER::UI);
}

void DomiScene::Update()
{
}
