#include "StdAfx.h"
#include "Butcher_Chain_Out.h"

CButcher_Chain_Out::CButcher_Chain_Out(void)
{
	m_eStateType = STATE_TYPE_BUTCHER_CHAIN_OUT;
}

CButcher_Chain_Out::~CButcher_Chain_Out(void)
{
}

void CButcher_Chain_Out::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);
}

CMonsterState* CButcher_Chain_Out::Action()
{
	//����Ʈ �浹��� ���ο� ���� Idle�� ���ư��� Pull Attack���� ���� ������ ���� �Ѵ�.

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Walk;

	return NULL;
}
