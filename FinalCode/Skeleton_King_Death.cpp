#include "StdAfx.h"
#include "Skeleton_King_Death.h"

CSkeleton_King_Death::CSkeleton_King_Death(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_DEATH;

	// Death
	m_bDeath = false;
	m_bDeathEffect = false;
}

CSkeleton_King_Death::~CSkeleton_King_Death(void)
{
}

void CSkeleton_King_Death::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(11);
}

CMonsterState* CSkeleton_King_Death::Action()
{
	if(!m_bDeath)
	{
		m_pOwner->Death();
		m_bDeath = true;
	}

	if(m_pAnimController->GetTrackPos() > 6.183 && !m_bDeathEffect)
	{
		CDestory_BombFlashEfect* pFlashEffect = new CDestory_BombFlashEfect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, true, _T("SkeletonKing_EctoplasmBase"));
		m_pOwner->GetLayer()->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vPos.y += 150.f;
		pFlashEffect->Initialize();
		
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		m_pOwner->Destroy();

	return NULL;
}
