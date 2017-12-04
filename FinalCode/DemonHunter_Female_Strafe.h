#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_Strafe : public CPlayerState
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
	explicit CDemonHunter_Female_Strafe(int _iPushSlot);
	virtual ~CDemonHunter_Female_Strafe();
};
