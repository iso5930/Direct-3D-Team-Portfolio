#pragma once
#include "effect.h"

class CWarden_Entangle :
	public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	float m_fTime;
	int m_iMode;
	float m_fSizeChangeTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

private:
	void Mode0();
	void Mode1();

public:
	explicit CWarden_Entangle(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CWarden_Entangle(void);
};
