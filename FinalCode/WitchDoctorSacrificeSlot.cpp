#include "StdAfx.h"
#include "WitchDoctorSacrificeSlot.h"

CWitchDoctorSacrificeSlot::CWitchDoctorSacrificeSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_TERROR;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_SACRIFICE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorSacrificeSlot::~CWitchDoctorSacrificeSlot()
{
}

SLOT_RESULT CWitchDoctorSacrificeSlot::Begin(int _iMode)
{
	/*
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	if (CInputMgr::GetInstance()->GetPickPos() == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));
		return SLOT_RESULT_ERROR_PICK;
	}

	CSlot::Begin(_iMode);

	D3DXVECTOR3 vDir =  *CInputMgr::GetInstance()->GetPickPos() - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;
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

	*/
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorSacrificeSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorSacrificeSlot::End()
{
	return SLOT_RESULT_NULL;
}
