#pragma once
#include "playerstate.h"

class CMonk_Male_2HT_DashingStrike :	public CPlayerState
{
private:
	D3DXVECTOR3 m_vDest;

	D3DXVECTOR3 m_vDist;

	D3DXVECTOR3 m_vDir;

	float		m_fLeagth;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CMonk_Male_2HT_DashingStrike(void);
	virtual ~CMonk_Male_2HT_DashingStrike(void);
};
