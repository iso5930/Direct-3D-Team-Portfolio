#include "StdAfx.h"
#include "WitchDoctorOpenSlot.h"

CWitchDoctorOpenSlot::CWitchDoctorOpenSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_OPEN;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;
}

CWitchDoctorOpenSlot::~CWitchDoctorOpenSlot()
{
}

SLOT_RESULT CWitchDoctorOpenSlot::Begin(int _iMode)
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

	return SLOT_RESULT_END;
}

SLOT_RESULT CWitchDoctorOpenSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorOpenSlot::End()
{
	return SLOT_RESULT_NULL;
}
