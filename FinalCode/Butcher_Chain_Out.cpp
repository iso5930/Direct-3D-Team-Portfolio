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
	//이펙트 충돌결과 여부에 따라 Idle로 돌아갈지 Pull Attack으로 갈지 결정이 나야 한다.

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CButcher_Walk;

	return NULL;
}
