#pragma once
#include "particleeffect.h"

class CDestory_BombEffect : public CParticleEffect
{
private:
	bool m_bDeath;
	float	m_fTime;
	float	m_fCreateTime;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();
	
public:
	explicit CDestory_BombEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, TCHAR* _tszName);
	virtual ~CDestory_BombEffect(void);
};