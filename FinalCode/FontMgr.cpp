#include "Stdafx.h"
#include "FontMgr.h"

IMPLEMENT_SINGLETON(CFontMgr)

CFontMgr::CFontMgr()
{
	m_pDevice = CDeviceMgr::GetInstance()->GetDevice();

	for(int i = 0; i < 64; ++i)
	{
		for(int j = 0; j < 64; ++j)
		{
			m_pRomanFont[i][j] = NULL;
			m_pKostarFont[i][j] = NULL;
			m_pBauhaus[i][j] = NULL;
		}
	}
}

CFontMgr::~CFontMgr()
{
	Release();
}

void CFontMgr::Initialize()
{
	if(FAILED(AddFontResourceEx(L"../Resource/Font/Kostar.ttf", FR_PRIVATE, 0)))
		cout << "AddFontResourceEx Error" << endl;
	if(FAILED(AddFontResourceEx(L"../Resource/Font/Bauhaus.ttf", FR_PRIVATE, 0)))
		cout << "AddFontResourceEx Error" << endl;
}

int CFontMgr::Update()
{
	return 0;
}

void CFontMgr::Render()
{
}

void CFontMgr::Release()
{
	for(int i = 0; i < 64; ++i)
	{
		for(int j = 0; j < 64; ++j)
		{
			if(m_pRomanFont[i][j] != NULL)
			{
				m_pRomanFont[i][j]->Release();
				m_pRomanFont[i][j] = NULL;
			}

			if(m_pKostarFont[i][j] != NULL)
			{
				m_pKostarFont[i][j]->Release();
				m_pKostarFont[i][j] = NULL;
			}

			if(m_pBauhaus[i][j] != NULL)
			{
				m_pBauhaus[i][j]->Release();
				m_pBauhaus[i][j] = NULL;
			}
		}
	}
}

LPD3DXFONT CFontMgr::GetRomanFont(int _iHeight, int _iWidth)
{
	if(m_pRomanFont[_iHeight][_iWidth] == NULL)
	{
		if(FAILED(D3DXCreateFont(m_pDevice, _iHeight, _iWidth, 500, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Time New Roman"), &(m_pRomanFont[_iHeight][_iWidth]))))
			MessageBox(g_hWnd, _T("Roman Font Load Error"), _T("Error"), MB_OK);
	}

	return m_pRomanFont[_iHeight][_iWidth];
}

LPD3DXFONT CFontMgr::GetKostarFont(int _iHeight, int _iWidth)
{
	if(m_pKostarFont[_iHeight][_iWidth] == NULL)
	{
		if(FAILED(D3DXCreateFont(m_pDevice, _iHeight, _iWidth, 500, 1, false, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Kostar"), &m_pKostarFont[_iHeight][_iWidth])))
			MessageBox(g_hWnd, _T("Kostar Font Load Error"), _T("Error"), MB_OK);
	}

	return m_pKostarFont[_iHeight][_iWidth];
}

LPD3DXFONT CFontMgr::GetBauhaus(int _iHeight, int _iWidth)
{
	if(m_pRomanFont[_iHeight][_iWidth] == NULL)
	{
		if(FAILED(D3DXCreateFont(m_pDevice, _iHeight, _iWidth, 500, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Time New Roman"), &(m_pRomanFont[_iHeight][_iWidth]))))
			MessageBox(g_hWnd, _T("Roman Font Load Error"), _T("Error"), MB_OK);
	}

	return m_pRomanFont[_iHeight][_iWidth];

	/*
	if(m_pBauhaus[_iHeight][_iWidth] == NULL)
	{
		if(FAILED(D3DXCreateFont(m_pDevice, _iHeight, _iWidth, 500, 1, false, HANGUL_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, _T("Bauhaus"), &m_pBauhaus[_iHeight][_iWidth])))
			MessageBox(g_hWnd, _T("Bauhaus Font Load Error"), _T("Error"), MB_OK);
	}

	return m_pBauhaus[_iHeight][_iWidth];
	*/
}