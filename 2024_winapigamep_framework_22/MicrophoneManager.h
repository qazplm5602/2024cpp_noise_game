#pragma once
class IMMDeviceEnumerator;
class IMMDevice;
class IAudioMeterInformation;

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
	bool SelectDevice(const LPWSTR id);
	void ClearDevice();
	void GetMicPeek(float* value);
private:
	IMMDeviceEnumerator* pEnumerator = nullptr;
	IMMDevice* pCurrentDevice = nullptr;
	IAudioMeterInformation* pMeterInfo = nullptr;
};

