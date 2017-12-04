#pragma once
#include "effect.h"

class CSkeletonSummoner_SummonSkeleton :
	public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonSummoner_SummonSkeleton(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pPos);
	virtual ~CSkeletonSummoner_SummonSkeleton(void);
};
