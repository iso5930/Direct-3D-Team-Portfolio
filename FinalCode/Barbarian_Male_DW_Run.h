#pragma once
#include "playerstate.h"

class CBarbarian_Male_DW_Run :	public CPlayerState
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
	explicit CBarbarian_Male_DW_Run(int _iSlotPush);
	virtual ~CBarbarian_Male_DW_Run(void);
};
