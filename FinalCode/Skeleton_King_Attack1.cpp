#include "StdAfx.h"
#include "Skeleton_King_Attack1.h"

CSkeleton_King_Attack1::CSkeleton_King_Attack1(void)
{
	// StateType
	m_eStateType = STATE_TYPE_SKELETON_KING_ATTACK1;

	// Mode
	m_iMode = 0;
	
	// Time
	m_fTime = 0.0f;

	m_bEffect = false;
}

CSkeleton_King_Attack1::~CSkeleton_King_Attack1(void)
{
}

void CSkeleton_King_Attack1::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("King_Attack1.ogg"));
}

CMonsterState* CSkeleton_King_Attack1::Action()
{
	if(!m_bEffect && m_pAnimController->GetTrackPos() > 0.58f)
	{
		CSkeletonKing_WeaponTrail* pWeaponTrail = new CSkeletonKing_WeaponTrail(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pWeaponTrail, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pWeaponTrail->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos, &pTransformCom->m_vPos, &((CSkeleton_King*)m_pOwner)->m_CenterTopBone.mWorld);
		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pWeaponTrail->Initialize();

		m_bEffect = true;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CSkeleton_King_Walk;

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CSkeleton_King_Attack1::Mode0()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 0.0f)
	{
		m_pOwner->CreateAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}

CMonsterState* CSkeleton_King_Attack1::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.0f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}
	return NULL;
}