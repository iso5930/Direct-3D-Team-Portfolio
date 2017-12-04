#include "StdAfx.h"
#include "WitchDoctorMassConfusionSlot.h"

CWitchDoctorMassConfusionSlot::CWitchDoctorMassConfusionSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_TERROR;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_MASS_CONFUSION;

	// CooldownTime
	m_fCooldownTime = 60.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorMassConfusionSlot::~CWitchDoctorMassConfusionSlot()
{
}

SLOT_RESULT CWitchDoctorMassConfusionSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	D3DXVECTOR3 vPickPos = D3DXVECTOR3(0.f , 0.f , 0.f);

	// Check Pick
	if(m_pOwner->GetPickObject() == NULL)
	{
		if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
			return SLOT_RESULT_ERROR_PICK;
		}

		vPickPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		vPickPos = pTransformCom->m_vPos;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Dir
	D3DXVECTOR3 vDir =  vPickPos - m_pTransformCom->m_vPos;
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

SLOT_RESULT CWitchDoctorMassConfusionSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorMassConfusionSlot::End()
{
	return SLOT_RESULT_NULL;
}
