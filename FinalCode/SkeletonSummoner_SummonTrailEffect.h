#pragma once
#include "traileffect_2.h"

class CSkeletonSummoner_SummonTrailEffect :
	public CTrailEffect_2
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonSummoner_SummonTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CSkeletonSummoner_SummonTrailEffect(void);
};
