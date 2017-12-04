#include "StdAfx.h"
#include "Enchantress_1HS_forceful_push_01.h"

CEnchantress_1HS_forceful_push_01::CEnchantress_1HS_forceful_push_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_FORCEFUL_PUSH_01;
}

CEnchantress_1HS_forceful_push_01::~CEnchantress_1HS_forceful_push_01()
{
}

void CEnchantress_1HS_forceful_push_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(61);
}

CFollowerState* CEnchantress_1HS_forceful_push_01::Action()
{
	return NULL;
}
