#pragma once
#include "playerstate.h"

class CMonk_Male_DW_SS_Run :	public CPlayerState
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
	explicit CMonk_Male_DW_SS_Run(int _iSlotPush);
	virtual ~CMonk_Male_DW_SS_Run(void);
};
