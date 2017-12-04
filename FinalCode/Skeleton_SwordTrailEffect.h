#pragma once
#include "traileffect.h"

class CSkeleton_SwordTrailEffect :
	public CTrailEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeleton_SwordTrailEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, D3DXMATRIX* _pMatrix);
	virtual ~CSkeleton_SwordTrailEffect(void);
};
