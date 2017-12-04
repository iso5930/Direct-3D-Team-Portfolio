#pragma once
#include "effect.h"

class CWizard_Disintegrate_RayEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_Disintegrate_RayEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Disintegrate_RayEffect(void);
};
