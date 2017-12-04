#pragma once
#include "effect.h"

class CMonk_BreathOfHeaven_NovaEffect : public CEffect
{
private:
	float m_fTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CMonk_BreathOfHeaven_NovaEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_BreathOfHeaven_NovaEffect(void);
};