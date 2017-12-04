#include "StdAfx.h"
#include "WitchDoctor_Male_1HT_FireBall.h"

CWitchDoctor_Male_1HT_FireBall::CWitchDoctor_Male_1HT_FireBall(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_1HT_FIREBALL;
}

CWitchDoctor_Male_1HT_FireBall::~CWitchDoctor_Male_1HT_FireBall(void)
{
}

void CWitchDoctor_Male_1HT_FireBall::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(72);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_1HT_FireBall::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_1HT_Idle;	
	}
	return NULL;
}
