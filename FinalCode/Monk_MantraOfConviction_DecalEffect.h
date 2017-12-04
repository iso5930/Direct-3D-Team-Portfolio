#pragma once
#include "effect.h"

class CMonk_MantraOfConviction_DecalEffect : public CEffect
{

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_MantraOfConviction_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_MantraOfConviction_DecalEffect(void);
};
