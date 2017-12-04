#include "StdAfx.h"
#include "WizardDiamondSkinSlot.h"

CWizardDiamondSkinSlot::CWizardDiamondSkinSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_DIAMOND_SKIN;

	// ColldownTime
	m_fCooldownTime = 15.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardDiamondSkinSlot::~CWizardDiamondSkinSlot()
{
}

SLOT_RESULT CWizardDiamondSkinSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("DIAMOND_SKIN.ogg"));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_WIZARD_ARMOR , 8.f));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardDiamondSkinSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardDiamondSkinSlot::End()
{
	return SLOT_RESULT_NULL;
}
