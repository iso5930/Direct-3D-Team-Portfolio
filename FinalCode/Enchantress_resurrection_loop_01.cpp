#include "StdAfx.h"
#include "Enchantress_resurrection_loop_01.h"

CEnchantress_resurrection_loop_01::CEnchantress_resurrection_loop_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_RESURRECTION_LOOP_01;
}

CEnchantress_resurrection_loop_01::~CEnchantress_resurrection_loop_01()
{
}

void CEnchantress_resurrection_loop_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);
}

CFollowerState* CEnchantress_resurrection_loop_01::Action()
{
	return NULL;
}
