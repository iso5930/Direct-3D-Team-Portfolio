#include "StdAfx.h"
#include "Enchantress_buff_01.h"

CEnchantress_buff_01::CEnchantress_buff_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_BUFF_01;
}

CEnchantress_buff_01::~CEnchantress_buff_01()
{
}

void CEnchantress_buff_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(43);
}

CFollowerState* CEnchantress_buff_01::Action()
{
	return NULL;
}
