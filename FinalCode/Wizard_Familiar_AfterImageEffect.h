#pragma once
#include "effect.h"

class CWizard_Familiar_AfterImageEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Familiar_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Familiar_AfterImageEffect(void);
};
