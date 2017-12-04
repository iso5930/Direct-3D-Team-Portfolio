#pragma once

#include "Slot.h"

class CMonkPotionSlot : public CSlot
{
public:
	// Begin
	virtual SLOT_RESULT Begin(int _iMode);

	// Action
	virtual SLOT_RESULT Action();

	// End
	virtual SLOT_RESULT End();

public:
	explicit CMonkPotionSlot();
	virtual ~CMonkPotionSlot();
};
