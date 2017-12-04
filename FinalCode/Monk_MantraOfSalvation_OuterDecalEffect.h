#pragma once
#include "effect.h"

class CMonk_MantraOfSalvation_OuterDecalEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_MantraOfSalvation_OuterDecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_MantraOfSalvation_OuterDecalEffect(void);
};