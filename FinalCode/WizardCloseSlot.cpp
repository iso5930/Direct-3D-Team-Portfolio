#include "StdAfx.h"
#include "WizardCloseSlot.h"

CWizardCloseSlot::CWizardCloseSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_END;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_CLOSE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;
}

CWizardCloseSlot::~CWizardCloseSlot()
{
}

SLOT_RESULT CWizardCloseSlot::Begin(int _iMode)
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

SLOT_RESULT CWizardCloseSlot::Action()
{
	return SLOT_RESULT_END;
}

SLOT_RESULT CWizardCloseSlot::End()
{
	return SLOT_RESULT_END;
}
