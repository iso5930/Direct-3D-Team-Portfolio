#include "StdAfx.h"
#include "MonkWayOfTheHundredFistsSlot.h"

CMonkWayOfTheHundredFistsSlot::CMonkWayOfTheHundredFistsSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 50.f;

}

CMonkWayOfTheHundredFistsSlot::~CMonkWayOfTheHundredFistsSlot()
{
}

SLOT_RESULT CMonkWayOfTheHundredFistsSlot::Begin(int _iMode)
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
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_01 
		)
	{
		CMonk_WayOfTheHundredFists_CreateEffect* pCreateEffect = new CMonk_WayOfTheHundredFists_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 0.f, 1);
		m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);
		pCreateEffect->Initialize();

		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("WAY_OF_THE_HUNDRED_FISTS2.ogg"));

	}
	else if(
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_RAPIDSTRIKES_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_RAPIDSTRIKES_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_RAPIDSTRIKES_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_RAPIDSTRIKES_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_RAPIDSTRIKES_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_RAPIDSTRIKES_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_RAPIDSTRIKES_02
		)
	{
		CMonk_WayOfTheHundredFists_CreateEffect* pCreateEffect = new CMonk_WayOfTheHundredFists_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 0.2f, 2);
		m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);
		pCreateEffect->Initialize();
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("WAY_OF_THE_HUNDRED_FISTS3.ogg"));

	}
	else
	{
		//1번째 이펙트 
		CMonk_WayOfTheHundredFists_CreateEffect* pCreateEffect = new CMonk_WayOfTheHundredFists_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 0.f, 0);
		m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);
		pCreateEffect->Initialize();
		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("WAY_OF_THE_HUNDRED_FISTS1.ogg"));

	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkWayOfTheHundredFistsSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkWayOfTheHundredFistsSlot::End()
{
	return SLOT_RESULT_NULL;
}
