#include "StdAfx.h"
#include "WizardMagicWeaponSlot.h"

CWizardMagicWeaponSlot::CWizardMagicWeaponSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_CONJURATION;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_MAGIC_WEAPON;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardMagicWeaponSlot::~CWizardMagicWeaponSlot()
{
}

SLOT_RESULT CWizardMagicWeaponSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Vision
	if (m_pOwner->GetStat()->iVision < 25 * (1.0f - m_pOwner->GetReducedVisionConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("비전력이 부족합니다."));
		return SLOT_RESULT_VISION_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("MAGIC_WEAPON.ogg"));

	// Vision
	m_pOwner->GetStat()->iVision -= int(25 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	CWizard_MagicWeapon_CastingEffect* pCastingEffect = new CWizard_MagicWeapon_CastingEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCastingEffect, LAYER_TYPE_EFFECT);
	pCastingEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardMagicWeaponSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardMagicWeaponSlot::End()
{
	return SLOT_RESULT_NULL;
}
