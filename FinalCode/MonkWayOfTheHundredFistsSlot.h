#pragma once

#include "Slot.h"

class CMonkWayOfTheHundredFistsSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CMonkWayOfTheHundredFistsSlot();
	virtual ~CMonkWayOfTheHundredFistsSlot();
};