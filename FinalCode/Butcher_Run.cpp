#include "StdAfx.h"
#include "Butcher_Run.h"

CButcher_Run::CButcher_Run(D3DXVECTOR3* _pDir)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_RUN;
	
	// Dir
	m_vDir = *_pDir;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;
}

CButcher_Run::~CButcher_Run(void)
{
}

void CButcher_Run::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimation
	m_pOwner->SetAnimation(3);

	m_pPathFindCom->m_fSpeed = 1500.f;

	m_pPathFindCom->Enable();
}

CMonsterState* CButcher_Run::Action()
{
	D3DXVECTOR3 vMovePos = m_pTransformCom->m_vPos + (m_vDir * 40.f);

	CNaviCell* pNaviCell = CPathFindMgr::GetInstance()->FindCell(&vMovePos);

	m_pPathFindCom->Move(&vMovePos);

	//if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	//	return new CSkeleton_King_Walk;

	D3DXVECTOR3 vNextPos;
	m_pPathFindCom->IsMove(&vNextPos);
	if(pNaviCell == NULL)
	{
		m_pPathFindCom->m_fSpeed = 120.f;
		return new CButcher_Stunned;
	}

	switch(m_iMode)
	{
	case 0:
		return Mode0();
	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CButcher_Run::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTime > 0.0f)
	{
		m_pOwner->CreateAttack();
		
		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}

CMonsterState* CButcher_Run::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 5.0f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}
