#pragma once
#include "effect.h"

class CCollisionCom;
class CMonk_SweepingWind_RingEffect : public CEffect
{
private:
	float m_fTime;
	float m_fDamageTime;
	CCollisionCom* m_pCollisionCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_SweepingWind_RingEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_SweepingWind_RingEffect(void);
};