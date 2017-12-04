#pragma once
#include "effect.h"

class CSkeletonKing_CenterTrail :
	public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonKing_CenterTrail(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CSkeletonKing_CenterTrail(void);
};
