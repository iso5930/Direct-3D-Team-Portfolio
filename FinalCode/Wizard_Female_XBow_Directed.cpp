#include "StdAfx.h"
#include "Wizard_Female_XBow_Directed.h"

CWizard_Female_XBow_Directed::CWizard_Female_XBow_Directed(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_XBOW_DIRECTED;
}

CWizard_Female_XBow_Directed::~CWizard_Female_XBow_Directed(void)
{
}

void CWizard_Female_XBow_Directed::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(10);


	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_XBow_Directed::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_XBow_Idle;
	}

	return NULL;
}