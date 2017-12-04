#include "StdAfx.h"
#include "Skeleton_King_Intro.h"

CSkeleton_King_Intro::CSkeleton_King_Intro(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_INTRO;
}

CSkeleton_King_Intro::~CSkeleton_King_Intro(void)
{
}

void CSkeleton_King_Intro::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(12);
}

CMonsterState* CSkeleton_King_Intro::Action()
{
	CCollisionCom*	pCollisionCom = new CCollisionCom(COLL_TYPE_MONSTER, new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 60.0f), new Sphere(&m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f));
	pCollisionCom->m_CollisionVec.push_back(new Collision(COLLISION_DAMAGE, &m_pTransformCom->m_mWorld, &D3DXVECTOR3(0.0f, 60.0f, 0.0f), 30.0f, 70.0f, 30.0f));
	m_pOwner->AddComponent(pCollisionCom);
	pCollisionCom->Initialize();

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_King_Idle(0);

	return NULL;
}
