#pragma once
#include "effect.h"

class CWizard_Familiar_FamiliarEffect : public CEffect
{
private:
	float	m_fTime;
	int		m_iMode;
	float	m_fCreateTime;
	float	m_fDeathTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CWizard_Familiar_FamiliarEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Familiar_FamiliarEffect(void);
};