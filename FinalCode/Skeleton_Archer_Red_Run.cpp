#include "StdAfx.h"
#include "Skeleton_Archer_Red_Run.h"

CSkeleton_Archer_Red_Run::CSkeleton_Archer_Red_Run(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ARCHER_RED_RUN;

	// Mode
	m_iMode = _iMode;

	// Time
	m_fTime = 0.0f;
	m_fEscapeTime = 0.0f;
	m_fChaseTime = 0.0f;
}

CSkeleton_Archer_Red_Run::~CSkeleton_Archer_Red_Run(void)
{
}

void CSkeleton_Archer_Red_Run::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	// Speed
	m_pPathFindCom->m_fSpeed = 100.0f;

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	//if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) >= 80.0f)
		m_pPathFindCom->Enable();
}

CMonsterState* CSkeleton_Archer_Red_Run::Action()
{	
	switch(m_iMode)
	{
	case 0:
		return Mode0();
	case 1:
		return Mode1();
	case 2:
		return Mode2();
	}

	return NULL;
}	

CMonsterState* CSkeleton_Archer_Red_Run::Mode0()
{
	//전투
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f)
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

		return new CSkeleton_Archer_Red_Attack(0);
	}

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f)
	{
		// Time
		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

		if(m_fTime > 1.0f)
		{
			if(m_pPathFindCom->Clear())
				return new CSkeleton_Archer_Red_Idle(0);
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

CMonsterState* CSkeleton_Archer_Red_Run::Mode1()
{
	m_fEscapeTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEscapeTime > 1.f)
	{
		m_vEscapePos = m_pTransformCom->m_vPos;
		m_fEscapeTime = 0.0f;
	}

	// 전투
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR3 vDir = m_pTransformCom->m_vPos - pPlayerTransformCom->m_vPos;
	vDir.y = 0;
	D3DXVec3Normalize(&vDir, &vDir);

	D3DXVECTOR3 vMovePos = m_pTransformCom->m_vPos + (vDir * m_pPathFindCom->m_fSpeed);

	CNaviCell* pNextCell;
	CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vMovePos, &pNextCell);

	D3DXVECTOR3 vPlayerLookDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;
	D3DXVECTOR3 vMoveDir = vMovePos - m_pTransformCom->m_vPos;

	vPlayerLookDir.y = 0.f;
	vMoveDir.y = 0.f;

	D3DXVec3Normalize(&vPlayerLookDir, &vPlayerLookDir);
	D3DXVec3Normalize(&vMoveDir, &vMoveDir);

	float fDot = D3DXVec3Dot(&vPlayerLookDir, &vMoveDir);

	if(fDot > 0)
		return new CSkeleton_Archer_Red_Attack(1);

	// Move
	m_pPathFindCom->Move(&vMovePos);
	
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

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 299)
		return new CSkeleton_Archer_Red_Idle(0);

	else if((int)m_pTransformCom->m_vPos.x == (int)m_vEscapePos.x && (int)m_pTransformCom->m_vPos.z == (int)m_vEscapePos.z)
		return new CSkeleton_Archer_Red_Idle(0);


	return NULL;
}

CMonsterState* CSkeleton_Archer_Red_Run::Mode2()
{
	//전투
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f)
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

		return new CSkeleton_Archer_Red_Attack(0);
	}

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f)
		m_fChaseTime += CTimeMgr::GetInstance()->GetDeltaTime();
	else
		m_fChaseTime = 0.0f;

	if(m_fChaseTime > 5.f)
		return new CSkeleton_Archer_Red_Idle(0);

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
