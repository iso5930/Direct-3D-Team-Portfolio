#pragma once
#include "effect.h"

class CWizard_Blizzard_DecalEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Blizzard_DecalEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Blizzard_DecalEffect(void);
};