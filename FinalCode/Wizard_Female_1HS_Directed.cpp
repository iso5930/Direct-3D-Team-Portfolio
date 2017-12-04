#include "StdAfx.h"
#include "Wizard_Female_1HS_Directed.h"

CWizard_Female_1HS_Directed::CWizard_Female_1HS_Directed(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_DIRECTED;
}

CWizard_Female_1HS_Directed::~CWizard_Female_1HS_Directed(void)
{
}

void CWizard_Female_1HS_Directed::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(12);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_Directed::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Idle;	
	}

	return NULL;
}
