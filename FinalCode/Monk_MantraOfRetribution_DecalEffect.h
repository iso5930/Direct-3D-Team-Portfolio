#pragma once
#include "effect.h"

class CMonk_MantraOfRetribution_DecalEffect : public CEffect
{

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	CMonk_MantraOfRetribution_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	~CMonk_MantraOfRetribution_DecalEffect(void);
};
