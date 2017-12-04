#pragma once
#include "effect.h"

class CZombieFemale_PukeBase :
	public CEffect
{
private:
	D3DXVECTOR3 m_vDir;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CZombieFemale_PukeBase(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3 *_pDir);
	virtual ~CZombieFemale_PukeBase(void);
};
