#include "StdAfx.h"
#include "Wizard_Female_2Hs_Summon.h"

CWizard_Female_2HS_Summon::CWizard_Female_2HS_Summon(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_2HS_SUMMON;
}

CWizard_Female_2HS_Summon::~CWizard_Female_2HS_Summon(void)
{
}

void CWizard_Female_2HS_Summon::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(7);


	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_2HS_Summon::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_2HS_Idle;
	}

	return NULL;
}