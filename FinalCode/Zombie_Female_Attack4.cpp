#include "StdAfx.h"
#include "Zombie_Female_Attack4.h"

CZombie_Female_Attack4::CZombie_Female_Attack4()
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_FEMALE_ATTACK4;

	// Effect
	m_bEffect = false;
}

CZombie_Female_Attack4::~CZombie_Female_Attack4()
{
}

void CZombie_Female_Attack4::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Female_Attack4.ogg"));
}

CMonsterState* CZombie_Female_Attack4::Action()
{
	if(!m_bEffect && m_pAnimController->GetTrackPos() > 0.165)
	{
		D3DXVECTOR3 vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
		memcpy(&vLook, &m_pTransformCom->m_mWorld.m[2][0], sizeof(D3DXVECTOR3));
		vLook.y = 0.f;
		D3DXVec3Normalize(&vLook, &vLook);

		CZombieFemale_Spit* pSpit = new CZombieFemale_Spit(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(-vLook * 400));
		m_pOwner->GetLayer()->AddObject(pSpit, LAYER_TYPE_EFFECT);
		
		CTransformCom* pTransformCom = (CTransformCom*)pSpit->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CZombie_Female*)m_pOwner)->m_JawBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

		pSpit->Initialize();
		m_bEffect = true;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Female_Walk(1);

	return NULL;
}