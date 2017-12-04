#include "StdAfx.h"
#include "Skeleton_Summoner_Brown_Summon.h"

CSkeleton_Summoner_Brown_Summon::CSkeleton_Summoner_Brown_Summon(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_SUMMONER_BROWN_SUMMON;

	// Effect
	m_pSummonEffect = NULL;
	m_bEffect = false;
}

CSkeleton_Summoner_Brown_Summon::~CSkeleton_Summoner_Brown_Summon(void)
{
}

void CSkeleton_Summoner_Brown_Summon::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Skeleton_Summoner_Summon.ogg"));
}

CMonsterState* CSkeleton_Summoner_Brown_Summon::Action()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(!m_bEffect && m_pAnimController->GetTrackPos() > 2.343f)
	{
		D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;
		vDir.y = 0.0f;
		D3DXVec3Normalize(&vDir, &vDir);

		D3DXVECTOR3 vReachPos = pPlayerTransformCom->m_vPos - (vDir * 100.0f);

		CNaviCell* pNaviCell = CPathFindMgr::GetInstance()->FindCell(&vReachPos);
		CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vReachPos, &pNaviCell);

		m_pSummonEffect = new CSkeletonSummoner_SummonEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vReachPos);
		m_pOwner->GetLayer()->AddObject(m_pSummonEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)m_pSummonEffect->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_Summoner_Brown*)m_pOwner)->m_RightHandBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

		m_pSummonEffect->Initialize();

		m_bEffect = true;
	}

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
			return new CSkeleton_Summoner_Brown_Idle(1);
	}
	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 150.0f)
	{
		if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		{
			return new CSkeleton_Summoner_Brown_Walk(2);
		}
	}
	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f
		&& m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_Summoner_Brown_Idle(0);

	return NULL;
}
