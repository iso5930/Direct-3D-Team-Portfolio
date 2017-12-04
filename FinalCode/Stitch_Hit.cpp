#include "StdAfx.h"
#include "Stitch_Hit.h"

CStitch_Hit::CStitch_Hit(void)
{
	// StateType
	m_eStateType = STATE_TYPE_STITCH_HIT; 
}

CStitch_Hit::~CStitch_Hit(void)
{
}

void CStitch_Hit::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Stitch_Hit.ogg"));
}

CMonsterState* CStitch_Hit::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CStitch_Run(1);

	return NULL;
}
