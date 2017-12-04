#include "StdAfx.h"
#include "MonkDeadlyReachSlot.h"

CMonkDeadlyReachSlot::CMonkDeadlyReachSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_DEADLY_REACH;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkDeadlyReachSlot::~CMonkDeadlyReachSlot()
{
}

SLOT_RESULT CMonkDeadlyReachSlot::Begin(int _iMode)
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
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_LONGREACH_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_LONGREACH_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_LONGREACH_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_LONGREACH_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_01 
		)
	{
		CMonk_DeadlyReach_AfterImageEffect* pAfterImage = new CMonk_DeadlyReach_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, (vDir * 1000.f));
		m_pOwner->GetLayer()->AddObject(pAfterImage, LAYER_TYPE_EFFECT);

		CTransformCom* pTrnasformCom = (CTransformCom*)pAfterImage->GetComponent(COM_TYPE_TRANSFORM);
		pTrnasformCom->m_vPos = m_pTransformCom->m_vPos;
		pTrnasformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pAfterImage->Initialize();

		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("DEADLY_REACH2.ogg"));
	}
	else if(
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_LONGREACH_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_LONGREACH_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_LONGREACH_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_LONGREACH_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_LONGREACH_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_LONGREACH_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_LONGREACH_02 
		)
	{
		//3번째 이펙트
		CMonk_DeadlyReach_FistsEffect* pFistsEffect = new CMonk_DeadlyReach_FistsEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, (vDir * 1000.f), 0.45f);
		m_pOwner->GetLayer()->AddObject(pFistsEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pFistsEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f) + (vDir * 30.f);
		pFistsEffect->Initialize();
		
	}
	else
	{
		CMonk_DeadlyReach_FistsEffect* pFistsEffect = new CMonk_DeadlyReach_FistsEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, (vDir * 1000.f));
		m_pOwner->GetLayer()->AddObject(pFistsEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pFistsEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f);
		pFistsEffect->Initialize();
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("DEADLY_REACH1.ogg"));
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkDeadlyReachSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkDeadlyReachSlot::End()
{
	return SLOT_RESULT_NULL;
}
