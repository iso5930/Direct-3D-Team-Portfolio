#include "StdAfx.h"
#include "WitchDoctorNearAttackSlot.h"

CWitchDoctorNearAttackSlot::CWitchDoctorNearAttackSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_NEAR_ATTACK;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 70.f;

}

CWitchDoctorNearAttackSlot::~CWitchDoctorNearAttackSlot()
{
}

SLOT_RESULT CWitchDoctorNearAttackSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Weapon
	DWORD dwFar = WEAPON_ID_BOW | WEAPON_ID_CROSSBOW | WEAPON_ID_WAND | WEAPON_ID_STAFF ; 
	if ( CItemMgr::GetInstance()->GetItemInEquip(9) == NULL  &&  CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & dwFar )
	{	
		CUIMgr::GetInstance()->CreateTextMessage(_T("무기가 적합하지 않습니다."));
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;	
	}

	D3DXVECTOR3 vPos;
	// Check Pick
	if(m_pOwner->GetPickObject() == NULL)
	{
		if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
			return SLOT_RESULT_ERROR_PICK;
		}

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
	D3DXVECTOR3 vDir =  vPos - m_pTransformCom->m_vPos;
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


	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorNearAttackSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorNearAttackSlot::End()
{
	return SLOT_RESULT_NULL;
}
