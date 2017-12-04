#include "StdAfx.h"
#include "Warden_Attack2.h"

CWarden_Attack2::CWarden_Attack2(void)
{
	// SetType
	m_eStateType = STATE_TYPE_WARDEN_ATTACK2;

	// Effect
	m_bEffect = false;
}

CWarden_Attack2::~CWarden_Attack2(void)
{
}

void CWarden_Attack2::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);
}

CMonsterState* CWarden_Attack2::Action()
{
	//이펙트 생성할 것.
	if(!m_bEffect && m_pAnimController->GetTrackPos() > 0.429f)
	{
		D3DXVECTOR3 vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
		memcpy(&vLook, &m_pTransformCom->m_mWorld.m[2][0], sizeof(D3DXVECTOR3));
		vLook.y= 0.f;
		D3DXVec3Normalize(&vLook, &vLook);

		D3DXVECTOR3 vRight = D3DXVECTOR3(0.f, 0.f, 0.f);
		memcpy(&vRight, &m_pTransformCom->m_mWorld.m[0][0], sizeof(D3DXVECTOR3));
		D3DXVec3Normalize(&vRight, &vRight);

		D3DXVECTOR3 vLeftUpLook, vRightUpLook;
		vLeftUpLook = vLook + -vRight;
		vRightUpLook = vLook + vRight;
		//vLeftUpLook = vLook;
		//vLeftUpLook.z -= D3DXToRadian(30.f);
		//vRightUpLook = vLook;
		//vRightUpLook.z += D3DXToRadian(30.f);

		// Look
		CWarden_FireEffect* pFireEffect = new CWarden_FireEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(-vLook * 400.f));
		m_pOwner->GetLayer()->AddObject(pFireEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pFireEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pFireEffect->Initialize();

		// LeftUpLook
		pFireEffect = new CWarden_FireEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(-vLeftUpLook * 400.f));
		m_pOwner->GetLayer()->AddObject(pFireEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pFireEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pTransformCom->m_vAngle.z += D3DXToRadian(45.f);
		pFireEffect->Initialize();

		// RightUpLook
		pFireEffect = new CWarden_FireEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(-vRightUpLook * 400.f));
		m_pOwner->GetLayer()->AddObject(pFireEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pFireEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pTransformCom->m_vAngle.z -= D3DXToRadian(45.f);
		pFireEffect->Initialize();

		m_bEffect = true;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CWarden_Run(1);

	return NULL;
}
