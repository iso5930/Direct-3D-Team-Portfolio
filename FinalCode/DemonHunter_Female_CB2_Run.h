#pragma once

#include "PlayerState.h"

class CDemonHunter_Female_CB2_Run : public CPlayerState
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
	explicit CDemonHunter_Female_CB2_Run(int _iSlotPush);
	virtual ~CDemonHunter_Female_CB2_Run();
};
