#include "StdAfx.h"
#include "Skeleton_OneHand_Mint_Run.h"

CSkeleton_OneHand_Mint_Run::CSkeleton_OneHand_Mint_Run(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ONEHAND_MINT_RUN;

	// Mode
	m_iMode = _iMode;

	// Time
	m_fTime = 0.0f;
	m_fChaseTime = 0.0f;
}

CSkeleton_OneHand_Mint_Run::~CSkeleton_OneHand_Mint_Run(void)
{
}

void CSkeleton_OneHand_Mint_Run::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) >= 80.0f)
		m_pPathFindCom->Enable();
}

CMonsterState* CSkeleton_OneHand_Mint_Run::Action()
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

CMonsterState* CSkeleton_OneHand_Mint_Run::Mode0()
{
	//������

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 350.0f)
	{	
		return new CSkeleton_OneHand_Mint_Run(1);
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
		return new CSkeleton_OneHand_Mint_Idle;

	return NULL;
}

CMonsterState* CSkeleton_OneHand_Mint_Run::Mode1()
{
	//����
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 80.0f)
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

		return new CSkeleton_OneHand_Mint_Attack;
	}

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f)
	{
		// Time
		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

		if(m_fTime > 1.0f)
		{
			if(m_pPathFindCom->Clear())
				return new CSkeleton_OneHand_Mint_Idle;
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

CMonsterState* CSkeleton_OneHand_Mint_Run::Mode2()
{
	//����
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 80.0f)
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

		return new CSkeleton_OneHand_Mint_Attack;
	}

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 350.0f)
		m_fChaseTime += CTimeMgr::GetInstance()->GetDeltaTime();
	else
		m_fChaseTime = 0.0f;

	if(m_fChaseTime > 5.f)
		return new CSkeleton_OneHand_Mint_Idle;

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