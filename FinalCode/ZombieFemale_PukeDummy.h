#pragma once
#include "effect.h"

class CZombieFemale_PukeDummy :
	public CEffect
{
private:
	float m_fDestroyTime;
	float m_fEffectTime;
	float m_fDecalTime;
	D3DXVECTOR3 m_vDir;
	bool m_bCreate;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CZombieFemale_PukeDummy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CZombieFemale_PukeDummy(void);
};
