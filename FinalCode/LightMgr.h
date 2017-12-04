#pragma once

class CLight;

class CLightMgr
{
private:
	LPD3DXMESH m_pSphere;

	CLight* m_pLightArr[100];
	CLight* m_pLight;

	D3DXVECTOR3 m_vPos3D;
	D3DXVECTOR4 m_vPos4D;

	float m_fNear;
	float m_fFar;
	float m_fDist;

	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;
	D3DXMATRIX m_mViewProj;

	D3DXMATRIX m_mInvView;
	D3DXMATRIX m_mInvProj;
	D3DXMATRIX m_mInvViewProj;

	D3DXMATRIX m_mPreView;
	D3DXMATRIX m_mPreProj;
	D3DXMATRIX m_mPreViewProj;

	D3DXMATRIX	m_matLightView[CASCADED_END];
	D3DXMATRIX	m_matLightProj[CASCADED_END];
	D3DXMATRIX	m_matLightViewProj[CASCADED_END];
	float		m_fCascadedFar[CASCADED_END];

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	CLight* GetLight() { return m_pLight; }
	CLight* GetLight(DWORD _dwIndex) { return m_pLightArr[_dwIndex]; }

	float GetNear() { return m_fNear; }
	float GetFar() { return m_fFar; }
	float GetDist() { return m_fDist; }

	D3DXVECTOR3* GetPos3D() { return &m_vPos3D; }
	D3DXVECTOR4* GetPos4D() { return &m_vPos4D; }

	D3DXMATRIX* GetView() { return &m_mView; }
	D3DXMATRIX* GetProj() { return &m_mProj; }
	D3DXMATRIX* GetViewProj() { return &m_mViewProj; }

	D3DXMATRIX* GetInvView() { return &m_mInvView; }
	D3DXMATRIX* GetInvProj() { return &m_mInvProj; }
	D3DXMATRIX* GetInvViewProj() { return &m_mInvViewProj; }

	D3DXMATRIX* GetPreView() { return &m_mPreView; }
	D3DXMATRIX* GetPreProj() { return &m_mPreProj; }
	D3DXMATRIX* GetPreViewProj() { return &m_mPreViewProj; }

	D3DXMATRIX* GetCascadedView(CASCADED_TYPE _eCascadedType) { return &m_matLightView[_eCascadedType]; }
	D3DXMATRIX* GetCascadedProj(CASCADED_TYPE _eCascadedType) { return &m_matLightProj[_eCascadedType]; }
	D3DXMATRIX* GetCascadedViewProj(CASCADED_TYPE _eCascadedType) { return &m_matLightViewProj[_eCascadedType]; }
	float GetCascadedFar(CASCADED_TYPE _eCascadedType) { return m_fCascadedFar[_eCascadedType]; }

public:
	// AddLight
	void AddLight(DWORD _dwIndex, CLight* _pLight);

	// RemoveLight
	void RemoveLight(DWORD _dwIndex, CLight* _pLight);

	// Enable
	void Enable(DWORD _dwIndex);

private:
	DECLARE_SINGLETON(CLightMgr)

private:
	explicit CLightMgr();
	~CLightMgr();
};
