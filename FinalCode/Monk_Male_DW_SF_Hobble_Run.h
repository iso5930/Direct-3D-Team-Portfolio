#pragma once
#include "playerstate.h"

class CMonk_Male_DW_SF_Hobble_Run :	public CPlayerState
{
private:
	int		m_iPushSlot;
	int		m_iMode;	

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	CPlayerState* Mode0();
	CPlayerState* Mode1();
	CPlayerState* SlotAction(int _iIndex);

public:
	explicit CMonk_Male_DW_SF_Hobble_Run(int	_iPushSlot);
	virtual ~CMonk_Male_DW_SF_Hobble_Run(void);
};
