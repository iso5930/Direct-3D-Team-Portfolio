#include "StdAfx.h"
#include "Zombie_Female_Walk.h"

CZombie_Female_Walk::CZombie_Female_Walk(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_FEMALE_WALK;

	// Mode
	m_iMode = _iMode;

	// Time
	m_fTime = 0.0f;
	m_fVomitTime = 0.0f;
	m_fWaitTime = 0.0f;
	m_fChaseTime = 0.0f;

	m_bHover = false;

}

CZombie_Female_Walk::~CZombie_Female_Walk()
{

}

void CZombie_Female_Walk::Initialize()
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

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) >= 60.0f && m_iMode != 2)
		m_pPathFindCom->Enable();

	//if(/*D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) <= 60.0f && */m_iMode == 2)
	if(m_iMode == 2)
		m_pPathFindCom->Enable();
}

CMonsterState* CZombie_Female_Walk::Action()
{

	switch(m_iMode)
	{
	case 0 :
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

CMonsterState* CZombie_Female_Walk::Mode0()
{
	//������
	//m_pPathFindCom->m_fSpeed = 40.f;

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f)
	{	
		return new CZombie_Female_Walk(1);
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
	{
		return new CZombie_Female_Idle(0);
	}

	return NULL;
}

CMonsterState* CZombie_Female_Walk::Mode1()
{
	//����
	m_fVomitTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fWaitTime += CTimeMgr::GetInstance()->GetDeltaTime();

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	// Stop
	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 150.0f &&
		D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 100.0f &&
		m_fWaitTime > 2.f)
	{
		int iRand = rand() % 2;
		
		if(iRand == 0)
		{
			m_fWaitTime = 0.0f;
			return NULL;
		}

		if(iRand == 1)
		{
			m_fWaitTime = 0.0f;
			return new CZombie_Female_Idle(1);
		}
	}

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 60.0f)
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
		
		return new CZombie_Female_Idle(2);
	}

	//���ϴ� �κ� ���ñ���
	if(m_fVomitTime > 3.f)
	{
		int iRand = rand() % 2;
		switch (iRand)
		{
		case 0:
			m_fVomitTime = 0.0f;
			return new CZombie_Female_Attack4;
		case 1:
			m_fVomitTime = 0.0f;
			return new CZombie_Female_Attack3;
		}
	}

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f)
	{
		// Time
		m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();

		if(m_fTime > 1.0f)
		{
			if(m_pPathFindCom->Clear())
				return new CZombie_Female_Idle(0);
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

CMonsterState* CZombie_Female_Walk::Mode2()
{

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	if(!m_bHover)
	{
		D3DXVECTOR3 vDir = m_pTransformCom->m_vPos - pPlayerTransformCom->m_vPos;
		vDir.y = 0.f;
		D3DXVec3Normalize(&vDir, &vDir);

		D3DXMATRIX matRotY;
		
		int iRand = rand() % 180 - 90;

		D3DXMatrixRotationY(&matRotY, D3DXToRadian(iRand));

		D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

		D3DXVECTOR3 vMovePos = m_pTransformCom->m_vPos + (vDir * 100.f); 
		
		m_vHoverPos = vMovePos;

		m_bHover = true;
	}

	CNaviCell* pNaviCell = CPathFindMgr::GetInstance()->FindCell(&m_vHoverPos);
	CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &m_vHoverPos, &pNaviCell);

	m_pPathFindCom->Move(&m_vHoverPos);

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

	if((int)m_pTransformCom->m_vPos.x == (int)m_vHoverPos.x && (int)m_pTransformCom->m_vPos.z == (int)m_vHoverPos.z)
		return new CZombie_Female_Idle(1);

	
	

	return NULL;
}

CMonsterState* CZombie_Female_Walk::Mode3()
{
	//����
	m_fVomitTime += CTimeMgr::GetInstance()->GetDeltaTime();
	//m_fWaitTime += CTimeMgr::GetInstance()->GetDeltaTime();

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// Move
	m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 60.0f)
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

		return new CZombie_Female_Idle(2);
	}

	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) > 300.0f)
		m_fChaseTime += CTimeMgr::GetInstance()->GetDeltaTime();
	else
		m_fChaseTime = 0.0f;

	if(m_fChaseTime > 5.f)
		return new CZombie_Female_Idle(0);

	//���ϴ� �κ� ���ñ���
	if(m_fVomitTime > 3.f)
	{
		int iRand = rand() % 2;
		switch (iRand)
		{
		case 0:
			m_fVomitTime = 0.0f;
			return new CZombie_Female_Attack4;
		case 1:
			m_fVomitTime = 0.0f;
			return new CZombie_Female_Attack3;
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
