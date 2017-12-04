#pragma once
#include "particleeffect.h"

class CMonk_MantraOfRetribution_CreateEffect : public CParticleEffect
{
private:
	float m_fTime;
	float m_fAccTime;
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
	explicit CMonk_MantraOfRetribution_CreateEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CMonk_MantraOfRetribution_CreateEffect(void);
};