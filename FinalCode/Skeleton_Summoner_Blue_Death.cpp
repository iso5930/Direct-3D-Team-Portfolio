#include "StdAfx.h"
#include "Skeleton_Summoner_Blue_Death.h"

CSkeleton_Summoner_Blue_Death::CSkeleton_Summoner_Blue_Death(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SUMMONER_BLUE_DEATH;

	// Death
	m_bDeath = false;
}

CSkeleton_Summoner_Blue_Death::~CSkeleton_Summoner_Blue_Death(void)
{
}

void CSkeleton_Summoner_Blue_Death::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Skeleton_Summoner_Death.ogg"));
}

CMonsterState* CSkeleton_Summoner_Blue_Death::Action()
{
	if(!m_bDeath)
	{
		//CDestory_BombFlashEfect* pFlashEffect = new CDestory_BombFlashEfect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, false, NULL);
		//m_pOwner->GetLayer()->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

		//CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
		//pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		//pTransformCom->m_vPos.y += 50.f;
		//pFlashEffect->Initialize();

		m_pOwner->Death();
		m_bDeath = true;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		CDestory_DustEffect* pDustEffect = new CDestory_DustEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pDustEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pDustEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vPos.y += 50.f;
		pDustEffect->Initialize();

		m_pOwner->Destroy();
	}

	return NULL;
}