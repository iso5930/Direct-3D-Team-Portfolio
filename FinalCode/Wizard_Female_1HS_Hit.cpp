#include "StdAfx.h"
#include "Wizard_Female_1HS_Hit.h"

CWizard_Female_1HS_Hit::CWizard_Female_1HS_Hit(void)
{
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_IDLE;
}

CWizard_Female_1HS_Hit::~CWizard_Female_1HS_Hit(void)
{
}

void CWizard_Female_1HS_Hit::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(39);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Idle;	
		
	}

	return NULL;
}
