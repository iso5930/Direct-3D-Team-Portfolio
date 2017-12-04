#include "StdAfx.h"
#include "Zombie_Female_Death.h"

CZombie_Female_Death::CZombie_Female_Death()
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_FEMALE_DEATH;

	// Death
	m_bDeath = false;
}

CZombie_Female_Death::~CZombie_Female_Death()
{
}

void CZombie_Female_Death::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(7);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Female_Death.ogg"));
}

CMonsterState* CZombie_Female_Death::Action()
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