#include "StdAfx.h"
#include "Triune_Vessel_Activation.h"

CTriune_Vessel_Activation::CTriune_Vessel_Activation(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_VESSEL_ACTIVATION;
}

CTriune_Vessel_Activation::~CTriune_Vessel_Activation(void)
{
}

void CTriune_Vessel_Activation::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Vessel_Activation.ogg"));
}

CMonsterState* CTriune_Vessel_Activation::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		CTransformCom* pTransformCom;
		CTriune_Possessed* pMonster0 = new CTriune_Possessed(NULL, OBJ_TYPE_DYNAMIC, m_pOwner->GetStat()->iLevel);
		m_pOwner->GetLayer()->AddObject(pMonster0, LAYER_TYPE_MONSTER);
		pTransformCom = (CTransformCom*)pMonster0->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pMonster0->Initialize();
		pMonster0->SetState(new CTriune_Possessed_Activation);

		m_pOwner->Destroy();
	}

	return NULL;
}

