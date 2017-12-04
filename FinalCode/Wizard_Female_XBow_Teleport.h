#pragma once
#include "playerstate.h"

class CWizard_Female_XBow_Teleport :	public CPlayerState
{
private:
	// Time
	float m_fTiem;

	// Mode
	int	m_iMode;
	// 
	D3DXVECTOR3 m_vModeDir;

	//
	D3DXVECTOR3 m_vModeDist;


private:
	 CPlayerState* Mode0();

	 CPlayerState* Mode1();

	 CPlayerState* Mode2();


public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_XBow_Teleport(void);
	virtual ~CWizard_Female_XBow_Teleport(void);
};
