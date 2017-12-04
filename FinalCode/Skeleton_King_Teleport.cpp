#include "StdAfx.h"
#include "Skeleton_King_Teleport.h"

CSkeleton_King_Teleport::CSkeleton_King_Teleport(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_TELEPORT;
	m_fInvisibleTime = 0.0f;

	// Effect
	m_bEffect = false;
}

CSkeleton_King_Teleport::~CSkeleton_King_Teleport(void)
{
}

void CSkeleton_King_Teleport::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(7);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("King_Teleport.ogg"));
}

CMonsterState* CSkeleton_King_Teleport::Action()
{
	if(!m_bEffect && m_pAnimController->GetTrackPos() > 1.155f)
	{
		CSkeletonKing_TeleportShell* pTeleportShell = new CSkeletonKing_TeleportShell(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pTeleportShell, LAYER_TYPE_EFFECT);
		pTeleportShell->Initialize();

		CTransformCom* pTransformCom = (CTransformCom*)pTeleportShell->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos;

		m_bEffect = true;
	}

	if(m_fInvisibleTime > 1.f)
	{
		CRenderCom* pRenderCom = new CRenderCom(RENDER_TYPE_MONSTER);
		m_pOwner->AddComponent(pRenderCom);
		return new CSkeleton_King_Teleport_Attack;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		m_fInvisibleTime += CTimeMgr::GetInstance()->GetDeltaTime();
		m_pOwner->RemoveComponent(COM_TYPE_RENDER);
	}

	return NULL;
}
