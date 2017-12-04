#pragma once
#include "effect.h"

class CWarden_EntangleDummy :
	public CEffect
{
private:
	bool m_bEffect;
	bool m_bDestroyCheck;
	float m_fDestroyTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWarden_EntangleDummy(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWarden_EntangleDummy(void);
};
