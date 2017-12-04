#pragma once
#include "playerstate.h"

class CWizard_Female_Bow_Channel :	public CPlayerState
{
private:
	// PushSlot
	int m_iPushSlot;

	// Mode
	int m_iMode;

	// Time
	float m_fTime;

private:
	CPlayerState* Mode0();

	CPlayerState* Mode1();

	CPlayerState* SlotAction(int _iIndex);

	bool IsSlotRange(int _iIndex);

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

public:
	explicit CWizard_Female_Bow_Channel(int _iPushSlot);
	virtual ~CWizard_Female_Bow_Channel(void);
};
