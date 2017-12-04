#pragma once
#include "playerstate.h"

class CWizard_Female_Bow_Idle :	public CPlayerState
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
	explicit CWizard_Female_Bow_Idle(void);
	virtual ~CWizard_Female_Bow_Idle(void);
};
