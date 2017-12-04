#include "StdAfx.h"
#include "Skeleton_King_Summon.h"

CSkeleton_King_Summon::CSkeleton_King_Summon(int _iCount)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_SUMMON;

	// Count 
	m_iCount = _iCount;

	m_iEffect = 0;

	m_fEctoplasmTime = 0.0f;
}

CSkeleton_King_Summon::~CSkeleton_King_Summon(void)
{
}

void CSkeleton_King_Summon::Initialize()
{
	CMonsterState::Initialize();
	
	// SetAnimaiton
	m_pOwner->SetAnimation(6);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("King_SummonSound.ogg"));
}

CMonsterState* CSkeleton_King_Summon::Action()
{
	m_fEctoplasmTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEctoplasmTime > 0.05f)
	{
		CSkeletonKing_EctoplasmBase* pEctoplasm = new CSkeletonKing_EctoplasmBase(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pEctoplasm, LAYER_TYPE_EFFECT);
		
		CTransformCom* pTransformCom = (CTransformCom*)pEctoplasm->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_LeftHandBone.mWorld);
		pTransformCom->m_vSize = D3DXVECTOR3(50.f, 50.f, 50.f);

		pEctoplasm->Initialize();

		m_fEctoplasmTime = 0.0f;
	}

	if(m_iEffect == 0 && m_pAnimController->GetTrackPos() > 1.155f)
	{
		CSkeletonKing_SummonShell* pSummonShell = new CSkeletonKing_SummonShell(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pSummonShell, LAYER_TYPE_EFFECT);
		pSummonShell->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)pSummonShell->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_LeftHandBone.mWorld);
		//pTransformCom->m_vPos = m_pTransformCom->m_vPos;

		m_iEffect = 1;
	}

	if(m_iEffect == 1 && m_pAnimController->GetTrackPos() > 3.0f)
	{
		
		//int iStartRandX = rand() % 600 - 300;
		//int iStartRandY = rand() % 200;
		//int iStartRandZ = rand() % 600 - 300;

		//D3DXVECTOR3 vStartPos = m_pTransformCom->m_vPos;
		//vStartPos.x += (float)iStartRandX;
		//vStartPos.y += (float)iStartRandY;
		//vStartPos.z += (float)iStartRandZ;

		CObject* pPlayer = NULL;
		m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);

		// PlayerTransformCom
		CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);
		
		D3DXVECTOR3 vEndPos, vLook, vRight;
		memcpy(&vLook, &m_pTransformCom->m_mWorld.m[2][0], sizeof(D3DXVECTOR3));
		vLook.y = 0.f;
		D3DXVec3Normalize(&vLook, &vLook);
		
		memcpy(&vRight, &m_pTransformCom->m_mWorld.m[0][0], sizeof(D3DXVECTOR3));
		vRight.y = 0.f;
		D3DXVec3Normalize(&vRight, &vRight);
		
		vEndPos = pPlayerTransformCom->m_vPos + (vLook * 100.0f);
		
		CNaviCell* pNaviCell = CPathFindMgr::GetInstance()->FindCell(&vEndPos);
		CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vEndPos, &pNaviCell);

		//pPlayerTransformCom->m_vPos +
		CSkeletonKing_SummonDummy* pSummonDummyEffect = new CSkeletonKing_SummonDummy(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vEndPos);
		m_pOwner->GetLayer()->AddObject(pSummonDummyEffect, LAYER_TYPE_EFFECT);
		pSummonDummyEffect->Initialize();

		vEndPos = pPlayerTransformCom->m_vPos - (vLook * 100.0f);

		pNaviCell = CPathFindMgr::GetInstance()->FindCell(&vEndPos);
		CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vEndPos, &pNaviCell);

		pSummonDummyEffect = new CSkeletonKing_SummonDummy(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vEndPos);
		m_pOwner->GetLayer()->AddObject(pSummonDummyEffect, LAYER_TYPE_EFFECT);
		pSummonDummyEffect->Initialize();

		vEndPos = pPlayerTransformCom->m_vPos + (vRight * 100.0f);

		pNaviCell = CPathFindMgr::GetInstance()->FindCell(&vEndPos);
		CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vEndPos, &pNaviCell);

		pSummonDummyEffect = new CSkeletonKing_SummonDummy(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vEndPos);
		m_pOwner->GetLayer()->AddObject(pSummonDummyEffect, LAYER_TYPE_EFFECT);
		pSummonDummyEffect->Initialize();

		vEndPos = pPlayerTransformCom->m_vPos - (vRight * 100.0f);

		pNaviCell = CPathFindMgr::GetInstance()->FindCell(&vEndPos);
		CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vEndPos, &pNaviCell);

		pSummonDummyEffect = new CSkeletonKing_SummonDummy(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vEndPos);
		m_pOwner->GetLayer()->AddObject(pSummonDummyEffect, LAYER_TYPE_EFFECT);
		pSummonDummyEffect->Initialize();

		m_iEffect = 2;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		if(m_iCount == 0)
		{
			CSkeletonKing_TeleportShell* pTeleportShell = new CSkeletonKing_TeleportShell(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
			m_pOwner->GetLayer()->AddObject(pTeleportShell, LAYER_TYPE_EFFECT);
			pTeleportShell->Initialize();

			CTransformCom* pTransformCom = (CTransformCom*)pTeleportShell->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vPos = m_pTransformCom->m_vPos;

			return new CSkeleton_King_Teleport_Back;
		}

		if(m_iCount == 1)
			return new CSkeleton_King_Taunt;
	}

	// 이펙트 추가할 것.

	return NULL;
}
