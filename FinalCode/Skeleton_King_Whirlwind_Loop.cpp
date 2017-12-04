#include "StdAfx.h"
#include "Skeleton_King_Whirlwind_Loop.h"

CSkeleton_King_Whirlwind_Loop::CSkeleton_King_Whirlwind_Loop(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_WHIRLWIND_LOOP;
	
	// Mode
	m_iMode = 0;
	
	// Time
	m_fTime = 0.0f;

	// Effect
	m_iEffect = 0;
}

CSkeleton_King_Whirlwind_Loop::~CSkeleton_King_Whirlwind_Loop(void)
{
}

void CSkeleton_King_Whirlwind_Loop::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) >= 100.0f)
		m_pPathFindCom->Enable();
}

CMonsterState* CSkeleton_King_Whirlwind_Loop::Action()
{
	if(m_iEffect == 0)
	{
		//CSkeletonKing_CenterTrail* pCenterTrail = new CSkeletonKing_CenterTrail(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		//m_pOwner->GetLayer()->AddObject(pCenterTrail, LAYER_TYPE_EFFECT);

		//CTransformCom* pTransformCom = (CTransformCom*)pCenterTrail->GetComponent(COM_TYPE_TRANSFORM);
		//D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_CenterBone.mWorld);
		//pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		//pCenterTrail->Initialize();

		//pCenterTrail = new CSkeletonKing_CenterTrail(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		//m_pOwner->GetLayer()->AddObject(pCenterTrail, LAYER_TYPE_EFFECT);

		//pTransformCom = (CTransformCom*)pCenterTrail->GetComponent(COM_TYPE_TRANSFORM);
		//D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_CenterBone.mWorld);
		//pTransformCom->m_vAngle = -m_pTransformCom->m_vAngle;
		//pCenterTrail->Initialize();
		m_iEffect = 1;
	}

	if(m_iEffect == 1 && m_pAnimController->GetTrackPos() > 0.654f)
	{
		CSkeletonKing_WeaponTrail* pWeaponTrail = new CSkeletonKing_WeaponTrail(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pWeaponTrail, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pWeaponTrail->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_CenterTopBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pWeaponTrail->Initialize();
		m_iEffect = 2;
	}

	if(m_iEffect == 2 && m_pAnimController->GetTrackPos() > 1.515f)
	{
		CSkeletonKing_WeaponTrail* pWeaponTrail = new CSkeletonKing_WeaponTrail(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pWeaponTrail, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pWeaponTrail->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_CenterTopBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pWeaponTrail->Initialize();
		m_iEffect = 3;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_King_Whirlwind_End;

	switch(m_iMode)
	{
	case 0:
		return Mode0();
	case 1:
		return Mode1();
	case 2:
		return Mode2();
	case 3:
		return Mode3();
	}

	return NULL;
}

CMonsterState* CSkeleton_King_Whirlwind_Loop::Mode0()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

	vDir.y = 0.0f;
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vMovePos = m_pTransformCom->m_vPos + (vDir * 80);

	m_pPathFindCom->Move(&vMovePos);

	vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

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

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.0f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}

CMonsterState* CSkeleton_King_Whirlwind_Loop::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.9f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}

CMonsterState* CSkeleton_King_Whirlwind_Loop::Mode2()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

	vDir.y = 0.0f;
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vMovePos = m_pTransformCom->m_vPos + (vDir * 80);

	m_pPathFindCom->Move(&vMovePos);

	vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

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

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.0f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}

CMonsterState* CSkeleton_King_Whirlwind_Loop::Mode3()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.7f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}
