#pragma once

#include "Slot.h"

class CWitchDoctorHauntSlot : public CSlot
{
private:
	float m_fTickTime;

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWitchDoctorHauntSlot();
	virtual ~CWitchDoctorHauntSlot();
};