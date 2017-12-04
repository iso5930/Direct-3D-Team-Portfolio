#include "StdAfx.h"
#include "Wizard_Female_1HS_Orb_Hit.h"

CWizard_Female_1HS_Orb_Hit::CWizard_Female_1HS_Orb_Hit(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_ORB_HIT;
}

CWizard_Female_1HS_Orb_Hit::~CWizard_Female_1HS_Orb_Hit(void)
{
}

void CWizard_Female_1HS_Orb_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(38);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_Orb_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Orb_Idle;
	}

	return NULL;
}
