#include "StdAfx.h"
#include "MonkSerenitySlot.h"

CMonkSerenitySlot::CMonkSerenitySlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_SERENITY;

	// CooldownTime
	m_fCooldownTime = 16.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkSerenitySlot::~CMonkSerenitySlot()
{

}

SLOT_RESULT CMonkSerenitySlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SERENITY.ogg"));


	// Buff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_MONK_SERENITY , 3.f));

	CMonk_Serenity_DummyEffect* pDummyEffect = new CMonk_Serenity_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDummyEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDummyEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkSerenitySlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkSerenitySlot::End()
{
	return SLOT_RESULT_NULL;
}
