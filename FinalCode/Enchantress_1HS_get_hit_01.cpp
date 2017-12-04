#include "StdAfx.h"
#include "Enchantress_1HS_get_hit_01.h"

CEnchantress_1HS_get_hit_01::CEnchantress_1HS_get_hit_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_GET_HIT_01;
}

CEnchantress_1HS_get_hit_01::~CEnchantress_1HS_get_hit_01()
{
}

void CEnchantress_1HS_get_hit_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(60);
}

CFollowerState* CEnchantress_1HS_get_hit_01::Action()
{
	return NULL;
}
