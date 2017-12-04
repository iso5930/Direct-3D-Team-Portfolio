#pragma once

#include "Slot.h"

class CWitchDoctorMagicAttackSlot : public CSlot
{
public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWitchDoctorMagicAttackSlot();
	virtual ~CWitchDoctorMagicAttackSlot();
};
