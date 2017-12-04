#pragma once
#include "effect.h"

class CZombieFemale_Spit :
	public CEffect
{
private:
	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vFirstPos;
	
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CZombieFemale_Spit(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CZombieFemale_Spit(void);
};
