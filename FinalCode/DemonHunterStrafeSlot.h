#pragma once

#include "Slot.h"

class CDemonHunter_Strafe_AfterImageEffect;
class CDemonHunter_Strafe_SpinEffect;
class CDemonHunterStrafeSlot : public CSlot
{
private:	
	CDemonHunter_Strafe_AfterImageEffect*	m_pAfterImage[3];
	CDemonHunter_Strafe_SpinEffect*			m_pSpinEffect;
	float	m_fTime; 
	float	m_fAngleTime;

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CDemonHunterStrafeSlot();
	virtual ~CDemonHunterStrafeSlot();
};