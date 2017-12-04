#include "StdAfx.h"
#include "WitchDoctorBigBadVoodooSlot.h"

CWitchDoctorBigBadVoodooSlot::CWitchDoctorBigBadVoodooSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_VOODOO;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO;

	// CooldownTime
	m_fCooldownTime = 120.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorBigBadVoodooSlot::~CWitchDoctorBigBadVoodooSlot()
{
}

SLOT_RESULT CWitchDoctorBigBadVoodooSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	if(CInputMgr::GetInstance()->GetPickPos() == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("��ȿ���� ���� �����Դϴ�."));	
		return SLOT_RESULT_ERROR_PICK;
	}

	// Begin
	CSlot::Begin(_iMode);

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorBigBadVoodooSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorBigBadVoodooSlot::End()
{
	return SLOT_RESULT_NULL;
}
