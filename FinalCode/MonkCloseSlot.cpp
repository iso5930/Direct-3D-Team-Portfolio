#include "StdAfx.h"
#include "MonkCloseSlot.h"

CMonkCloseSlot::CMonkCloseSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_END;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_CLOSE;

	// CooldownTime
	m_fCooldownTime = 0.0f;
	
	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;
}

CMonkCloseSlot::~CMonkCloseSlot()
{
}

SLOT_RESULT CMonkCloseSlot::Begin(int _iMode)
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

SLOT_RESULT CMonkCloseSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkCloseSlot::End()
{
	return SLOT_RESULT_NULL;
}
