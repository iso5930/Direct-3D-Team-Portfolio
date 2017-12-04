#include "StdAfx.h"
#include "MonkMagicAttackSlot.h"

CMonkMagicAttackSlot::CMonkMagicAttackSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_END;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_OPEN;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;
}

CMonkMagicAttackSlot::~CMonkMagicAttackSlot()
{
}

SLOT_RESULT CMonkMagicAttackSlot::Begin(int _iMode)
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

SLOT_RESULT CMonkMagicAttackSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMagicAttackSlot::End()
{
	return SLOT_RESULT_NULL;
}
