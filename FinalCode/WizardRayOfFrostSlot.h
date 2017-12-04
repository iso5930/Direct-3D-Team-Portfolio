#pragma once

#include "Slot.h"

class CWizard_RayOfFrost_RayEffect;
class CWizard_RayOfFrost_HitEffect;
class CWizard_RayOfFrost_DummyEffect;
class CWizardRayOfFrostSlot : public CSlot
{
private:
	// TickTime
	float m_fTickTime; 

	int	m_iSoundNum; 

	CWizard_RayOfFrost_RayEffect* m_pRayEffect;
	CWizard_RayOfFrost_HitEffect* m_pHitEffect;
	CWizard_RayOfFrost_DummyEffect* m_pDummyEffect;

public:
	virtual SLOT_RESULT Begin(int _iMode);

	virtual SLOT_RESULT Action();

	virtual SLOT_RESULT End();
public:
	explicit CWizardRayOfFrostSlot();
	virtual ~CWizardRayOfFrostSlot();
};