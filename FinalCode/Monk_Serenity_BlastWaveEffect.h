#pragma once
#include "effect.h"

class CMonk_Serenity_BlastWaveEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_Serenity_BlastWaveEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_Serenity_BlastWaveEffect(void);
};