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

        //LPWSTR copiedID = _wcsdup(deviceID);
        //LPWSTR copiedName = _wcsdup(varName.pwszVal);

        MicDeviceData data{ deviceID, varName.pwszVal };
        result.push_back(data);
        std::wcout << varName.pwszVal << endl;
        result222.push_back(deviceID);

        PropVariantClear(&varName);
        CoTaskMemFree(deviceID);
        pProps->Release();
        pDevice->Release();
    }

    return result;
}

