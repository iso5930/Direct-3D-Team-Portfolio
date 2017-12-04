#include "StdAfx.h"
#include "WizardFamiliarSlot.h"

CWizardFamiliarSlot::CWizardFamiliarSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_CONJURATION;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_FAMILIAR;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardFamiliarSlot::~CWizardFamiliarSlot()
{
}

SLOT_RESULT CWizardFamiliarSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Vision
	if (m_pOwner->GetStat()->iVision < 20 * (1.0f - m_pOwner->GetReducedVisionConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("비전력이 부족합니다."));
		return SLOT_RESULT_VISION_EMPTY;
	}

	//Begin
	CSlot::Begin(_iMode);


	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("FAMILIAR.ogg"));

	// Vision
	m_pOwner->GetStat()->iVision -= int(20 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	// 이펙트 생성
	CWizard_Familiar_FamiliarEffect* pFamiliarEffect = new CWizard_Familiar_FamiliarEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pFamiliarEffect, LAYER_TYPE_EFFECT);
	pFamiliarEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardFamiliarSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardFamiliarSlot::End()
{
	return SLOT_RESULT_NULL;
}
