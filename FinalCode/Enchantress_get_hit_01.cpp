#include "StdAfx.h"
#include "Enchantress_get_hit_01.h"

CEnchantress_get_hit_01::CEnchantress_get_hit_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_GET_HIT_01;
}

CEnchantress_get_hit_01::~CEnchantress_get_hit_01()
{
}

void CEnchantress_get_hit_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(37);
}

CFollowerState* CEnchantress_get_hit_01::Action()
{
	return NULL;
}
