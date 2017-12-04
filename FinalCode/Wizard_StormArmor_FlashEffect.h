#pragma once
#include "effect.h"

class CWizard_StormArmor_FlashEffect : public CEffect
{
private:
	float	m_fTime;
	int		m_iMode;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	explicit CWizard_StormArmor_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_StormArmor_FlashEffect(void);
};