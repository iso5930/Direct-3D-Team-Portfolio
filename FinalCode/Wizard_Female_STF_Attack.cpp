#include "StdAfx.h"
#include "Wizard_Female_STF_Attack.h"

CWizard_Female_STF_Attack::CWizard_Female_STF_Attack(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_STF_ATTACK;
}

CWizard_Female_STF_Attack::~CWizard_Female_STF_Attack(void)
{
}

void CWizard_Female_STF_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(45);


	// Clear
	m_pPathFindCom->Clear();

	if(m_pOwner->GetSlot(m_pOwner->GetLastPushSlotNum())->GetSlotID() == SLOT_ID_WIZARD_PUNCH ||
		m_pOwner->GetSlot(m_pOwner->GetLastPushSlotNum())->GetSlotID() == SLOT_ID_WIZARD_NEAR_ATTACK )
		m_pOwner->CreateAttack();
}

CPlayerState* CWizard_Female_STF_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		m_pOwner->RemoveAttack();
		return new CWizard_Female_STF_Idle;
	}

	return NULL;
}