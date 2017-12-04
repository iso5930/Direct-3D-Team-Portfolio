#pragma once
#include "TrailEffect.h"

class CMonk_CripplingWave_Attack1TrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_CripplingWave_Attack1TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXMATRIX* _pMatWorld);
	virtual ~CMonk_CripplingWave_Attack1TrailEffect(void);
};
