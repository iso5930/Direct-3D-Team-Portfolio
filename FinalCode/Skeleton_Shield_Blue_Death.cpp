#include "StdAfx.h"
#include "Skeleton_Shield_Blue_Death.h"

CSkeleton_Shield_Blue_Death::CSkeleton_Shield_Blue_Death(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SHIELD_BLUE_DEATH;

	// Death
	m_bDeath = false;
}

CSkeleton_Shield_Blue_Death::~CSkeleton_Shield_Blue_Death(void)
{
}

void CSkeleton_Shield_Blue_Death::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Skeleton_Shield_Death.ogg"));
}

CMonsterState* CSkeleton_Shield_Blue_Death::Action()
{
	if(!m_bDeath)
	{
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