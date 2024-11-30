#pragma once
#include "Scene.h"
#define CENTER_MARGIN_TOP -50.0f

class TextRenderer;
class ProgressBar;
struct MicDeviceData;
class DeviceSettingScene : public Scene
{
public:
	DeviceSettingScene();
	virtual ~DeviceSettingScene();
public:
	virtual void Init() override;
	virtual void Update();
	void OnDeviceUpdate();
	virtual void Render(HDC _hdc);

private:
	void CreateMicSection();
	void CreateDeviceSection();

private:
	TextRenderer* m_deviceText;
	TextRenderer* m_errorText;
	ProgressBar* m_peekBar;

	vector<MicDeviceData> m_devices;
	int m_currentDeviceIdx;
	wstring m_lastDeviceId;
	float m_lastPeek;
};

