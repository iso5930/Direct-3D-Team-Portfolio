#pragma once
#include "effect.h"

class CWizard_RayOfFrost_RayEffect : public CEffect
{
public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_RayOfFrost_RayEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_RayOfFrost_RayEffect(void);
};