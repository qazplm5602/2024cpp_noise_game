#pragma once
class IMMDeviceEnumerator;
class IMMDevice;
class IAudioMeterInformation;

struct MicDeviceData {
	wstring id;
	wstring name;
};

class MicrophoneManager
{
	DECLARE_SINGLE(MicrophoneManager);

public:
	void Init();
	void Release();
	vector<MicDeviceData> GetDevices();
	bool SelectDevice(const wstring id);
	void ClearDevice();
	void GetMicPeek(float* value);
	bool IsConnected();
	wstring GetCurrentDeviceId();
	wstring GetDefaultDeviceId();
private:
	IMMDeviceEnumerator* pEnumerator = nullptr;
	IMMDevice* pCurrentDevice = nullptr;
	IAudioMeterInformation* pMeterInfo = nullptr;
};

