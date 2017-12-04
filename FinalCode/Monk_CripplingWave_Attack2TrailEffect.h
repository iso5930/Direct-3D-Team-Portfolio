#pragma once
#include "traileffect.h"

class CMonk_CripplingWave_Attack2TrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_CripplingWave_Attack2TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pMatWorld);
	virtual ~CMonk_CripplingWave_Attack2TrailEffect(void);
};