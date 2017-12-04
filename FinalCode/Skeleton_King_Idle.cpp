#include "StdAfx.h"
#include "Skeleton_King_Idle.h"

CSkeleton_King_Idle::CSkeleton_King_Idle(int _iMode)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_IDLE;

	// Mode
	m_iMode = _iMode;
	
	// Time
	m_fActSelectTime = 0.0f;
	m_fWaitTime = 0.0f;
}

CSkeleton_King_Idle::~CSkeleton_King_Idle(void)
{
}

void CSkeleton_King_Idle::Initialize()
{
	CMonsterState::Initialize();
	m_pOwner->SetAnimation(0);
}

CMonsterState* CSkeleton_King_Idle::Action()
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

CMonsterState* CSkeleton_King_Idle::Mode0()
{
	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return NULL;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	// 걸어서 접근 가능 거리일 때
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

					return new CSkeleton_King_Walk;
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
	else
	{
		m_fActSelectTime += CTimeMgr::GetInstance()->GetDeltaTime();

		if(m_fActSelectTime > 2.f)
		{
			int iRand = rand() % 4;
			switch(iRand)
			{
			case 0:
				return new CSkeleton_King_Teleport;
			case 1:
				return new CSkeleton_King_Summon(0);
			case 2:
				return new CSkeleton_King_Teleport;
			case 3:
				return new CSkeleton_King_Teleport;
			}
		}
	}
	return NULL;
}

CMonsterState* CSkeleton_King_Idle::Mode1()
{
	m_fWaitTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fWaitTime > 1.f)
	{
		int iRand = rand() % 2;
		
		switch(iRand)
		{
		case 0:
			return new CSkeleton_King_Attack1;
		case 1:
			return new CSkeleton_King_Whirlwind_Start;
		}
	}

	return NULL;
}
