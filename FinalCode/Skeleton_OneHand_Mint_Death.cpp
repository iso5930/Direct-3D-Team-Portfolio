#include "StdAfx.h"
#include "Skeleton_OneHand_Mint_Death.h"

CSkeleton_OneHand_Mint_Death::CSkeleton_OneHand_Mint_Death(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ONEHAND_MINT_DEATH;

	// Death
	m_bDeath = false;
}

CSkeleton_OneHand_Mint_Death::~CSkeleton_OneHand_Mint_Death(void)
{
}

void CSkeleton_OneHand_Mint_Death::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Skeleton_Death.ogg"));
}

CMonsterState* CSkeleton_OneHand_Mint_Death::Action()
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