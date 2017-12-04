#include "StdAfx.h"
#include "Wizard_Female_1HS_Orb_AOE2.h"

CWizard_Female_1HS_Orb_AOE2::CWizard_Female_1HS_Orb_AOE2(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_ORB_AOE2 ;
}

CWizard_Female_1HS_Orb_AOE2::~CWizard_Female_1HS_Orb_AOE2(void)
{
}

void CWizard_Female_1HS_Orb_AOE2::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(17);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_Orb_AOE2::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Orb_Idle;
	}

	return NULL;
}