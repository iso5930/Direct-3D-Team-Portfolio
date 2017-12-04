#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB2_Knockback : public CPlayerState
{
private:
	D3DXVECTOR3 m_vDir;

	float		m_fTime;

	float		m_fPower;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CDemonHunter_Female_CB2_Knockback(D3DXVECTOR3& _vDir , float _fPower );
	virtual ~CDemonHunter_Female_CB2_Knockback();
};
