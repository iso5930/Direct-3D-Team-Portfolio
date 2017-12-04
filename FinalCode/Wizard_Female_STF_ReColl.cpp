#include "StdAfx.h"
#include "Wizard_Female_STF_ReColl.h"

CWizard_Female_STF_ReColl::CWizard_Female_STF_ReColl(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_STF_RECOLL;
}

CWizard_Female_STF_ReColl::~CWizard_Female_STF_ReColl(void)
{
}

void CWizard_Female_STF_ReColl::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(48);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_STF_ReColl::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_STF_Idle;		
	}

	return NULL;
}