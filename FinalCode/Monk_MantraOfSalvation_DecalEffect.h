#pragma once
#include "effect.h"

class CMonk_MantraOfSalvation_DecalEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	CMonk_MantraOfSalvation_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	~CMonk_MantraOfSalvation_DecalEffect(void);
};
