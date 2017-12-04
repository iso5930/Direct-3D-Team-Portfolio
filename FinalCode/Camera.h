#pragma once

#include "Object.h"

class CCamera : public CObject
{
protected:
	DWORD m_dwIndex;

	float m_fFar;
	float m_fNear;

	D3DXMATRIX m_mView;
	D3DXMATRIX m_mProj;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void SetView(D3DXVECTOR3* _pPos, D3DXVECTOR3* _pAngle, D3DXVECTOR3* _pSize);
	void SetProj(float _fFovy, float _fAspect, float _fNear, float _fFar);

	float GetFar() { return m_fFar; }
	float GetNear() { return m_fNear; }

	D3DXMATRIX* GetView() { return &m_mView; }
	D3DXMATRIX* GetProj() { return &m_mProj; }

public:
	explicit CCamera(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, DWORD _dwIndex);
	virtual ~CCamera();
};