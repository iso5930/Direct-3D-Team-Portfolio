#pragma once
#include "playerstate.h"

class CWitchDoctor_Male_Mojo_1HT_Run :	public CPlayerState
{
private:
	//SlotPush
	int m_iSlotPush;

public:
	virtual void Initialize();
	virtual CPlayerState* Action();

private:
	// Event
	CPlayerState* Mode0();

	// Attack Target
	CPlayerState* Mode1();

private:
	CPlayerState* SlotAction(int _iIndex);

	bool IsSlotRange(int _iIndex);

public:
	explicit CWitchDoctor_Male_Mojo_1HT_Run(int _iSlotPush);
	virtual ~CWitchDoctor_Male_Mojo_1HT_Run(void);
};
