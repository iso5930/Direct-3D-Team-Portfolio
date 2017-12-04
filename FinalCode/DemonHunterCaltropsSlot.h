#pragma once

#include "Slot.h"

class CDemonHunterCaltropsSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CDemonHunterCaltropsSlot();
	virtual ~CDemonHunterCaltropsSlot();
};