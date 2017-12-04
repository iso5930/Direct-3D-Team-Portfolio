#include "StdAfx.h"
#include "Zombie_Skinny_Male_White_Attack2.h"

CZombie_Skinny_Male_White_Attack2::CZombie_Skinny_Male_White_Attack2(void)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_SKINNY_MALE_WHITE_ATTACK2;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.f;

	// Effect
	m_fEffectCreateTime = 0.0f;
	m_bEffect = false;
}

CZombie_Skinny_Male_White_Attack2::~CZombie_Skinny_Male_White_Attack2(void)
{
}


void CZombie_Skinny_Male_White_Attack2::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Skinny_Male_Attack2.ogg"));
}

CMonsterState* CZombie_Skinny_Male_White_Attack2::Action()
{
	m_fEffectCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEffectCreateTime > 0.495f && !m_bEffect)
	{
		CZombie_Skinny_Male_Scratch_B* pScratchB = new CZombie_Skinny_Male_Scratch_B(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(m_pTransformCom->m_vPos));
		m_pOwner->GetLayer()->AddObject(pScratchB, LAYER_TYPE_EFFECT);
		pScratchB->Initialize();

		CTransformCom* pEffectTransformCom = (CTransformCom*)pScratchB->GetComponent(COM_TYPE_TRANSFORM);

		CObject* pPlayer = NULL;
		m_pOwner->GetLayer()->FindObject(pPlayer, _T("Player"), LAYER_TYPE_PLAYER);

		CTransformCom* pPlayerTransformCom = (CTransformCom*)pPlayer->GetComponent(COM_TYPE_TRANSFORM);

		// AxisZ
		D3DXVECTOR3 vAxisZ(0.0f, 0.0f, 0.0f);
		vAxisZ.x = pPlayerTransformCom->m_vPos.x - m_pTransformCom->m_vPos.x;
		vAxisZ.z = pPlayerTransformCom->m_vPos.z - m_pTransformCom->m_vPos.z;
		D3DXVec3Normalize(&vAxisZ, &vAxisZ);

		// AxisX
		D3DXVECTOR3 vAxisX(0.0f, 0.0f, 0.0f);
		vAxisX.x = -vAxisZ.z;
		vAxisX.z = vAxisZ.x;

		// DotX
		float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vAxisZ);
		fDotX = RevisionDot(fDotX);

		// DotZ
		float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vAxisZ);
		fDotZ = RevisionDot(fDotZ);

		pEffectTransformCom->m_vAngle.y = acosf(fDotZ);

		pEffectTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

		m_fEffectCreateTime = 0.0f;
		m_bEffect = true;
	}

	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
		return new CZombie_Skinny_Male_White_Walk1(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CZombie_Skinny_Male_White_Attack2::Mode0()
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

CMonsterState* CZombie_Skinny_Male_White_Attack2::Mode1()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > 1.f)
	{
		m_pOwner->RemoveAttack();

		m_fTime = 0.0f;
		++m_iMode;
	}

	return NULL;
}
