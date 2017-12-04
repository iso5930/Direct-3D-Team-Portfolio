#pragma once
#include "playerstate.h"

class CWizard_Female_XBow_Knockback :	public CPlayerState
{
private:
	D3DXVECTOR3 m_vDir;

	float		m_fTime;

	float		m_fPower;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_XBow_Knockback(D3DXVECTOR3& _vDir , float _fPower );
	virtual ~CWizard_Female_XBow_Knockback(void);
};
