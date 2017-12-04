#pragma once

#include "Object.h"

class CLight : public CObject
{
private:
	DWORD m_dwIndex;

	LIGHT_TYPE m_eLightType;
	D3DXVECTOR4 m_vDiffuse;
	D3DXVECTOR4 m_vSpecular;
	D3DXVECTOR4 m_vAmbient;
	D3DXVECTOR4 m_vPos;
	D3DXVECTOR4 m_vDir;
	float m_fRange;

	float m_fFar;
	float m_fNear;
	float m_fDist;

	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;

	LPD3DXMESH m_pSphere;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void SetView(float _fDist, D3DXVECTOR3* _pAngle);
	void SetProj(float _fFovy, float _fAspect, float _fNear, float _fFar);

	LIGHT_TYPE GetLightType() { return m_eLightType; }
	D3DXVECTOR4* GetDiffuse() { return &m_vDiffuse; }
	D3DXVECTOR4* GetSpecular() { return &m_vSpecular; }
	D3DXVECTOR4* GetAmbient() { return &m_vAmbient; }
	D3DXVECTOR4* GetPos() { return &m_vPos; }
	D3DXVECTOR4* GetDir() { return &m_vDir; }
	float GetRange() { return m_fRange; }

	float GetFar() { return m_fFar; }
	float GetNear() { return m_fNear; }
	float GetDist() { return m_fDist; }

	D3DXMATRIX* GetView() { return &m_mView; }
	D3DXMATRIX* GetProj() { return &m_mProj; }

	LPD3DXMESH GetSphere() { return m_pSphere; }

public:
	explicit CLight(TCHAR* _tszObjKey,
		OBJ_TYPE _eObjType,
		DWORD _dwIndex,
		LIGHT_TYPE _eLightType,
		D3DXVECTOR4* _pDiffuse,
		D3DXVECTOR4* _pSpecular,
		D3DXVECTOR4* _pAmbient,
		D3DXVECTOR4* _pPos,
		D3DXVECTOR4* _pDir,
		float _fRange);
	virtual ~CLight();
};
