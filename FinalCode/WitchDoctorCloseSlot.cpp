#include "StdAfx.h"
#include "WitchDoctorCloseSlot.h"

CWitchDoctorCloseSlot::CWitchDoctorCloseSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_END;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_CLOSE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;
}

CWitchDoctorCloseSlot::~CWitchDoctorCloseSlot()
{
}

SLOT_RESULT CWitchDoctorCloseSlot::Begin(int _iMode)
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

SLOT_RESULT CWitchDoctorCloseSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorCloseSlot::End()
{
	return SLOT_RESULT_NULL;
}
