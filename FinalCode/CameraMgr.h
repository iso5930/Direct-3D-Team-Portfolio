#pragma once

class CCamera;

class CCameraMgr
{
private:
	CCamera* m_pCameraArr[100];
	CCamera* m_pCamera;

	D3DXVECTOR4 m_vViewPoint4D[8];
	D3DXVECTOR4 m_vWorldPoint4D[8];
	D3DXVECTOR3 m_vViewPoint3D[8];
	D3DXVECTOR3 m_vWorldPoint3D[8];
	D3DXPLANE m_Plane[6];

	D3DXVECTOR3 m_vPos3D;
	D3DXVECTOR4 m_vPos4D;

	float m_fNear;
	float m_fFar;

	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;
	D3DXMATRIX m_mViewProj;

	D3DXMATRIX m_mInvView;
	D3DXMATRIX m_mInvProj;
	D3DXMATRIX m_mInvViewProj;

	D3DXMATRIX m_mPreView;
	D3DXMATRIX m_mPreProj;
	D3DXMATRIX m_mPreViewProj;

	D3DXMATRIX m_mBillBoard;

	float m_fBeginTime;
	float m_fEndTime;
	float m_fPeriod;
	float m_fAmplit;
	float m_fAmount;
	float m_fSign;

public:
	void Initialize();
	int Update();
	void Render();
	void Release();

public:
	CCamera* GetCamera() { return m_pCamera; }
	CCamera* GetCamera(DWORD _dwIndex) { return m_pCameraArr[_dwIndex]; }

	D3DXVECTOR4* GetViewPoint4D(int _iIndex) { return &m_vViewPoint4D[_iIndex]; }
	D3DXVECTOR4* GetWorldPoint4D(int _iIndex) { return &m_vWorldPoint4D[_iIndex]; }

	D3DXVECTOR3* GetViewPoint3D(int _iIndex) { return &m_vViewPoint3D[_iIndex]; }
	D3DXVECTOR3* GetWorldPoint3D(int _iIndex) { return &m_vWorldPoint3D[_iIndex]; }

	D3DXVECTOR3* GetPos3D() { return &m_vPos3D; }
	D3DXVECTOR4* GetPos4D() { return &m_vPos4D; }

	float GetNear() { return m_fNear; }
	float GetFar() { return m_fFar; }

	D3DXMATRIX* GetView() { return &m_mView; }
	D3DXMATRIX* GetProj() { return &m_mProj; }
	D3DXMATRIX* GetViewProj() { return &m_mViewProj; }

	D3DXMATRIX* GetInvView() { return &m_mInvView; }
	D3DXMATRIX* GetInvProj() { return &m_mInvProj; }
	D3DXMATRIX* GetInvViewProj() { return &m_mInvViewProj; }

	D3DXMATRIX* GetPreView() { return &m_mPreView; }
	D3DXMATRIX* GetPreProj() { return &m_mPreProj; }
	D3DXMATRIX* GetPreViewProj() { return &m_mPreViewProj; }

	D3DXMATRIX* GetBillBoard() { return &m_mBillBoard; }

public:
	// AddCamera
	void AddCamera(DWORD _dwIndex, CCamera* _pCamera);

	// RemoveCamera
	void RemoveCamera(DWORD _dwIndex, CCamera* _pCamera);

	// Enable
	void Enable(DWORD _dwIndex);

	// Shake
	void Shake(float _fBeginTime, float _fEndTime, float _fPeriod, float _fAmplit);

	// IsIn
	bool IsIn(D3DXVECTOR3* _pPos, float _fRadius);

private:
	DECLARE_SINGLETON(CCameraMgr)

private:
	explicit CCameraMgr();
	~CCameraMgr();
};