#pragma once	
#include "playerstate.h"

class CBarbarian_Male_1HS_Furious_Charge_Loop :	public CPlayerState
{
private:
	D3DXVECTOR3 m_vDest;
	D3DXVECTOR3 m_vDist;
	D3DXVECTOR3 m_vDir;
	float		m_fLeagth;

	int			m_iMode;
	float		m_fTime;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	CPlayerState* Mode0();	
	CPlayerState* Mode1();

public:
	explicit CBarbarian_Male_1HS_Furious_Charge_Loop(void);
	virtual ~CBarbarian_Male_1HS_Furious_Charge_Loop(void);
};
