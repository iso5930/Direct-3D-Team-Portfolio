#include "StdAfx.h"
#include "Butcher_Walk.h"

CButcher_Walk::CButcher_Walk(void)
{
	// StateType
	m_eStateType = STATE_TYPE_BUTCHER_WALK;
	
	// Time
	m_fActSelectTime = 0.0f;
}

CButcher_Walk::~CButcher_Walk(void)
{
}

void CButcher_Walk::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) >= 150.0f)
		m_pPathFindCom->Enable();
}

CMonsterState* CButcher_Walk::Action()
{
	m_fActSelectTime += CTimeMgr::GetInstance()->GetDeltaTime();

	//ÀüÅõ
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 150.0f)
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

		int iRand = rand() % 2;

		switch (iRand)
		{
		case 0:
			return new CButcher_Attack1;
		case 1:
			return new CButcher_Attack2;
		}
	}
	else if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 250.0f)
	{
		if(m_fActSelectTime > 1.65f)
		{
			int iRand = rand() % 5;
			
			switch(iRand)
			{
			case 0:
				return new CButcher_Walk;
			case 1:
				return new CButcher_Chain_In;
			case 2:
				return new CButcher_Charge_In;
			case 3:
				return new CButcher_Walk;
			case 4:
				return new CButcher_Walk;
			}
		}
	}

	// NextPos
	D3DXVECTOR3 vNextPos;
	if(m_pPathFindCom->IsMove(&vNextPos))
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

	return NULL;
}
