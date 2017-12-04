#pragma once
#include "effect.h"

class CWizard_ExplosiveBlast_CastingEffect;
class CWizard_ExplosiveBlast_DummyEffect : public CEffect
{
private:
	float m_fTime;
	int	  m_iMode;
	float m_fCreateTime;
	CWizard_ExplosiveBlast_CastingEffect* m_pCastingEffect;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CWizard_ExplosiveBlast_DummyEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_ExplosiveBlast_DummyEffect(void);
};