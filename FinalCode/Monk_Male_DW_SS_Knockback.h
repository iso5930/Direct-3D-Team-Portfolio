#pragma once
#include "playerstate.h"

class CMonk_Male_DW_SS_Knockback :	public CPlayerState
{
private:
	D3DXVECTOR3 m_vDir;

	float		m_fTime;

	float		m_fPower;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_DW_SS_Knockback(D3DXVECTOR3& _vDir , float _fPower );
	virtual ~CMonk_Male_DW_SS_Knockback(void);
};
