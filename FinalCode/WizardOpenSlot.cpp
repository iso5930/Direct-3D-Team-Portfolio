#include "StdAfx.h"
#include "WizardOpenSlot.h"

CWizardOpenSlot::CWizardOpenSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_OPEN;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	m_fRange = 9999.f;
}

CWizardOpenSlot::~CWizardOpenSlot()
{
}

SLOT_RESULT CWizardOpenSlot::Begin(int _iMode)
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

SLOT_RESULT CWizardOpenSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardOpenSlot::End()
{
	return SLOT_RESULT_NULL;
}
