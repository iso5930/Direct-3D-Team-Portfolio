#pragma once

#include "Slot.h"

class CBarbarianWhirlwindSlot : public CSlot
{
private:
	float m_fTime;

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CBarbarianWhirlwindSlot();
	virtual ~CBarbarianWhirlwindSlot();
};
