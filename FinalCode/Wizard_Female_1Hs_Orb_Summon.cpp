#include "StdAfx.h"
#include "Wizard_Female_1HS_Orb_Summon.h"

CWizard_Female_1HS_Orb_Summon::CWizard_Female_1HS_Orb_Summon(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_ORB_SUMMON;
}

CWizard_Female_1HS_Orb_Summon::~CWizard_Female_1HS_Orb_Summon(void)
{
}

void CWizard_Female_1HS_Orb_Summon::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(8);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_Orb_Summon::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Orb_Idle;
	}

	return NULL;
}
