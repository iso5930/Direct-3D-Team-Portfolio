#include "StdAfx.h"
#include "DeviceMgr.h"

IMPLEMENT_SINGLETON(CDeviceMgr)

CDeviceMgr::CDeviceMgr()
{
	m_pSDK = NULL;
	m_pDevice = NULL;
}

CDeviceMgr::~CDeviceMgr()
{
	Release();
}

void CDeviceMgr::Initialize()
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));

	if(FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		cout << "GetDeviceCaps() Error!" << endl;
		return;
	}

	DWORD vp;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS param;
	ZeroMemory(&param, sizeof(D3DPRESENT_PARAMETERS));

	SetParam(param);

	if(FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &param, &m_pDevice)))
	{
		cout << "CreateDevice() Error!" << endl;
		return;
	}
}

int CDeviceMgr::Update()
{
	return 0;
}

void CDeviceMgr::RenderBegin()
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0);
	m_pDevice->BeginScene();
}

void CDeviceMgr::RenderEnd()
{
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void CDeviceMgr::Release()
{
	if(m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	if(m_pSDK != NULL)
	{
		m_pSDK->Release();
		m_pSDK = NULL;
	}
}

LPDIRECT3DDEVICE9 CDeviceMgr::GetDevice()
{
	return m_pDevice;
}

void CDeviceMgr::SetParam(D3DPRESENT_PARAMETERS& _rParam)
{
	_rParam.BackBufferWidth = WINCX;
	_rParam.BackBufferHeight = WINCY;
	_rParam.BackBufferCount = 1;
	//_rParam.BackBufferFormat = D3DFMT_A8R8G8B8;
	_rParam.BackBufferFormat = D3DFMT_X8R8G8B8;

	_rParam.MultiSampleQuality = 0;
	_rParam.MultiSampleType = D3DMULTISAMPLE_NONE;

	//_rParam.AutoDepthStencilFormat = D3DFMT_D24S8;
	_rParam.AutoDepthStencilFormat = D3DFMT_D24X8;
	_rParam.EnableAutoDepthStencil = TRUE;

	_rParam.hDeviceWindow = g_hWnd;
	_rParam.Windowed = TRUE;

	_rParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	_rParam.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//_rParam.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	_rParam.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}