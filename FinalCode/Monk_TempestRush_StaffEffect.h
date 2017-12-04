#pragma once
#include "effect.h"

class CMonk_TempsetRush_TrailEffect;
class CMonk_TempsetRush_DownTrailEffect;
class CCollisionCom;
class CMonk_TempestRush_StaffEffect : public CEffect
{
private:
	CMonk_TempsetRush_TrailEffect* m_pTrailEffect;
	CMonk_TempsetRush_DownTrailEffect*	m_pTrailEffect2;
	float m_fTime;
	CCollisionCom*		m_pCollisionCom;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_TempestRush_StaffEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_TempestRush_StaffEffect(void);
};