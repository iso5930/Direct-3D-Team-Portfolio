#pragma once
#include "effect.h"

class CCollisionCom;
class CWizard_Disintegrate_FlashEffect : public CEffect
{
private:
	float	m_fTime;
	int		m_iMode;
	CCollisionCom* m_pCollisionCom;
	float	m_fResetTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	void Mode1();
	void Mode2();

public:
	void AddCollisionComponent();
	void ResetCollision();

public:
	explicit CWizard_Disintegrate_FlashEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_Disintegrate_FlashEffect(void);
};