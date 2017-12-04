#include "StdAfx.h"
#include "Enchantress_HTH_knockback_land_01.h"

CEnchantress_HTH_knockback_land_01::CEnchantress_HTH_knockback_land_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_KNOCKBACK_LAND_01;
}

CEnchantress_HTH_knockback_land_01::~CEnchantress_HTH_knockback_land_01()
{
}

void CEnchantress_HTH_knockback_land_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(27);
}

CFollowerState* CEnchantress_HTH_knockback_land_01::Action()
{
	return NULL;
}
