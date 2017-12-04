#pragma once

#include "Slot.h"

class CWitchDoctorFirebatsSlot : public CSlot
{
private:
	float	m_fTickTime;

	float	m_fEffectTime;

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWitchDoctorFirebatsSlot();
	virtual ~CWitchDoctorFirebatsSlot();
};