#include "StdAfx.h"
#include "Enchantress_run_01.h"

CEnchantress_run_01::CEnchantress_run_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_RUN_01;
}

CEnchantress_run_01::~CEnchantress_run_01()
{
}

void CEnchantress_run_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);
}

CFollowerState* CEnchantress_run_01::Action()
{
	return NULL;
}
