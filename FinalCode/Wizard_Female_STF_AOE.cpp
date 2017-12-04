#include "StdAfx.h"
#include "Wizard_Female_STF_AOE.h"

CWizard_Female_STF_AOE::CWizard_Female_STF_AOE(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_STF_AOE;
}

CWizard_Female_STF_AOE::~CWizard_Female_STF_AOE(void)
{
}

void CWizard_Female_STF_AOE::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(19);


	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_STF_AOE::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_STF_Idle;
	}

	return NULL;
}