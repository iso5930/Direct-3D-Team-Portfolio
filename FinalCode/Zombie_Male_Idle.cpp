#include "StdAfx.h"
#include "Zombie_Male_Idle.h"

CZombie_Male_Idle::CZombie_Male_Idle(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_MALE_IDLE;

	// Time
	m_fHoverTime = 0.0f;
	m_fWaitTime = 0.0f;

	// Worry
	m_fWorryTime = 0.f;
	m_iWorryRand = 0;
	m_fWorryMaxTime = 0.0f;

	m_iMode = _iMode;

	m_bWorry = false;

	// Hover
	// 배회와 관련된 변수. 0 : 대기,  1 : 배회, 2 : 고민
	m_iHover = -1;
}

CZombie_Male_Idle::~CZombie_Male_Idle(void)
{
}

void CZombie_Male_Idle::Initialize()
{
	CMonsterState::Initialize();

	m_pOwner->SetAnimation(0);
	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Male_Idle.ogg"));

}

CMonsterState* CZombie_Male_Idle::Action()
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

CMonsterState* CZombie_Male_Idle::Mode0()
{
	

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	//전투모드
	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 300.0f)
	{
		// Move
		m_pPathFindCom->Move(&pPlayerTransformCom->m_vPos);


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

					return new CZombie_Male_Walk(1);
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

	}
	else //비전투
	{
		m_fHoverTime += CTimeMgr::GetInstance()->GetDeltaTime();

		if(m_fHoverTime > 5.94)
		{
			//배회

			if(m_iHover == -1)
				m_iHover = rand() % 2;

			//배회하지 않는다.
			if(m_iHover == 0)
			{
				m_fHoverTime = 0.f;
				m_iHover = -1;
			}

			//배회한다.
			if(m_iHover == 1)//m_bHover)
			{
				//임의의 좌표
				int iRand2 = rand() % 200 - 100;
				int iRand3 = rand() % 200 - 100;

				D3DXVECTOR3	vMovePos = m_pTransformCom->m_vPos;

				vMovePos.x += iRand2;
				vMovePos.z += iRand3;

				CNaviCell* pNaviCell = CPathFindMgr::GetInstance()->FindCell(&vMovePos);
				CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &vMovePos, &pNaviCell);

				m_pPathFindCom->Move(&vMovePos);
				m_iHover = 2;
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

						//Walk
						return new CZombie_Male_Walk(0);

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
		}
	}

	return NULL;
}

CMonsterState* CZombie_Male_Idle::Mode1()
{
	// WaitTime
	m_fWaitTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fWaitTime > 2.f)
		return new CZombie_Male_Idle(0);

	return NULL;
}

CMonsterState* CZombie_Male_Idle::Mode2()
{
	
	m_fWorryTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(!m_bWorry)
	{
		m_iWorryRand = rand() % 5;
		m_bWorry = true;

		switch(m_iWorryRand)
		{
		case 0:
			m_fWorryMaxTime = 0.2f;
			break;
		case 1:
			m_fWorryMaxTime = 0.4f;
			break;
		case 2:
			m_fWorryMaxTime = 0.6f;
			break;
		case 3:
			m_fWorryMaxTime = 0.8f;
			break;
		case 4:
			m_fWorryMaxTime = 1.0f;
			break;
		}
	}

	if(m_fWorryTime > m_fWorryMaxTime)
	{
		int iRand = rand() % 4;

		switch (iRand)
		{
		case 0:
			m_fWorryTime = 0.0f;
			m_bWorry = true;
			return new CZombie_Male_Attack;
		case 1:
			m_fWorryTime = 0.0f;
			m_bWorry = true;
			return new CZombie_Male_Attack;
		case 2:
			m_fWorryTime = 0.0f;
			m_bWorry = true;
			return new CZombie_Male_Attack;
		case 3:
			m_fWorryTime = 0.0f;
			m_bWorry = true;
			return new CZombie_Male_Walk(2);
		}
	}

	return NULL;
}