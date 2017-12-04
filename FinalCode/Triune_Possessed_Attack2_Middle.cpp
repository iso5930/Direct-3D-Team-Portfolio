#include "StdAfx.h"
#include "Triune_Possessed_Attack2_Middle.h"

CTriune_Possessed_Attack2_Middle::CTriune_Possessed_Attack2_Middle(void)
{
	// SetType
	m_eStateType = STATE_TYPE_TRIUNE_POSSESSED_ATTACK2_MIDDLE;
	m_fPlayerSearchTime = 0.0f;
}

CTriune_Possessed_Attack2_Middle::~CTriune_Possessed_Attack2_Middle(void)
{
}

void CTriune_Possessed_Attack2_Middle::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

	// Speed
	m_pPathFindCom->m_fSpeed = 900.f;

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

CMonsterState* CTriune_Possessed_Attack2_Middle::Action()
{
	m_fPlayerSearchTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fPlayerSearchTime > 3.f)
		return new CTriune_Possessed_Idle(0);

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 100.0f)
	{
		// Dir
		D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;

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
		return new CTriune_Possessed_Attack2_End;
	}
	return NULL;
}
