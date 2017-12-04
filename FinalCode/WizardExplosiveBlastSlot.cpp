#include "StdAfx.h"
#include "WizardExplosiveBlastSlot.h"

CWizardExplosiveBlastSlot::CWizardExplosiveBlastSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_MASTERY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_EXPLOSIVE_BLAST;

	// ColldownTime
	m_fCooldownTime = 6.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardExplosiveBlastSlot::~CWizardExplosiveBlastSlot()
{
}

SLOT_RESULT CWizardExplosiveBlastSlot::Begin(int _iMode)
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

	// Begin
	CSlot::Begin(_iMode);

	// Vision
	m_pOwner->GetStat()->iVision -= int(20 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("EXPLOSIVE_BLAST.ogg"));


	//이펙트 생성
	CWizard_ExplosiveBlast_DummyEffect* pEffect = new CWizard_ExplosiveBlast_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pEffect, LAYER_TYPE_EFFECT);
	pEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardExplosiveBlastSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardExplosiveBlastSlot::End()
{
	return SLOT_RESULT_NULL;
}
