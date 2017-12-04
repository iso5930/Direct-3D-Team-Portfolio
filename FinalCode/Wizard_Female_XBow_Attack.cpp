#include "StdAfx.h"
#include "Wizard_Female_XBow_Attack.h"

CWizard_Female_XBow_Attack::CWizard_Female_XBow_Attack(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_XBOW_ATTACK;
}

CWizard_Female_XBow_Attack::~CWizard_Female_XBow_Attack(void)
{
}

void CWizard_Female_XBow_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(40);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_XBow_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_XBow_Idle;		
	}


	return NULL;
}
