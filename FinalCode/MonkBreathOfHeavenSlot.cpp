#include "StdAfx.h"
#include "MonkBreathOfHeavenSlot.h"

CMonkBreathOfHeavenSlot::CMonkBreathOfHeavenSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_BREATH_OF_HEAVEN;

	// CooldownTime
	m_fCooldownTime = 15.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkBreathOfHeavenSlot::~CMonkBreathOfHeavenSlot()
{
}

SLOT_RESULT CMonkBreathOfHeavenSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("BREATH_OF_HEAVEN.ogg"));

	// Life
	int iMaxLife = int((m_pOwner->GetStat()->iMaxLife + m_pOwner->GetVitality() * 10) * m_pOwner->GetRestoresBonus());
	m_pOwner->GetStat()->iLife += 500;
	if(m_pOwner->GetStat()->iLife > iMaxLife)
		m_pOwner->GetStat()->iLife = iMaxLife;

	CMonk_BreathOfHeaven_NovaEffect* pNovaEffect = new CMonk_BreathOfHeaven_NovaEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pNovaEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pNovaEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 30.f, 0.f);
	pNovaEffect->Initialize();

	CMonk_BreathOfHeaven_FlashEffect* pFlashEffect = new CMonk_BreathOfHeaven_FlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pFlashEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pFlashEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 80.f, 0.f);
	pFlashEffect->Initialize();

	CMonk_BreathOfHeaven_UpFlashEffect* pUpFlash = new CMonk_BreathOfHeaven_UpFlashEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pUpFlash, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pUpFlash->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 150.f, 0.f);
	pUpFlash->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkBreathOfHeavenSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkBreathOfHeavenSlot::End()
{
	return SLOT_RESULT_NULL;
}
