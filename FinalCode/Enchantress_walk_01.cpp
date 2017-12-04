#include "StdAfx.h"
#include "Enchantress_walk_01.h"

CEnchantress_walk_01::CEnchantress_walk_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_WALK_01;
}

CEnchantress_walk_01::~CEnchantress_walk_01()
{
}

void CEnchantress_walk_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);
}

CFollowerState* CEnchantress_walk_01::Action()
{
	return NULL;
}
