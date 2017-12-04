#include "StdAfx.h"
#include "Enchantress_HTH_Town_idle_01.h"

CEnchantress_HTH_Town_idle_01::CEnchantress_HTH_Town_idle_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_TOWN_IDLE_01;
}

CEnchantress_HTH_Town_idle_01::~CEnchantress_HTH_Town_idle_01()
{
}

void CEnchantress_HTH_Town_idle_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(16);
}

CFollowerState* CEnchantress_HTH_Town_idle_01::Action()
{
	return NULL;
}