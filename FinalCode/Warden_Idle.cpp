#include "StdAfx.h"
#include "Warden_Idle.h"

CWarden_Idle::CWarden_Idle(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_WARDEN_IDLE;

	// Mode
	m_iMode = _iMode;

	// Worry
	m_fWorryTime = 0.0f;

	// Fetter
	m_fFetterTime = 0.0f;

	// Hover
	m_fHoverTime = 0.0f;

	// Hover
	// 배회와 관련된 변수. 0 : 대기,  1 : 배회, 2 : 고민
	m_iHover = -1;

	// Effect
	m_bEffect = false;
}

CWarden_Idle::~CWarden_Idle(void)
{
}

void CWarden_Idle::Initialize()
{
	CMonsterState::Initialize();
	m_pOwner->SetAnimation(0);
}

CMonsterState* CWarden_Idle::Action()
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

CMonsterState* CWarden_Idle::Mode0()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	//전투모드
	if(D3DXVec3Length(&(pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos)) < 500.0f)
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

					return new CWarden_Run(1);
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
						return new CWarden_Run(0);

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

CMonsterState* CWarden_Idle::Mode1()
{
	m_fWorryTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fWorryTime > 0.2f)
		return new CWarden_Attack1;

	return NULL;
}

CMonsterState* CWarden_Idle::Mode2()
{
	// 속박 이펙트 생성 후 Run으로 전환.

	if(!m_bEffect)
	{
		CWarden_EntangleDummy* pDummyEffect = new CWarden_EntangleDummy(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);
		pDummyEffect->Initialize();

		CSoundMgr::GetInstance()->PlaySoundForMonsterSkill(_T("Warden_Entangle.ogg"));

		//for(int i = 0; i < 25; ++i)
		//{
		//	CObject* pPlayer = NULL;
		//	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
		//	if(pPlayer == NULL)
		//		return NULL;

		//	// PlayerTransformCom
		//	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

		//	int iRand = rand() % 400 + 200;
		//	D3DXVECTOR3 vDir(0.f, 0.f, 1.f);
		//	D3DXMATRIX matRotY;
		//	D3DXMatrixRotationY(&matRotY, D3DXToRadian((360 / 25) * i));
		//	D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);

		//	D3DXVECTOR3 vPos = pPlayerTransformCom->m_vPos + vDir * 50.f;

		//	CWarden_Entangle* pEntangleEffect = new CWarden_Entangle(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &D3DXVECTOR3(0.f, 0.f, 0.f));
		//	m_pOwner->GetLayer()->AddObject(pEntangleEffect, LAYER_TYPE_EFFECT);

		//	CTransformCom* pTransformCom = (CTransformCom*)pEntangleEffect->GetComponent(COM_TYPE_TRANSFORM);
		//	pTransformCom->m_vPos = vPos;
		//	pTransformCom->m_vPos.y += iRand / 2.f;
		//	pTransformCom->m_vSize.x = 20.f;
		//	pTransformCom->m_vSize.y = (float)iRand;
		//	pTransformCom->m_vAngle.y = D3DXToRadian((360 / 25) * i);
		//	pEntangleEffect->Initialize();
		//}
		m_bEffect = true;
	}


	m_fFetterTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fFetterTime > 1.f)
		return new CWarden_Run(1);

	return NULL;
}
