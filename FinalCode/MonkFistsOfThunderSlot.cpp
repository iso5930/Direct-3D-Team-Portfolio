#include "StdAfx.h"
#include "MonkFistsOfThunderSlot.h"

CMonkFistsOfThunderSlot::CMonkFistsOfThunderSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_FISTS_OF_THUNDER;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 50.f;

}

CMonkFistsOfThunderSlot::~CMonkFistsOfThunderSlot()
{
}

SLOT_RESULT CMonkFistsOfThunderSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
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
			CUIMgr::GetInstance()->CreateTextMessage(_T("��ȿ���� ���� �����Դϴ�."));	
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
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_LIGHTNING_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_LIGHTNING_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_LIGHTNING_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_LIGHTNING_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_01 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_01 
		)
	{
		//2��° ����Ʈ 
		CMonk_FistsOfThunder_CreateEffect* pCreateEffect = new CMonk_FistsOfThunder_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 0.3f, 1);
		m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);
		pCreateEffect->Initialize();
	
	}
	else if(
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HS_LIGHTNING_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_1HT_LIGHTNING_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_STF_LIGHTNING_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_2HT_LIGHTNING_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_FF_LIGHTNING_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SF_LIGHTNING_02 ||
		m_pOwner->GetState()->GetStateType() == STATE_TYPE_MONK_MALE_DW_SS_LIGHTNING_02 
		)
	{
		//3��° ����Ʈ 
		CMonk_FistsOfThunder_CreateEffect* pCreateEffect = new CMonk_FistsOfThunder_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 0.6f, 2);
		m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);
		pCreateEffect->Initialize();
		
	}
	else
	{
		//1��° ����Ʈ
		CMonk_FistsOfThunder_CreateEffect* pCreateEffect = new CMonk_FistsOfThunder_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, 0.4f, 0);
		m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);
		pCreateEffect->Initialize();
		
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkFistsOfThunderSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkFistsOfThunderSlot::End()
{
	return SLOT_RESULT_NULL;
}
