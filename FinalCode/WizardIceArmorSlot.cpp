#include "StdAfx.h"
#include "WizardIceArmorSlot.h"

CWizardIceArmorSlot::CWizardIceArmorSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_CONJURATION;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_ICE_ARMOR;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardIceArmorSlot::~CWizardIceArmorSlot()
{
}

SLOT_RESULT CWizardIceArmorSlot::Begin(int _iMode)
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("ICE_ARMOR.ogg"));

	// Vision
	m_pOwner->GetStat()->iVision -= int(25 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_WIZARD_ARMOR, 1800.f));

	vector<CObject*> vecFindObj;

	m_pOwner->GetLayer()->FindObjects(vecFindObj, _T("Armor"), LAYER_TYPE_EFFECT);

	for(size_t i = 0; i < vecFindObj.size(); ++i)
	{
		vecFindObj[i]->Destroy();
	}

	//키값을 넣어서 찾아.
	CWizard_IceArmor_CastingEffect* pCastingEffect = new CWizard_IceArmor_CastingEffect(_T("Armor"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCastingEffect, LAYER_TYPE_EFFECT);
	pCastingEffect->Initialize();

	pCastingEffect = new CWizard_IceArmor_CastingEffect(_T("Armor"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCastingEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pCastingEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vAngle.y = D3DXToRadian(180.f);
	pCastingEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardIceArmorSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardIceArmorSlot::End()
{
	return SLOT_RESULT_NULL;
}
