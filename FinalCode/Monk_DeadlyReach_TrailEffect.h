#pragma once
#include "TrailEffect.h"

class CMonk_DeadlyReach_TrailEffect : public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_DeadlyReach_TrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CMonk_DeadlyReach_TrailEffect(void);
};