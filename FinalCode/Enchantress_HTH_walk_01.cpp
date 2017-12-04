#include "StdAfx.h"
#include "Enchantress_HTH_walk_01.h"

CEnchantress_HTH_walk_01::CEnchantress_HTH_walk_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_WALK_01;
}

CEnchantress_HTH_walk_01::~CEnchantress_HTH_walk_01()
{
}

void CEnchantress_HTH_walk_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(14);
}

CFollowerState* CEnchantress_HTH_walk_01::Action()
{
	return NULL;
}
