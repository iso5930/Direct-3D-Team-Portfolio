#include "StdAfx.h"
#include "DemonHunterShadowPowerSlot.h"

CDemonHunterShadowPowerSlot::CDemonHunterShadowPowerSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_SHADOW_POWER;

	// ColldownTime
	m_fCooldownTime = 5.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterShadowPowerSlot::~CDemonHunterShadowPowerSlot()
{
}

SLOT_RESULT CDemonHunterShadowPowerSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Control
	if(m_pOwner->GetStat()->iControl < 12 * (1.0f - m_pOwner->GetReducedControlConsumption()) )
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("절제가 부족합니다."));
		return SLOT_RESULT_CONTROL_EMPTY;

	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SHADOW_POWER.ogg"));

	// Control
	m_pOwner->GetStat()->iControl -= int(12 * (1.0f - m_pOwner->GetReducedControlConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_SHADOW_POWER , 5.f));

	CDemonHunter_ShadowPower_WingEffect* pWingEffect = new CDemonHunter_ShadowPower_WingEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &m_pTransformCom->m_mWorld);
	m_pOwner->GetLayer()->AddObject(pWingEffect, LAYER_TYPE_EFFECT);
	pWingEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterShadowPowerSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterShadowPowerSlot::End()
{
	return SLOT_RESULT_NULL;
}
