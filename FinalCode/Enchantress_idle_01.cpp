#include "StdAfx.h"
#include "Enchantress_idle_01.h"

CEnchantress_idle_01::CEnchantress_idle_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_IDLE_01;
}

CEnchantress_idle_01::~CEnchantress_idle_01()
{
}

void CEnchantress_idle_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(13);
}

CFollowerState* CEnchantress_idle_01::Action()
{
	return NULL;
}
