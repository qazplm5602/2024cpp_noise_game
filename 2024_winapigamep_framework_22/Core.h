#pragma once
// GameManager
//SAFE_DELETE()
// ���� �̱���(���̳��� �̱���)
// ���� �̱���
#include "Define.h"
//#include "Object.h"
class Core
{
	DECLARE_SINGLE(Core);
public:
	bool Init(HWND _hwnd);
	void GameLoop();
	void CleanUp();
private:
	void MainUpdate();
	void MainRender();
	void CreateGDI();
	void CreateFonts();
	void RemoveFonts();
public:
	const HWND& GetHwnd() const { return m_hWnd; }
	// �̸� �ٲٱ�
	const HDC& GetMainDC() const { return m_hDC; }
	const HDC& GetBackDC() const { return m_hBackDC; }
	const HBRUSH& GetBrush(BRUSH_TYPE _eType)
	{
		return m_colorBrushs[(UINT)_eType];
	}
	const HPEN& GetPen(PEN_TYPE _eType)
	{
		return m_colorPens[(UINT)_eType];
	}
	const wstring& GetFont(FONT_TYPE _eType) {
		return m_fontNames[(UINT)_eType];
	}

private:
	HBRUSH m_colorBrushs[(UINT)BRUSH_TYPE::END] = {};
	HPEN m_colorPens[(UINT)PEN_TYPE::END] = {};
	wstring m_fontNames[(UINT)FONT_TYPE::END] = {};
	wstring m_fontFiles[(UINT)FONT_TYPE::END] = {
		L"SpoqaHanSansNeo-Bold",
		L"SpoqaHanSansNeo-Light",
		L"SpoqaHanSansNeo-Medium",
		L"SpoqaHanSansNeo-Regular",
		L"SpoqaHanSansNeo-Thin",
	};

	HWND m_hWnd;
	HDC  m_hDC; // Main DC
	HDC  m_hBackDC; // ����� DC
	HBITMAP m_hBackBit; // ������� bitmap
	//Object m_obj;
	//private:
//	Core() {}
//public:
//	static Core* GetInst()
//	{
//		static Core m_pInst;
//		return &m_pInst;
//	}
//	/*static Core& GetInst2()
//	{
//		static Core m_pInst;
//		return m_pInst;
//	}*/
//
//private:


};
//void test()
//{
//	static int a = 0;
//
//}
// ���ø� �̱���
//class Core 
//{
// //private:
//	static Core* m_pInst;
//public:
//	static Core* GetInst()
//	{
//		if (nullptr == m_pInst)
//			m_pInst = new Core;
//		return m_pInst;
//	}
//	static void DestoryInst()
//	{
//		if (nullptr != m_pInst)
//		{
//
//		}
//	}
//private:
//	Core() {}

//};

