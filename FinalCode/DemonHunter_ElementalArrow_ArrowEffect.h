#pragma once
#include "effect.h"

class CDemonHunter_ElementalArrow_FlashEffect;
class CDemonHunter_ElementalArrow_FireEffect;
class CDemonHunter_ElementalArrow_ArrowEffect : public CEffect
{
private:
	CDemonHunter_ElementalArrow_FlashEffect* m_pFlashEffect;
	CDemonHunter_ElementalArrow_FireEffect*	m_pFireEffect;
	D3DXVECTOR3 m_vDir;
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CDemonHunter_ElementalArrow_ArrowEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, D3DXVECTOR3* _pDir);
	virtual ~CDemonHunter_ElementalArrow_ArrowEffect(void);
};