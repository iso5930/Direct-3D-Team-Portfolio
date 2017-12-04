#include "StdAfx.h"
#include "WitchDoctor_Male_Mojo_1HT_Channel.h"

CWitchDoctor_Male_Mojo_1HT_Channel::CWitchDoctor_Male_Mojo_1HT_Channel(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_MOJO_1HT_CHANNEL;
}

CWitchDoctor_Male_Mojo_1HT_Channel::~CWitchDoctor_Male_Mojo_1HT_Channel(void)
{
}

void CWitchDoctor_Male_Mojo_1HT_Channel::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(68);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_Mojo_1HT_Channel::Action()
{
	int iSlotNum = CPlayerState::UsingKeyMouse();

	if (iSlotNum == -1)
		return new CWitchDoctor_Male_Mojo_1HT_Idle;		
	else if(!(m_pOwner->GetSlot(iSlotNum)->GetSlotID() == SLOT_ID_WITCHDOCTOR_FIREBATS && m_pOwner->GetSlot(iSlotNum)->Action() == SLOT_RESULT_NULL))
		return new CWitchDoctor_Male_Mojo_1HT_Idle;	
	
	return NULL;
}
