#include "StdAfx.h"
#include "Enchantress_forceful_push_01.h"

CEnchantress_forceful_push_01::CEnchantress_forceful_push_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_FORCEFUL_PUSH_01;
}

CEnchantress_forceful_push_01::~CEnchantress_forceful_push_01()
{
}

void CEnchantress_forceful_push_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(38);
}

CFollowerState* CEnchantress_forceful_push_01::Action()
{
	return NULL;
}
