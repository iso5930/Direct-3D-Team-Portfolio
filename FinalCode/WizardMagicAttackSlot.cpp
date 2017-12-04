#include "StdAfx.h"
#include "WizardMagicAttackSlot.h"

CWizardMagicAttackSlot::CWizardMagicAttackSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_MAGIC_ATTACK;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardMagicAttackSlot::~CWizardMagicAttackSlot()
{
}

SLOT_RESULT CWizardMagicAttackSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}


	// Check Weapon
	if (CItemMgr::GetInstance()->GetItemInEquip(9) == NULL )
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("무기가 적합 하지 않습니다."));
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
	}

	if(!(CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & (WEAPON_ID_WAND | WEAPON_ID_STAFF) ))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("무기가 적합 하지 않습니다."));
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("MAGIC_MISSILE.ogg"));

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

	//완드를 장착했을때. 공격 모션.
	CWizard_MagicAttack_CreateEffect* pMissileEffect = new CWizard_MagicAttack_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.f), 0.3f);
	m_pOwner->GetLayer()->AddObject(pMissileEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTrnasformCom = (CTransformCom*)pMissileEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTrnasformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f);
	pTrnasformCom->m_vPos += vDir * 15.f;
	pMissileEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardMagicAttackSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardMagicAttackSlot::End()
{
	return SLOT_RESULT_NULL;
}
