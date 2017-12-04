#include "StdAfx.h"
#include "WizardFarAttackSlot.h"

CWizardFarAttackSlot::CWizardFarAttackSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_FAR_ATTACK;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardFarAttackSlot::~CWizardFarAttackSlot()
{
}

SLOT_RESULT CWizardFarAttackSlot::Begin(int _iMode)
{	
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Weapon
	if (CItemMgr::GetInstance()->GetItemInEquip(9) == NULL )
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("���Ⱑ ���� ���� �ʽ��ϴ�."));
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
	}

	if(!(CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & (WEAPON_ID_CROSSBOW | WEAPON_ID_BOW) ))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("���Ⱑ ���� ���� �ʽ��ϴ�."));
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
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

	CWizard_FarAttack_ArrowEffect* pArrowEffect = new CWizard_FarAttack_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.f));
	m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pArrowEffect->Initialize();
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardFarAttackSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardFarAttackSlot::End()
{
	return SLOT_RESULT_NULL;
}
