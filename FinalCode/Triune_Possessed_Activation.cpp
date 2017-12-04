#include "StdAfx.h"
#include "Triune_Possessed_Activation.h"

CTriune_Possessed_Activation::CTriune_Possessed_Activation(void)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_POSSESSED_ACTIVATION;

	// Effect
	m_bEffect = false;

	// Invisible
	m_fInvisibleTime = 0.f;
	m_bInvisibleCheck = false;
}

CTriune_Possessed_Activation::~CTriune_Possessed_Activation(void)
{
}

void CTriune_Possessed_Activation::Initialize()
{
	CMonsterState::Initialize();

	m_pOwner->SetAnimationMode(2);
	// SetAnimation
	m_pOwner->SetAnimation(2);
}

CMonsterState* CTriune_Possessed_Activation::Action()
{
	if(!m_bEffect)
	{
		m_pOwner->RemoveComponent(COM_TYPE_RENDER);

		CVessel_TransformEffect* pTransformEffect = new CVessel_TransformEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 0);
		m_pOwner->GetLayer()->AddObject(pTransformEffect, LAYER_TYPE_EFFECT);
		
		CTransformCom* pTransformCom = (CTransformCom*)pTransformEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vPos.y += 50.f;
		pTransformCom->m_vSize = D3DXVECTOR3(200.f, 200.f, 200.f);

		pTransformEffect->Initialize();

		pTransformEffect = new CVessel_TransformEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 1);
		m_pOwner->GetLayer()->AddObject(pTransformEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pTransformEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vPos.y += 60.f;
		pTransformCom->m_vPos.x += 50.f;
		pTransformCom->m_vSize = D3DXVECTOR3(150.f, 150.f, 150.f);

		pTransformEffect->Initialize();

		pTransformEffect = new CVessel_TransformEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 2);
		m_pOwner->GetLayer()->AddObject(pTransformEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pTransformEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vPos.y += 70.f;
		pTransformCom->m_vPos.z += 50.f;
		pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 50.f);

		pTransformCom->Initialize();

		pTransformEffect = new CVessel_TransformEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 3);
		m_pOwner->GetLayer()->AddObject(pTransformEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pTransformEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vPos.y += 40.f;
		pTransformCom->m_vPos.x -= 50.f;
		pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 100.f);

		pTransformCom->Initialize();

		m_bEffect = true;
		m_bInvisibleCheck = true;
	}

	if(m_bInvisibleCheck)
		m_fInvisibleTime += CTimeMgr::GetInstance()->GetDeltaTime();
	
	if(m_fInvisibleTime > 0.8f && m_bInvisibleCheck)
	{
		CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_MONSTER);
		m_pOwner->AddComponent(pRenderCom);
		m_pOwner->SetAnimationMode(0);
		m_bInvisibleCheck = false;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CTriune_Possessed_Idle(0);

	return NULL;
}