#include "StdAfx.h"
#include "Skeleton_Archer_Red_Attack.h"

CSkeleton_Archer_Red_Attack::CSkeleton_Archer_Red_Attack(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ARCHER_RED_ATTACK;

	// Mode
	m_iMode = _iMode;

	// Effect
	m_pArrowEffect = NULL;
	m_bEffect = false;
}

CSkeleton_Archer_Red_Attack::~CSkeleton_Archer_Red_Attack(void)
{
}

void CSkeleton_Archer_Red_Attack::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Skeleton_Archer_Attack.ogg"));
}

CMonsterState* CSkeleton_Archer_Red_Attack::Action()
{
	if(!m_bEffect && m_pAnimController->GetTrackPos() > 0.66f)
	{
		D3DXVECTOR3 vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
		memcpy(&vLook, &m_pTransformCom->m_mWorld.m[2][0], sizeof(D3DXVECTOR3));
		vLook.y = 0.f;
		D3DXVec3Normalize(&vLook, &vLook);

		m_pArrowEffect = new CSkeleton_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(-vLook * 1000.f));
		m_pOwner->GetLayer()->AddObject(m_pArrowEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)m_pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_Archer_Brown*)m_pOwner)->m_WeaponBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

		m_pArrowEffect->Initialize();
		CSoundMgr::GetInstance()->PlaySoundForMonsterSkill(_T("Skeleton_Archer_Arrow.ogg"));
		m_bEffect = true;
	}

	switch(m_iMode)
	{
	case 0:
		return Mode0();
	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CSkeleton_Archer_Red_Attack::Mode0()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f
		&& D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 200.0f)
	{

		// Dir
		D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

		if(m_pAnimController->GetTrackPos() < 0.45)
		{
			if(!Equals(vDir.x, 0.0f, MIN_EPSILON) || !Equals(vDir.z, 0.0f, MIN_EPSILON))
			{
				// Normalize
				vDir.y = 0.0f;
				D3DXVec3Normalize(&vDir, &vDir);

				// DotX
				float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
				fDotX = RevisionDot(fDotX);

				// DotZ
				float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
				fDotZ = RevisionDot(fDotZ);

				if(fDotX > 0.0f)
					m_pTransformCom->m_vAngle.y += acosf(fDotZ);
				else
					m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
			}
		}
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
			return new CSkeleton_Archer_Red_Idle(1);
	}
	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) <= 200.0f)
	{
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		{
			return new CSkeleton_Archer_Red_Run(1);
		}
	}
	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f
		&& m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Archer_Red_Idle(0);

	return NULL;
}

CMonsterState* CSkeleton_Archer_Red_Attack::Mode1()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f)
	{
		// Dir
		D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

		if(m_pAnimController->GetTrackPos() < 0.45)
		{
			if(!Equals(vDir.x, 0.0f, MIN_EPSILON) || !Equals(vDir.z, 0.0f, MIN_EPSILON))
			{
				// Normalize
				vDir.y = 0.0f;
				D3DXVec3Normalize(&vDir, &vDir);

				// DotX
				float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
				fDotX = RevisionDot(fDotX);

				// DotZ
				float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
				fDotZ = RevisionDot(fDotZ);

				if(fDotX > 0.0f)
					m_pTransformCom->m_vAngle.y += acosf(fDotZ);
				else
					m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
			}
		}
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
			return new CSkeleton_Archer_Red_Attack(1);
	}
	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f)
	{
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		{
			return new CSkeleton_Archer_Red_Idle(0);
		}
	}

	return NULL;
}
