#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB1_Idle : public CPlayerState
{
private:
	// Mode
	int m_iMode;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	// Mode0
	CPlayerState* Mode0();

	// Mode1
	CPlayerState* Mode1();

private:
	CPlayerState* SlotAction(int _iIndex);
	bool IsSlotRange(int _iIndex);

public:
	explicit CDemonHunter_Female_CB1_Idle();
	virtual ~CDemonHunter_Female_CB1_Idle();
};
