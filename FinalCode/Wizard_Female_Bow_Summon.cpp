#include "StdAfx.h"
#include "Wizard_Female_Bow_Summon.h"

CWizard_Female_Bow_Summon::CWizard_Female_Bow_Summon(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_BOW_SUMMON;
}

CWizard_Female_Bow_Summon::~CWizard_Female_Bow_Summon(void)
{
}

void CWizard_Female_Bow_Summon::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(7);


	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_Bow_Summon::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_Bow_Idle;
	}

	return NULL;
}