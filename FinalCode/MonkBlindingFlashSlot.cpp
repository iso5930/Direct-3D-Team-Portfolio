#include "StdAfx.h"
#include "MonkBlindingFlashSlot.h"

CMonkBlindingFlashSlot::CMonkBlindingFlashSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_BLINDING_FLASH;
	
	// CooldownTime
	m_fCooldownTime = 15.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkBlindingFlashSlot::~CMonkBlindingFlashSlot()
{
}

SLOT_RESULT CMonkBlindingFlashSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("BLINDING_FLASH.ogg"));


	CMonk_BlindingFlash_FlashEffect* pFlashEffect = new CMonk_BlindingFlash_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);
	
	CTransformCom* pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
	pFlashEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkBlindingFlashSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkBlindingFlashSlot::End()
{
	return SLOT_RESULT_NULL;
}
