#pragma once
#include "traileffect.h"

class CSkeleton_AxeTrailEffect :
	public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();
	
public:
	explicit CSkeleton_AxeTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CSkeleton_AxeTrailEffect(void);
};
