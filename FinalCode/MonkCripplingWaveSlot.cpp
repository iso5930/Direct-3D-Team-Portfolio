#include "StdAfx.h"
#include "MonkCripplingWaveSlot.h"

CMonkCripplingWaveSlot::CMonkCripplingWaveSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_CRIPPLING_WAVE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 50.f;

}

CMonkCripplingWaveSlot::~CMonkCripplingWaveSlot()
{
}

SLOT_RESULT CMonkCripplingWaveSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	D3DXVECTOR3 vPos;
	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			vPos =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
			return SLOT_RESULT_ERROR_PICK;
		}
		else
			vPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		vPos = pTransformCom->m_vPos;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Dir
	D3DXVECTOR3 vDir = vPos - m_pTransformCom->m_vPos;
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

	// Effort
	m_pOwner->GetStat()->iEffort += 12;
	if ( m_pOwner->GetStat()->iEffort > m_pOwner->GetStat()->iMaxEffort )
		m_pOwner->GetStat()->iEffort = m_pOwner->GetStat()->iMaxEffort;

	if (
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_01||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_01 
		)
	{
		CMonk_CripplingWave_Attack2DummyEffect* pDummyEffect = new CMonk_CripplingWave_Attack2DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);
		pDummyEffect->Initialize();
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("CRIPPLING_WAVE2.ogg"));
	}
	else if(
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_DEBILITATINGBLOWS_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_DEBILITATINGBLOWS_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_DEBILITATINGBLOWS_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_DEBILITATINGBLOWS_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_DEBILITATINGBLOWS_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_DEBILITATINGBLOWS_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_DEBILITATINGBLOWS_02 
		)
	{
		CMonk_CripplingWave_Attack3CreateEffect* pAttack3 = new CMonk_CripplingWave_Attack3CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pAttack3, LAYER_TYPE_EFFECT);
		pAttack3->Initialize();
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("CRIPPLING_WAVE3.ogg"));
	}
	else
	{
		CMonk_CripplingWave_Attack1DummyEffect* pDummyEffect = new CMonk_CripplingWave_Attack1DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);
		pDummyEffect->Initialize();
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("CRIPPLING_WAVE1.ogg"));
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkCripplingWaveSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkCripplingWaveSlot::End()
{
	return SLOT_RESULT_NULL;
}
