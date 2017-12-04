#include "StdAfx.h"
#include "Enchantress_HTH_buff_01.h"

CEnchantress_HTH_buff_01::CEnchantress_HTH_buff_01(int _iMode)
: CFollowerState(_iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ENCHANTRESS_HTH_BUFF_01;
}

CEnchantress_HTH_buff_01::~CEnchantress_HTH_buff_01()
{
}

void CEnchantress_HTH_buff_01::Initialize()
{
	// Initialize
	CFollowerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(33);
}

CFollowerState* CEnchantress_HTH_buff_01::Action()
{
	return NULL;
}
