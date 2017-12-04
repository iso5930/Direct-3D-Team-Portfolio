#pragma once
#include "traileffect.h"

class CButcher_AxeTrail :
	public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CButcher_AxeTrail(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CButcher_AxeTrail(void);
};
