#include "StdAfx.h"
#include "MonkExplodingPalmSlot.h"

CMonkExplodingPalmSlot::CMonkExplodingPalmSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_TECHNIQUES;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_EXPLODING_PALM;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 50.f;

}

CMonkExplodingPalmSlot::~CMonkExplodingPalmSlot()
{
}

SLOT_RESULT CMonkExplodingPalmSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Effort
	if(m_pOwner->GetStat()->iEffort < 40 * (1.0f - m_pOwner->GetReducedEffortConsumption()))
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
	m_pOwner->GetStat()->iEffort -= int(40 * (1.0f - m_pOwner->GetReducedEffortConsumption()));

	CMonk_ExplodingPalm_DummyEffect* pDummyEffect = new CMonk_ExplodingPalm_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);
	pDummyEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkExplodingPalmSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkExplodingPalmSlot::End()
{
	return SLOT_RESULT_NULL;
}
