#include "StdAfx.h"
#include "DemonHunterMultishotSlot.h"

CDemonHunterMultishotSlot::CDemonHunterMultishotSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_ARCHERY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_MULTISHOT;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterMultishotSlot::~CDemonHunterMultishotSlot()
{
}

SLOT_RESULT CDemonHunterMultishotSlot::Begin(int _iMode)
{
	// Check Enable
	if(!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Weapon
	bool bCheckWeapon = false;
	DWORD dwBow = WEAPON_ID_BOW | WEAPON_ID_CROSSBOW | WEAPON_ID_HANDXBOW;

	if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL && (CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & dwBow))
		bCheckWeapon = true;
	else if(CItemMgr::GetInstance()->GetItemInEquip(11) != NULL && (CItemMgr::GetInstance()->GetItemInEquip(11)->dwItemID & dwBow))
		bCheckWeapon = true;

	if(bCheckWeapon == false)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("다른 무기가 필요합니다."));	
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
	}

	// Check Hate
	if(m_pOwner->GetStat()->iHate < 25 * (1.0f - m_pOwner->GetReducedHateConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("증오가 부족합니다."));
		return SLOT_RESULT_HATE_EMPTY;
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("MULTISHOT.ogg"));

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

	// Hate
	m_pOwner->GetStat()->iHate -= int(25 * (1.0f - m_pOwner->GetReducedHateConsumption()));

	CDemonHunter_MultiShot_DummyEffect* pDummyEffect = new CDemonHunter_MultiShot_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &vDir);
	m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDummyEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
	pDummyEffect->Initialize();
	
	CDemonHunter_MultiShot_FlashEffect* pFlashEffect = new CDemonHunter_MultiShot_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f) + vDir * 30.f;
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pFlashEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterMultishotSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterMultishotSlot::End()
{
	return SLOT_RESULT_NULL;
}