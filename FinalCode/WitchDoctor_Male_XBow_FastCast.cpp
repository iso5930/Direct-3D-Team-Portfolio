#include "StdAfx.h"
#include "WitchDoctor_Male_XBow_FastCast.h"

CWitchDoctor_Male_XBow_FastCast::CWitchDoctor_Male_XBow_FastCast(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_XBOW_FASTCAST;
}

CWitchDoctor_Male_XBow_FastCast::~CWitchDoctor_Male_XBow_FastCast(void)
{
}

void CWitchDoctor_Male_XBow_FastCast::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(73);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_XBow_FastCast::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		int iSlotNum = CPlayerState::UsingKeyMouse();

		if (iSlotNum != -1)
		{
			return new CWitchDoctor_Male_XBow_Idle;	
		}
		else if (m_pOwner->GetSlot(iSlotNum)->GetSlotID() == SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE)
		{
			if (m_pOwner->GetSlot(iSlotNum)->Action() == SLOT_RESULT_NULL)
			{
				return new CWitchDoctor_Male_XBow_FastCast;	
			}
		}

		return new CWitchDoctor_Male_XBow_Idle;	
	}
	return NULL;
}
