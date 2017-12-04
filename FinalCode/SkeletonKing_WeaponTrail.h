#pragma once
#include "effect.h"

class CSkeletonKing_WeaponTrail :
	public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonKing_WeaponTrail(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CSkeletonKing_WeaponTrail(void);
};
