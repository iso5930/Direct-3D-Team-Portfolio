#include "StdAfx.h"
#include "MonkSevenSidedStrikeSlot.h"

CMonkSevenSidedStrikeSlot::CMonkSevenSidedStrikeSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_FOCUS;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_SEVEN_SIDED_STRIKE;

	// CooldownTime
	m_fCooldownTime = 30.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkSevenSidedStrikeSlot::~CMonkSevenSidedStrikeSlot()
{
}

SLOT_RESULT CMonkSevenSidedStrikeSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Effort
	if(m_pOwner->GetStat()->iEffort < 50 * (1.0f - m_pOwner->GetReducedEffortConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ �����մϴ�."));
		return SLOT_RESULT_EFFORT_EMPTY;
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
	m_pOwner->GetStat()->iEffort -= int(50 * (1.0f - m_pOwner->GetReducedEffortConsumption()));

	CMonk_SevenSidedStrike_DecalEffect* pDecalEffect = new CMonk_SevenSidedStrike_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDecalEffect->Initialize();

	CMonk_SevenSidedStrike_DecalGlowEffect* pDecalGlowEffect = new CMonk_SevenSidedStrike_DecalGlowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecalGlowEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pDecalGlowEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDecalGlowEffect->Initialize();

	CMonk_SevenSidedStrike_RuneEffect* pRuneEffect = new CMonk_SevenSidedStrike_RuneEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pRuneEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pRuneEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pRuneEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkSevenSidedStrikeSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkSevenSidedStrikeSlot::End()
{
	return SLOT_RESULT_NULL;
}
