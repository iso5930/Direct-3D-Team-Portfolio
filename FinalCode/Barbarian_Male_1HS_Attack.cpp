#include "StdAfx.h"
#include "Barbarian_male_1HS_Attack.h"

CBarbarian_Male_1HS_Attack::CBarbarian_Male_1HS_Attack(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_ATTACK;

	m_iMode = 0;
	m_fTime	= 0.0f;

}

CBarbarian_Male_1HS_Attack::~CBarbarian_Male_1HS_Attack(void)
{
}

void CBarbarian_Male_1HS_Attack::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(108);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HS_Attack::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HS_Idle;	
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

CPlayerState* CBarbarian_Male_1HS_Attack::Mode0()
{
	++m_iMode;
	m_fTime = 0.0f;
	m_pOwner->CreateAttack();

	return NULL;
}

CPlayerState* CBarbarian_Male_1HS_Attack::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if (m_fTime > m_pAnimController->m_dFrameTime - 0.3 )
	{
		++m_iMode;
		m_fTime = 0.0f;
		m_pOwner->RemoveAttack();	
	}
	
	return NULL;
}
