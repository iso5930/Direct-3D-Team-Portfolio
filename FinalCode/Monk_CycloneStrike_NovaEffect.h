#pragma once
#include "effect.h"

class CMonk_CycloneStrike_NovaEffect : public CEffect
{
public:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_CycloneStrike_NovaEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_CycloneStrike_NovaEffect(void);
};