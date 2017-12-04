#pragma once
#include "effect.h"

class CWizard_StormArmor_CastingEffect : public CEffect
{
private:
	float m_fTime;
	float m_fAccTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_StormArmor_CastingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_StormArmor_CastingEffect(void);
};