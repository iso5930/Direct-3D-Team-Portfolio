#pragma once
#include "effect.h"

class CMonk_DashingStrike_AfterImageEffect : public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_DashingStrike_AfterImageEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_DashingStrike_AfterImageEffect(void);
};