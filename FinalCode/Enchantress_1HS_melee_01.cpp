#include "StdAfx.h"
#include "Enchantress_1HS_melee_01.h"

CEnchantress_1HS_melee_01::CEnchantress_1HS_melee_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_MELEE_01;
}

CEnchantress_1HS_melee_01::~CEnchantress_1HS_melee_01()
{
}

void CEnchantress_1HS_melee_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(55);
}

CFollowerState* CEnchantress_1HS_melee_01::Action()
{
	return NULL;
}
