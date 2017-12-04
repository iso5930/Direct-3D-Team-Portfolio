#include "StdAfx.h"
#include "Tristram_Mystic_Walk.h"

CTristram_Mystic_Walk::CTristram_Mystic_Walk()
{
	// StateType
	m_eStateType = STATE_TYPE_TRISTRAM_MYSTIC_WALK;

	// Time
	m_fTime = 0.0f;
}

CTristram_Mystic_Walk::~CTristram_Mystic_Walk()
{
}

void CTristram_Mystic_Walk::Initialize()
{
	// Initialize
	CNPCState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);
}

CNPCState* CTristram_Mystic_Walk::Action()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 10.0f)
		m_pOwner->Destroy();

	CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos -= pTransformCom->m_vAxisZ * 100.0f * CTimeMgr::GetInstance()->GetDeltaTime();

	return NULL;
}