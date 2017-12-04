#pragma once

#include "Slot.h"

class CWizardNearAttackSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWizardNearAttackSlot();
	virtual ~CWizardNearAttackSlot();
};
