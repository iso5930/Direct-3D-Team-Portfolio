#include "StdAfx.h"
#include "Zombie_Male_Attack.h"

CZombie_Male_Attack::CZombie_Male_Attack(void)
{
	// StateType
	m_eStateType = STATE_TYPE_ZOMBIE_MALE_ATTACK;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

	// Effect
	m_fEffectCreateTime = 0.0f;
	m_bEffect = false;
}

CZombie_Male_Attack::~CZombie_Male_Attack(void)
{
}


void CZombie_Male_Attack::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Zombie_Male_Attack.ogg"));
}

CMonsterState* CZombie_Male_Attack::Action()
{
	m_fEffectCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEffectCreateTime > 0.561f && !m_bEffect)
	{
		CZombie_Male_Scratch* pScratch = new CZombie_Male_Scratch(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(m_pTransformCom->m_vPos));
		m_pOwner->GetLayer()->AddObject(pScratch, LAYER_TYPE_EFFECT);
		pScratch->Initialize();

		CTransformCom* pEffectTransformCom = (CTransformCom*)pScratch->GetComponent(COM_TYPE_TRANSFORM);

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
		return new CZombie_Male_Walk(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CZombie_Male_Attack::Mode0()
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

CMonsterState* CZombie_Male_Attack::Mode1()
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

