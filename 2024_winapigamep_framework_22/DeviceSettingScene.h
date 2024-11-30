#pragma once
#include "Scene.h"
#define CENTER_MARGIN_TOP -50.0f

class DeviceSettingScene : public Scene
{
public:
	DeviceSettingScene();
	virtual ~DeviceSettingScene();
public:
	virtual void Init() override;

private:
	void CreateMicSection();
	void CreateDeviceSection();
};

