#pragma once
#include "playerstate.h"

class CMonk_Male_STF_Run :	public CPlayerState
{
private:
	// SlotPush
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
	explicit CMonk_Male_STF_Run(int _iSlotPush);
	virtual ~CMonk_Male_STF_Run(void);
};
