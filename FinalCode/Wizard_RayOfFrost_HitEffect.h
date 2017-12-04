#pragma once
#include "ParticleEffect.h"

class CWizard_RayOfFrost_HitEffect : public CParticleEffect
{
private:
	float	m_fCreateTime;
	bool	m_bDeath;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	explicit CWizard_RayOfFrost_HitEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner);
	virtual ~CWizard_RayOfFrost_HitEffect(void);
};