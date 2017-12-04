#include "StdAfx.h"
#include "Enchantress_1HS_knockback_loop_01.h"

CEnchantress_1HS_knockback_loop_01::CEnchantress_1HS_knockback_loop_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_KNOCKBACK_LOOP_01;
}

CEnchantress_1HS_knockback_loop_01::~CEnchantress_1HS_knockback_loop_01()
{
}

void CEnchantress_1HS_knockback_loop_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(57);
}

CFollowerState* CEnchantress_1HS_knockback_loop_01::Action()
{
	return NULL;
}
