#include "StdAfx.h"
#include "Triune_Possessed_Idle.h"

CTriune_Possessed_Idle::CTriune_Possessed_Idle(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_TRIUNE_POSSESSED_IDLE;

	// Mode
	m_iMode = _iMode;

	// Worry
	m_fWorryTime = 0.0f;

	// Time
	m_fHoverTime = 0.0f;

	// Hover
	// ��ȸ�� ���õ� ����. 0 : ���,  1 : ��ȸ, 2 : ���
	m_iHover = -1;
}

CTriune_Possessed_Idle::~CTriune_Possessed_Idle(void)
{

}

void CTriune_Possessed_Idle::Initialize()
{
	CMonsterState::Initialize();
	m_pOwner->SetAnimation(0);
}

CMonsterState* CTriune_Possessed_Idle::Action()
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

CMonsterState* CTriune_Possessed_Idle::Mode0()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	//�������
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

					return new CTriune_Possessed_Walk(1);
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
	else //������
	{
		m_fHoverTime += CTimeMgr::GetInstance()->GetDeltaTime();

		if(m_fHoverTime > 5.94)
		{
			//��ȸ

			if(m_iHover == -1)
				m_iHover = rand() % 2;

			//��ȸ���� �ʴ´�.
			if(m_iHover == 0)
			{
				m_fHoverTime = 0.f;
				m_iHover = -1;
			}

			//��ȸ�Ѵ�.
			if(m_iHover == 1)//m_bHover)
			{
				//������ ��ǥ
				int iRand2 = rand() % 400 - 200;
				int iRand3 = rand() % 400 - 200;

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
						return new CTriune_Possessed_Walk(0);

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

CMonsterState* CTriune_Possessed_Idle::Mode1()
{
	m_fWorryTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fWorryTime > 0.2f)
		return new CTriune_Possessed_Attack1;

	return NULL;
}
