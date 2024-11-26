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

    pCollection->GetCount(&count); // 마이크 장치 갯수 불러오기

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
    return true;
}

void MicrophoneManager::ClearDevice()
{
    if (pCurrentDevice == nullptr) return;

    pMeterInfo->Release();
    pCurrentDevice->Release();
}

void MicrophoneManager::GetMicPeek(float* value)
{
    pMeterInfo->GetPeakValue(value);
}

