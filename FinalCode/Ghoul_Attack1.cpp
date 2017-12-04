#include "StdAfx.h"
#include "Ghoul_Attack1.h"

CGhoul_Attack1::CGhoul_Attack1(void)
{
	// StateType
	m_eStateType = STATE_TYPE_GHOUL_ATTACK1;

	// Mode
	m_iMode = 0;
	
	// Time
	m_fTime = 0.0f;

	// Effect
	m_fEffectCreateTime = 0.0f;
	m_bEffect = false;
}

CGhoul_Attack1::~CGhoul_Attack1(void)
{
}

void CGhoul_Attack1::Initialize()
{
	CMonsterState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(2);

	CSoundMgr::GetInstance()->PlaySoundForMonster(_T("Ghoul_Attack.ogg"));
}

CMonsterState* CGhoul_Attack1::Action()
{
	m_fEffectCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fEffectCreateTime > 0.264 && !m_bEffect)
	{
		D3DXVECTOR3 vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
		memcpy(&vLook, &m_pTransformCom->m_mWorld.m[2][0], sizeof(D3DXVECTOR3));
		vLook.y = 0.f;
		D3DXVec3Normalize(&vLook, &vLook);

		D3DXVECTOR3 vPos = m_pTransformCom->m_vPos - (vLook * 100);

		CGhoul_Scratch_A* pScratchA = new CGhoul_Scratch_A(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vPos));
		m_pOwner->GetLayer()->AddObject(pScratchA, LAYER_TYPE_EFFECT);
		pScratchA->Initialize();

		CTransformCom* pEffectTransformCom = (CTransformCom*)pScratchA->GetComponent(COM_TYPE_TRANSFORM);

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
		return new CGhoul_Run(1);

	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CMonsterState* CGhoul_Attack1::Mode0()
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

CMonsterState* CGhoul_Attack1::Mode1()
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