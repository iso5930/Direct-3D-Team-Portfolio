#pragma once

#include "Slot.h"

class CWizardElectrocuteSlot : public CSlot
{
private:
	// TickTime
	float	m_fTickTime;

	int		m_iSoundNum;

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWizardElectrocuteSlot();
	virtual ~CWizardElectrocuteSlot();
};