#include "StdAfx.h"
#include "Enchantress_knockback_01.h"

CEnchantress_knockback_01::CEnchantress_knockback_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_KNOCKBACK_01;
}

CEnchantress_knockback_01::~CEnchantress_knockback_01()
{
}

void CEnchantress_knockback_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(12);
}

CFollowerState* CEnchantress_knockback_01::Action()
{
	return NULL;
}
