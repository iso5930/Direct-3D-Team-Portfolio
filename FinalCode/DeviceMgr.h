#pragma once

class CDeviceMgr
{
private:
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;

public:
	void Initialize();
	int Update();
	void RenderBegin();
	void RenderEnd();
	void Release();

public:
	// GetDevice
	LPDIRECT3DDEVICE9 GetDevice();

	// SetParam
	void SetParam(D3DPRESENT_PARAMETERS& _rParam);

private:
	DECLARE_SINGLETON(CDeviceMgr)

private:
	explicit CDeviceMgr();
	~CDeviceMgr();
};