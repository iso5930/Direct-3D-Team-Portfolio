#pragma once

#include "Slot.h"

class CWizardEnergyTwisterSlot : public CSlot
{
private:
	// Time
	float m_fTickTiem;


public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWizardEnergyTwisterSlot();
	virtual ~CWizardEnergyTwisterSlot();
};