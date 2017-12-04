#include "StdAfx.h"
#include "Skeleton_King_Teleport_Attack.h"

CSkeleton_King_Teleport_Attack::CSkeleton_King_Teleport_Attack(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_TELEPORT_ATTACK;

	// Mode
	m_iMode = 0;
	
	// Time
	m_fTime = 0.0f;

	// Effect
	m_bEffect = false;

	m_fEctoplasmTime = 0.0f;
}

CSkeleton_King_Teleport_Attack::~CSkeleton_King_Teleport_Attack(void)
{
}

void CSkeleton_King_Teleport_Attack::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(8);

	// 렌더 시키는 방법에 대한 문제.
	// 플레이어 위치와 방향 설정. 일단 없이 하고 네비메쉬가 없는 길이면 재설정해준다.

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);
	
	D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;
	D3DXVec3Normalize(&vDir, &vDir);
	

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

	D3DXVECTOR3 vMovePos = pPlayerTransformCom->m_vPos - (vDir * 100.0f);

	CNaviCell* pNextCell;
	CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vMovePos, &pNextCell);

	m_pTransformCom->m_vPos = vMovePos;//pPlayerTransformCom->m_vPos;// + (vDir * (100.0f - fDist));

	m_pPathFindCom->m_pCell = pNextCell;
}

CMonsterState* CSkeleton_King_Teleport_Attack::Action()
{
	m_fEctoplasmTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEctoplasmTime > 0.05f && m_pAnimController->GetTrackPos() < 1.0f)
	{
		int iRandY = rand() % 25;
		int iRandX = rand() % 50 - 25;
		int iRandZ = rand() % 50 - 25;

		CSkeletonKing_EctoplasmBase* pEctoplasm = new CSkeletonKing_EctoplasmBase(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pEctoplasm, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pEctoplasm->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_LeftHandBone.mWorld);
		pTransformCom->m_vSize = D3DXVECTOR3(100.f, 100.f, 100.f);
		pTransformCom->m_vPos.x += (float)iRandX;
		pTransformCom->m_vPos.y += (float)iRandY;
		pTransformCom->m_vPos.z += (float)iRandZ;

		pEctoplasm->Initialize();

		m_fEctoplasmTime = 0.0f;
	}

	if(!m_bEffect && m_pAnimController->GetTrackPos() > 0.643f)
	{
		CSkeletonKing_WeaponTrail* pWeaponTrail = new CSkeletonKing_WeaponTrail(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pWeaponTrail, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pWeaponTrail->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_CenterTopBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pWeaponTrail->Initialize();

		m_bEffect = true;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_King_Idle(0);

	switch(m_iMode)
	{
	case 0:
		return Mode0();
	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CSkeleton_King_Teleport_Attack::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.0f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}

CMonsterState* CSkeleton_King_Teleport_Attack::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}
