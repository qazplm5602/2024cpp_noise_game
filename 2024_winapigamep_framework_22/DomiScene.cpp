#include "pch.h"
#include "DomiScene.h"
#include "RectObject.h"
#include "ImageRenderer.h"

void DomiScene::Init()
{
	RectObject* testRect = new RectObject();

	testRect->SetPos({20, 20});
	testRect->SetSize({ 500, 100 });
	testRect->SetAnchor(RectAnchor::Center);

	testRect->AddComponent<ImageRenderer>();
	testRect->GetComponent<ImageRenderer>()->SetTexture(L"planem", L"Texture\\planem.bmp");

	AddObject(testRect, LAYER::UI);
}

void DomiScene::Update()
{
}
