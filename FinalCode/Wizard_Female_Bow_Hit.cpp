#include "StdAfx.h"
#include "Wizard_Female_Bow_Hit.h"

CWizard_Female_Bow_Hit::CWizard_Female_Bow_Hit(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_BOW_HIT;
}

CWizard_Female_Bow_Hit::~CWizard_Female_Bow_Hit(void)
{
}

void CWizard_Female_Bow_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(36);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_Bow_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_Bow_Idle;
	}

	return NULL;
}