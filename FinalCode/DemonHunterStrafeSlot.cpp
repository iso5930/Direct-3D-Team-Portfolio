#include "StdAfx.h"
#include "DemonHunterStrafeSlot.h"

CDemonHunterStrafeSlot::CDemonHunterStrafeSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_ARCHERY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_STRAFE;

	// CooldownTime
	m_fCooldownTime = 1.0f;

	// Time
	m_fTime = m_fCooldownTime;

	for(int i = 0; i < 3; ++i)
	{
		m_pAfterImage[i] = NULL;
	}

	m_pSpinEffect = NULL;	

	m_fAngleTime = 0.f;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterStrafeSlot::~CDemonHunterStrafeSlot()
{
}

SLOT_RESULT CDemonHunterStrafeSlot::Begin(int _iMode)
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
	if(m_pOwner->GetStat()->iHate < 12 * (1.0f - m_pOwner->GetReducedHateConsumption()))
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
	m_pOwner->GetStat()->iHate -= int(12 * (1.0f - m_pOwner->GetReducedHateConsumption()));

	
	m_pSpinEffect = new CDemonHunter_Strafe_SpinEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pOwner->GetLayer()->AddObject(m_pSpinEffect, LAYER_TYPE_EFFECT);
	m_pSpinEffect->Initialize();

	for(int i = 0; i < 3; ++i)
	{
		int iRand = rand() % 360;

		m_pAfterImage[i] = new CDemonHunter_Strafe_AfterImageEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(m_pAfterImage[i], LAYER_TYPE_EFFECT);
		
		CTransformCom* pTransform = (CTransformCom*)m_pAfterImage[i]->GetComponent(COM_TYPE_TRANSFORM);
		pTransform->m_vAngle.y = D3DXToRadian(iRand);
		m_pAfterImage[i]->Initialize();
	}
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterStrafeSlot::Action()
{
	// Time
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	m_fAngleTime += CTimeMgr::GetInstance()->GetDeltaTime();

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

	// Check Hate
	if (m_fTime >  0.5f )
	{
		m_fTime = 0.0f;

		if(m_pOwner->GetStat()->iHate < 12 * (1.0f - m_pOwner->GetReducedHateConsumption()))
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("증오가 부족합니다."));
			return SLOT_RESULT_HATE_EMPTY;
		}

		// Hate
		m_pOwner->GetStat()->iHate -= int(12 * (1.0f - m_pOwner->GetReducedHateConsumption()));
	}

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
	
	if(m_fAngleTime >= 0.5f)
	{
		m_fAngleTime = 0.f;

		for(int i = 0; i < 3; ++i)
		{
			int iRand = rand() % 360;
			CTransformCom* pTransformCom = (CTransformCom*)m_pAfterImage[i]->GetComponent(COM_TYPE_TRANSFORM);
			pTransformCom->m_vAngle.y = D3DXToRadian(iRand);
		}
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterStrafeSlot::End()
{
	for(int i = 0; i < 3; ++i)
	{
		if(m_pAfterImage[i] != NULL)
		{
			m_pAfterImage[i]->Destroy();
			m_pAfterImage[i] = NULL;
		}
	}
	
	if(m_pSpinEffect != NULL)
	{
		m_pSpinEffect->Destroy();
		m_pSpinEffect = NULL;
	}

	m_fAngleTime = 0.f;

	return SLOT_RESULT_NULL;
}
