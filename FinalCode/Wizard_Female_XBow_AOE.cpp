#include "StdAfx.h"
#include "Wizard_Female_XBow_AOE.h"

CWizard_Female_XBow_AOE::CWizard_Female_XBow_AOE(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_XBOW_AOE ;
}

CWizard_Female_XBow_AOE::~CWizard_Female_XBow_AOE(void)
{
}

void CWizard_Female_XBow_AOE::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(20);


	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_XBow_AOE::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_XBow_Idle;		
	}

	return NULL;
}