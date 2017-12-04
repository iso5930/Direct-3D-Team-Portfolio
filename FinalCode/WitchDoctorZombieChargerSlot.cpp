#include "StdAfx.h"
#include "WitchDoctorZombieChargerSlot.h"

CWitchDoctorZombieChargerSlot::CWitchDoctorZombieChargerSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_DECAY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorZombieChargerSlot::~CWitchDoctorZombieChargerSlot()
{
}

SLOT_RESULT CWitchDoctorZombieChargerSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Mana
	if (m_pOwner->GetStat()->iMana < 150 * (1.0f - m_pOwner->GetReducedManaConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("마나가 부족합니다."));
		return SLOT_RESULT_MANA_EMPTY;
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

	// Mana
	m_pOwner->GetStat()->iMana -= int(150 * (1.0f - m_pOwner->GetReducedManaConsumption()));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorZombieChargerSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorZombieChargerSlot::End()
{
	return SLOT_RESULT_NULL;
}
