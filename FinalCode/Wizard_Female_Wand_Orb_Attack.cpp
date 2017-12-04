#include "StdAfx.h"
#include "Wizard_Female_Wand_Orb_Attack.h"

CWizard_Female_Wand_Orb_Attack::CWizard_Female_Wand_Orb_Attack(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_WAND_ORB_ATTACK;
}

CWizard_Female_Wand_Orb_Attack::~CWizard_Female_Wand_Orb_Attack(void)
{
}

void CWizard_Female_Wand_Orb_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(41);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_Wand_Orb_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL)
		{
			if(CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & WEAPON_ID_BOW)
			{
				return new CWizard_Female_Bow_Idle;
			}
			else if (CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & WEAPON_ID_CROSSBOW)
			{
				return new CWizard_Female_XBow_Idle;
			}
			else if (CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & WEAPON_ID_STAFF)
			{
				return new CWizard_Female_STF_Idle;
			}
			else if (CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & (WEAPON_ID_TWO_HAND_AXE | WEAPON_ID_TWO_HAND_MACE | WEAPON_ID_TWO_HAND_SWORD  ))
			{
				return new CWizard_Female_STF_Idle;
			}
		}

		if (CItemMgr::GetInstance()->GetItemInEquip(11) != NULL && CItemMgr::GetInstance()->GetItemInEquip(11)->dwItemID & WEAPON_ID_ORB )
		{
			return new CWizard_Female_1HS_Orb_Idle;
		}
		else
		{
			return new CWizard_Female_1HS_Idle;	
		}
	}

	return NULL;
}
