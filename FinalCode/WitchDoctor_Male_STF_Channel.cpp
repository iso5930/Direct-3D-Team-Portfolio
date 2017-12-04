#include "StdAfx.h"
#include "WitchDoctor_Male_STF_Channel.h"

CWitchDoctor_Male_STF_Channel::CWitchDoctor_Male_STF_Channel(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_STF_CHANNEL;
}

CWitchDoctor_Male_STF_Channel::~CWitchDoctor_Male_STF_Channel(void)
{
}

void CWitchDoctor_Male_STF_Channel::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(68);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_STF_Channel::Action()
{
	int iSlotNum = CPlayerState::UsingKeyMouse();

	if (iSlotNum == -1)
		return new CWitchDoctor_Male_STF_Idle;		
	else if(!(m_pOwner->GetSlot(iSlotNum)->GetSlotID() == SLOT_ID_WITCHDOCTOR_FIREBATS && m_pOwner->GetSlot(iSlotNum)->Action() == SLOT_RESULT_NULL))
		return new CWitchDoctor_Male_STF_Idle;	

	return NULL;
}
