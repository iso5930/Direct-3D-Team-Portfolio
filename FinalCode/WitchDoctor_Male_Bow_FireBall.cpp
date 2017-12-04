#include "StdAfx.h"
#include "WitchDoctor_Male_Bow_FireBall.h"

CWitchDoctor_Male_Bow_FireBall::CWitchDoctor_Male_Bow_FireBall(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_BOW_FIREBALL;
}

CWitchDoctor_Male_Bow_FireBall::~CWitchDoctor_Male_Bow_FireBall(void)
{
}

void CWitchDoctor_Male_Bow_FireBall::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(72);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWitchDoctor_Male_Bow_FireBall::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWitchDoctor_Male_Bow_Idle;	
	}
	return NULL;
}
