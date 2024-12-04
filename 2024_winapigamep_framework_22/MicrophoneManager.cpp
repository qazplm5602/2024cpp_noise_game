#include "pch.h"
#include "MicrophoneManager.h"

#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include <functiondiscoverykeys_devpkey.h>

void MicrophoneManager::Init()
{
    CoInitialize(nullptr);
    
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
}

void MicrophoneManager::Release()
{
    ClearDevice();
    CoUninitialize();
}

vector<MicDeviceData> MicrophoneManager::GetDevices()
{
    vector<MicDeviceData> result;
    IMMDeviceCollection* pCollection = nullptr;
    IMMDevice* pDevice = nullptr;
    IPropertyStore* pProps = nullptr;

    pEnumerator->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &pCollection);

    UINT count;

    pCollection->GetCount(&count); // ����ũ ��ġ ���� �ҷ�����

    for (UINT i = 0; i < count; i++)
    {
        pCollection->Item(i, &pDevice);

        LPWSTR deviceID = NULL;
        pDevice->GetId(&deviceID);
        
        pDevice->OpenPropertyStore(STGM_READ, &pProps);

        PROPVARIANT varName;
        PropVariantInit(&varName);

        pProps->GetValue(PKEY_Device_FriendlyName, &varName);

        MicDeviceData data{ std::wstring(deviceID), std::wstring(varName.pwszVal) };
        result.push_back(data);

        PropVariantClear(&varName);
        //CoTaskMemFree(deviceID);
        pProps->Release();
        pDevice->Release();
    }

    return result;
}

bool MicrophoneManager::SelectDevice(const wstring id)
{
    HRESULT hr = pEnumerator->GetDevice(id.c_str(), &pCurrentDevice);
    if (!SUCCEEDED(hr)) {
        return false;
    }

    pCurrentDevice->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&pMeterInfo);

    IAudioClient* pAudioClient;
    WAVEFORMATEX* pwfx = NULL;
    pCurrentDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);

    pAudioClient->GetMixFormat(&pwfx);
    pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, 0, 0, pwfx, NULL);

    pAudioClient->Start();

    return true;
}

void MicrophoneManager::ClearDevice()
{
    if (pCurrentDevice == nullptr) return;

    IAudioClient* pAudioClient;
    HRESULT hr = pCurrentDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
    if (SUCCEEDED(hr)) { // audio client �ҷ�������
        pAudioClient->Stop();
        pAudioClient->Release();
    }

    pMeterInfo->Release();
    pCurrentDevice->Release();
    pCurrentDevice = nullptr;
    pMeterInfo = nullptr;
}

void MicrophoneManager::GetMicPeek(float* value)
{
    pMeterInfo->GetPeakValue(value);
}

bool MicrophoneManager::IsConnected()
{
    return pCurrentDevice != nullptr;
}

wstring MicrophoneManager::GetCurrentDeviceId()
{
    assert(MicrophoneManager::IsConnected()); // ���� �ȵǾ��ִµ� �� ȣ����
    
    LPWSTR deviceID = NULL;
    pCurrentDevice->GetId(&deviceID);

    return wstring(deviceID);
}

wstring MicrophoneManager::GetDefaultDeviceId()
{
    IMMDevice* pDevice;
    pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDevice);

    LPWSTR deviceID = NULL;
    pDevice->GetId(&deviceID);

    return wstring(deviceID);
}

