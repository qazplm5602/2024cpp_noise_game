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
    vector<LPWSTR> result222;

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

        LPWSTR copiedID = _wcsdup(deviceID);
        LPWSTR copiedName = _wcsdup(varName.pwszVal);

        MicDeviceData data{ copiedID, copiedName };
        result.push_back(data);
        //std::wcout << varName.pwszVal << endl;
        result222.push_back(deviceID);

        PropVariantClear(&varName);
        //CoTaskMemFree(deviceID);
        pProps->Release();
        pDevice->Release();
    }

    return result;
}

bool MicrophoneManager::SelectDevice(const LPWSTR id)
{
    HRESULT hr = pEnumerator->GetDevice(id, &pCurrentDevice);
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

