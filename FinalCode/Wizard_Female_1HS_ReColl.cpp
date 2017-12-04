#include "StdAfx.h"
#include "Wizard_Female_1HS_ReColl.h"

CWizard_Female_1HS_ReColl::CWizard_Female_1HS_ReColl(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_RECOLL;
}

CWizard_Female_1HS_ReColl::~CWizard_Female_1HS_ReColl(void)
{
}

void CWizard_Female_1HS_ReColl::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(48);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_ReColl::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Idle;	
	}

	return NULL;
}