#include "StdAfx.h"
#include "Enchantress_HTH_knockback_loop_01.h"

CEnchantress_HTH_knockback_loop_01::CEnchantress_HTH_knockback_loop_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_KNOCKBACK_LOOP_01;
}

CEnchantress_HTH_knockback_loop_01::~CEnchantress_HTH_knockback_loop_01()
{
}

void CEnchantress_HTH_knockback_loop_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(26);
}

CFollowerState* CEnchantress_HTH_knockback_loop_01::Action()
{
	return NULL;
}