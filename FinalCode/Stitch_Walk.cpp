#include "StdAfx.h"
#include "Stitch_Walk.h"

CStitch_Walk::CStitch_Walk(void)
{
	// StateType
	m_eStateType = STATE_TYPE_STITCH_WALK;
}

CStitch_Walk::~CStitch_Walk(void)
{
}

void CStitch_Walk::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	// Speed
	m_pPathFindCom->m_fSpeed = 100.0f;

	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	//if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) >= 60.0f)
	m_pPathFindCom->Enable();
}
CMonsterState* CStitch_Walk::Action()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 400.0f)
	{	
		return new CStitch_Run(0);
	}

	// NextPos
	D3DXVECTOR3 vNextPos;
	if(m_pPathFindCom->IsMove(&vNextPos) != false)
	{
		// Dir
		D3DXVECTOR3 vDir = vNextPos - m_pTransformCom->m_vPos;
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

			if(Equals(fDotZ, 1.0f, MAX_EPSILON))
			{
				if(fDotX > 0.0f)
					m_pTransformCom->m_vAngle.y += acosf(fDotZ);
				else
					m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
			}
			else
			{
				if(fDotX > 0.0f)
					m_pTransformCom->m_vAngle.y += 20.0f * CTimeMgr::GetInstance()->GetDeltaTime();
				else
					m_pTransformCom->m_vAngle.y -= 20.0f * CTimeMgr::GetInstance()->GetDeltaTime();
			}
		}	
	}
	else
		return new CStitch_Idle;

	return NULL;
}
