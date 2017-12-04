#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HT_LeapAttack_Air :	public CPlayerState
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
	explicit CBarbarian_Male_1HT_LeapAttack_Air(void);
	virtual ~CBarbarian_Male_1HT_LeapAttack_Air(void);
};
