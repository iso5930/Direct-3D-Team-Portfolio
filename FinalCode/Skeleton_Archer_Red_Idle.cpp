#include "StdAfx.h"
#include "Skeleton_Archer_Red_Idle.h"

CSkeleton_Archer_Red_Idle::CSkeleton_Archer_Red_Idle(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_ARCHER_RED_IDLE;

	// Mode
	m_iMode = _iMode;

	// Time
	m_fHoverTime = 0.0f;
	m_fWorryTime = 0.0f;

	// Hover
	// 배회와 관련된 변수. 0 : 대기,  1 : 배회, 2 : 고민
	m_iHover = -1;
}

CSkeleton_Archer_Red_Idle::~CSkeleton_Archer_Red_Idle(void)
{
}

void CSkeleton_Archer_Red_Idle::Initialize()
{
	CMonsterState::Initialize();
	m_pOwner->SetAnimation(0);
}

CMonsterState* CSkeleton_Archer_Red_Idle::Action()
{
	switch(m_iMode)
	{
	case 0:
		return Mode0();
	case 1:
		return Mode1();
	}
	return NULL;
}

CMonsterState* CSkeleton_Archer_Red_Idle::Mode0()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	//전투모드
	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 400.0f)
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

					//공격
					return new CSkeleton_Archer_Red_Run(0);
					//return new CGhoul_Run(1);
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
				int iRand2 = rand() % 600 - 300;
				int iRand3 = rand() % 600 - 300;

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
						return new CSkeleton_Archer_Red_Walk;

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

CMonsterState* CSkeleton_Archer_Red_Idle::Mode1()
{
	m_fWorryTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fWorryTime > 1.f)
		return new CSkeleton_Archer_Red_Attack(0);
	
	return NULL;
}
