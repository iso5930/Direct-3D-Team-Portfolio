#include "StdAfx.h"
#include "Enchantress_1HS_resurrection_outro_01.h"

CEnchantress_1HS_resurrection_outro_01::CEnchantress_1HS_resurrection_outro_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_1HS_RESURRECTION_OUTRO_01;
}

CEnchantress_1HS_resurrection_outro_01::~CEnchantress_1HS_resurrection_outro_01()
{
}

void CEnchantress_1HS_resurrection_outro_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(50);
}

CFollowerState* CEnchantress_1HS_resurrection_outro_01::Action()
{
	return NULL;
}
