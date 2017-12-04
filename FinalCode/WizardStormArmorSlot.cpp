#include "StdAfx.h"
#include "WizardStormArmorSlot.h"

CWizardStormArmorSlot::CWizardStormArmorSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_CONJURATION;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_STORM_ARMOR;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardStormArmorSlot::~CWizardStormArmorSlot()
{
}

SLOT_RESULT CWizardStormArmorSlot::Begin(int _iMode)
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

	// Vision
	m_pOwner->GetStat()->iVision -= int(25 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_WIZARD_ARMOR , 1800.f));

	vector<CObject*> vecFindObj;

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("STORM_ARMOR.ogg"));

	m_pOwner->GetLayer()->FindObjects(vecFindObj, _T("Armor"), LAYER_TYPE_EFFECT);

	for(size_t i = 0; i < vecFindObj.size(); ++i)
	{
		vecFindObj[i]->Destroy();
	}

	CWizard_StormArmor_CastingEffect* pCastingEffect = new CWizard_StormArmor_CastingEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCastingEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pCastingEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pCastingEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardStormArmorSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardStormArmorSlot::End()
{
	return SLOT_RESULT_NULL;
}
