#pragma once

#include "Slot.h"

class CWizard_Disintegrate_FlashEffect;
class CWizard_Disintegrate_RayEffect;
class CWizardDisintegrateSlot : public CSlot
{
private:
	float m_fTickTime;

	int	m_iSoundNum;

	CWizard_Disintegrate_RayEffect* m_pRayEffect;
	CWizard_Disintegrate_FlashEffect* m_pFlashEffect[2];
	CWizard_Disintegrate_FlashEffect* m_pHitEffect[2];

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWizardDisintegrateSlot();
	virtual ~CWizardDisintegrateSlot();
};