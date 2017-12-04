#pragma once
#include "effect.h"

class CSkeletonKing_SummonShell :
	public CEffect
{
private:
	float m_fSize;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CSkeletonKing_SummonShell(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CSkeletonKing_SummonShell(void);
};
