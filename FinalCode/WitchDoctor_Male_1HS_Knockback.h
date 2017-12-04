#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_1HS_Knockback :	public CPlayerState
{
private:
	D3DXVECTOR3 m_vDir;

	float		m_fTime;

	float		m_fPower;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWitchDoctor_Male_1HS_Knockback(D3DXVECTOR3& _vDir , float _fPower );
	virtual ~CWitchDoctor_Male_1HS_Knockback(void);
};