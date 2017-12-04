#pragma once

#include "Slot.h"

class CBarbarianIgnorePainSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CBarbarianIgnorePainSlot();
	virtual ~CBarbarianIgnorePainSlot();
};
