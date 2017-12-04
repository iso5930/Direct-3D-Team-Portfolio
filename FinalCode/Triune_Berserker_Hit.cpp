#include "StdAfx.h"
#include "Triune_Berserker_Hit.h"

CTriune_Berserker_Hit::CTriune_Berserker_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_BERSERKER_HIT;
}

CTriune_Berserker_Hit::~CTriune_Berserker_Hit(void)
{
}

void CTriune_Berserker_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Berserker_Hit.ogg"));
}

CMonsterState* CTriune_Berserker_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CTriune_Berserker_Run(2);

	return NULL;
}
