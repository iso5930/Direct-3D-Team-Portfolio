#include "StdAfx.h"
#include "Enchantress_melee_01.h"

CEnchantress_melee_01::CEnchantress_melee_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_MELEE_01;
}

CEnchantress_melee_01::~CEnchantress_melee_01()
{
}

void CEnchantress_melee_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(9);
}

CFollowerState* CEnchantress_melee_01::Action()
{
	return NULL;
}
