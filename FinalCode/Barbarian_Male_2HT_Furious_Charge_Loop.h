#pragma once
#include "playerstate.h"

class CBarbarian_Male_2HT_Furious_Charge_Loop :	public CPlayerState
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
	explicit CBarbarian_Male_2HT_Furious_Charge_Loop(void);
	virtual ~CBarbarian_Male_2HT_Furious_Charge_Loop(void);
};
