#pragma once

#include "MonkSweepingWindSlot.h"

class CMonkSweepingWindSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CMonkSweepingWindSlot();
	virtual ~CMonkSweepingWindSlot();
};