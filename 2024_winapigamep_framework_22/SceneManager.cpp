#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "DomiScene.h"
#include "bbqScene.h"
#include "RalScene.h"
#include "bbqScene.h"
#include "GameScene.h"
#include "DeviceSettingScene.h"
#include "EndingScene.h"
void SceneManager::Init()
{
	m_pCurrentScene = nullptr;

	// �� ���
	RegisterScene(L"TitleScene",std::make_shared<TitleScene>());
	RegisterScene(L"GameScene",std::make_shared<GameScene>());
	RegisterScene(L"DomiScene",std::make_shared<DomiScene>());
	RegisterScene(L"bbqScene",std::make_shared<bbqScene>());
	RegisterScene(L"RalScene",std::make_shared<RalScene>());
	RegisterScene(L"DeviceSettingScene",std::make_shared<DeviceSettingScene>());
	RegisterScene(L"EndingScene",std::make_shared<EndingScene>());

	// �� �ε�
	LoadScene(L"TitleScene");
}

void SceneManager::Update()
{
	if (m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Update();
	m_pCurrentScene->LateUpdate();
}

void SceneManager::Render(HDC _hdc)
{
	if (m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Render(_hdc);
}

void SceneManager::RegisterScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene)
{
	if (_sceneName.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), {_sceneName, _scene});
}

void SceneManager::LoadScene(const wstring& _sceneName)
{
	// ���� ������
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->Release();
		m_pCurrentScene = nullptr;
	}

	auto iter = m_mapScenes.find(_sceneName);
	if (iter != m_mapScenes.end())
	{
		m_pCurrentScene = iter->second;
		m_pCurrentScene->Init();
	}
}
