#pragma once

#include "Slot.h"

class CMonk_TempestRush_StaffEffect;
class CMonkTempestRushSlot : public CSlot
{
private:
	float	m_fTickTime;
	int	m_iSoundMgr;
	CMonk_TempestRush_StaffEffect* m_pStaffEffect;

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CMonkTempestRushSlot();
	virtual ~CMonkTempestRushSlot();
};