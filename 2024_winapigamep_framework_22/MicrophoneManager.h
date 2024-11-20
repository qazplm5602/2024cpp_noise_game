#pragma once
class IMMDeviceEnumerator;
class IMMDevice;

struct MicDeviceData {
	LPWSTR id;
	LPWSTR name;
};

class MicrophoneManager
{
	DECLARE_SINGLE(MicrophoneManager);

public:
	void Init();
	void Release();
	vector<MicDeviceData> GetDevices();
private:
	IMMDeviceEnumerator* pEnumerator = nullptr;
	IMMDevice* pCurrentDevice = nullptr;
};

