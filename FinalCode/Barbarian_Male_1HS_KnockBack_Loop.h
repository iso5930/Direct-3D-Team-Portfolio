#pragma once
#include "playerstate.h"

class CBarbarian_Male_1HS_Knockback_Loop :	public CPlayerState
{
private:
	D3DXVECTOR3 m_vDir;

	float		m_fTime;

	float		m_fPower;
public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CBarbarian_Male_1HS_Knockback_Loop(D3DXVECTOR3& _vDir , float _fPower );
	virtual ~CBarbarian_Male_1HS_Knockback_Loop(void);
};
