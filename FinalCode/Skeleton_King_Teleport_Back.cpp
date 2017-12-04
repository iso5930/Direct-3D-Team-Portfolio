#include "StdAfx.h"
#include "Skeleton_King_Teleport_Back.h"

CSkeleton_King_Teleport_Back::CSkeleton_King_Teleport_Back(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_TELEPORT_BACK;

	// Pos
	m_vMovePos = D3DXVECTOR3(0.f, 0.f, 0.f);
}

CSkeleton_King_Teleport_Back::~CSkeleton_King_Teleport_Back(void)
{
}

void CSkeleton_King_Teleport_Back::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(9);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("King_Teleport.ogg"));

	// Player
	CObject* pPlayer = NULL;
	m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);
	if(pPlayer == NULL)
		return;

	// PlayerTransformCom
	CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

	D3DXVECTOR3 vDir = pPlayerTransformCom->m_vPos - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;
	D3DXVec3Normalize(&vDir, &vDir);

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

	m_vMovePos = m_pTransformCom->m_vPos - (vDir * 400.f);
}

CMonsterState* CSkeleton_King_Teleport_Back::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		CNaviCell* pNextCell;
		CPathFindMgr::GetInstance()->Solution(&m_pTransformCom->m_vPos, m_pPathFindCom->m_pCell, &m_vMovePos, &pNextCell);

		m_pPathFindCom->m_pCell = pNextCell;

		return new CSkeleton_King_Summon(1);
	}

	return NULL;
}
