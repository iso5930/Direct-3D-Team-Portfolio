#include "StdAfx.h"
#include "WizardPotionSlot.h"

CWizardPotionSlot::CWizardPotionSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_END;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_POTION;

	// CooldownTime
	m_fCooldownTime = 30.0f;

	// Time
	m_fTime = m_fCooldownTime;
}

CWizardPotionSlot::~CWizardPotionSlot()
{
}

SLOT_RESULT CWizardPotionSlot::Begin(int _iMode)
{
	// Check Enable
	if(m_bEnable == false)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// MaxLife
	int iMaxLife = int((m_pOwner->GetStat()->iMaxLife + m_pOwner->GetVitality() * 10) * m_pOwner->GetRestoresBonus());
	if(m_pOwner->GetStat()->iLife == iMaxLife)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("생명력이 이미 가득 찼습니다."));
		return SLOT_RESULT_FULL_LIFE;
	}

	// PlaySoundForUI
	CSoundMgr::GetInstance()->PlaySoundForUI(_T("Drink.ogg"));

	// Begin
	CSlot::Begin(_iMode);

	// Recovery
	m_pOwner->GetStat()->iLife += int(iMaxLife * 0.6f);
	if(m_pOwner->GetStat()->iLife > iMaxLife)
		m_pOwner->GetStat()->iLife = iMaxLife;

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardPotionSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardPotionSlot::End()
{
	return SLOT_RESULT_NULL;
}