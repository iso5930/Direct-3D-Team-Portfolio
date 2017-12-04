#pragma once
#include "effect.h"

class CBufferCom;
class CDemonHunter_Strafe_WeaponEffect;
class CDemonHunter_Strafe_AfterImageEffect : public CEffect
{
private:
	CBufferCom* m_pBufferCom;
	CDemonHunter_Strafe_WeaponEffect* m_pWeaponEffect[2];
	float		m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_Strafe_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CDemonHunter_Strafe_AfterImageEffect(void);
};