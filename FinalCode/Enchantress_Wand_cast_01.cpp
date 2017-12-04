#include "StdAfx.h"
#include "Enchantress_Wand_cast_01.h"

CEnchantress_Wand_cast_01::CEnchantress_Wand_cast_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_WAND_CAST_01;
}

CEnchantress_Wand_cast_01::~CEnchantress_Wand_cast_01()
{
}

void CEnchantress_Wand_cast_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(0);
}

CFollowerState* CEnchantress_Wand_cast_01::Action()
{
	return NULL;
}
