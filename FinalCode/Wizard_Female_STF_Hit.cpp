#include "StdAfx.h"
#include "Wizard_Female_STF_Hit.h"

CWizard_Female_STF_Hit::CWizard_Female_STF_Hit(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_STF_HIT;
}

CWizard_Female_STF_Hit::~CWizard_Female_STF_Hit(void)
{
}

void CWizard_Female_STF_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(35);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_STF_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_STF_Idle;
	}
	return NULL;
}