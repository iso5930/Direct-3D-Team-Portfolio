#include "StdAfx.h"
#include "Enchantress_HTH_resurrection_loop_01.h"

CEnchantress_HTH_resurrection_loop_01::CEnchantress_HTH_resurrection_loop_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_RESURRECTION_LOOP_01;
}

CEnchantress_HTH_resurrection_loop_01::~CEnchantress_HTH_resurrection_loop_01()
{
}

void CEnchantress_HTH_resurrection_loop_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(20);
}

CFollowerState* CEnchantress_HTH_resurrection_loop_01::Action()
{
	return NULL;
}
