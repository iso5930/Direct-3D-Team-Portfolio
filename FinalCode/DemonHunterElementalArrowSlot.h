#pragma once

#include "Slot.h"

class CDemonHunterElementalArrowSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CDemonHunterElementalArrowSlot();
	virtual ~CDemonHunterElementalArrowSlot();
};