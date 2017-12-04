#include "StdAfx.h"
#include "Enchantress_HTH_forceful_push_01.h"

CEnchantress_HTH_forceful_push_01::CEnchantress_HTH_forceful_push_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_FORCEFUL_PUSH_01;
}

CEnchantress_HTH_forceful_push_01::~CEnchantress_HTH_forceful_push_01()
{
}

void CEnchantress_HTH_forceful_push_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(29);
}

CFollowerState* CEnchantress_HTH_forceful_push_01::Action()
{
	return NULL;
}
