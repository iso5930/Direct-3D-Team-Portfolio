#pragma once
#include "object.h"

class CParticle;
class CParticleEffect : public CObject
{
protected:
	ParticleValue* m_pParticleValue;
	Particle*	m_pVS;
	CObject*	m_pOwner;
	DWORD		m_dwParticleMaxCnt;
	DWORD		m_dwParticleOffset;
	CParticle*	m_pParticle;

protected:
	DWORD		m_dwCount;

public:
	virtual void Initialize();
	virtual int Update();
	virtual void Render();
	virtual void Release();

public:
	int	 Add_Particle(ParticleValue _ParticleValue); //��ƼŬ �߰�.
	void Release_Particle(DWORD _dwCur); //��ƼŬ ����.

public:
	explicit CParticleEffect(TCHAR* _tszObjKey, OBJ_TYPE _eObjType, CObject* _pOwner, DWORD _dwParticleCnt, DWORD _dwParticleOffset, TCHAR* _tszTexKey);
	virtual ~CParticleEffect(void);
};