#include "StdAfx.h"
#include "Enchantress_HTH_run_01.h"

CEnchantress_HTH_run_01::CEnchantress_HTH_run_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_RUN_01;
}

CEnchantress_HTH_run_01::~CEnchantress_HTH_run_01()
{
}

void CEnchantress_HTH_run_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(18);
}

CFollowerState* CEnchantress_HTH_run_01::Action()
{
	return NULL;
}
