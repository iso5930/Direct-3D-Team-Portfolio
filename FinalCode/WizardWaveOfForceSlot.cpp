#include "StdAfx.h"
#include "WizardWaveOfForceSlot.h"

CWizardWaveOfForceSlot::CWizardWaveOfForceSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_FORCE;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_WAVE_OF_FORCE;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardWaveOfForceSlot::~CWizardWaveOfForceSlot()
{
}

SLOT_RESULT CWizardWaveOfForceSlot::Begin(int _iMode)
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("WAVE_OF_FORCE.ogg"));


	// Vision
	m_pOwner->GetStat()->iVision -= int(25 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	CWizard_WaveOfForce_CreateEffect* pEffect = new CWizard_WaveOfForce_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardWaveOfForceSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardWaveOfForceSlot::End()
{
	return SLOT_RESULT_NULL;
}
