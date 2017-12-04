#include "StdAfx.h"
#include "DemonHunterPreparationSlot.h"

CDemonHunterPreparationSlot::CDemonHunterPreparationSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_HUNTING;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_PREPARATION;

	// CooldownTime
	m_fCooldownTime = 10.f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterPreparationSlot::~CDemonHunterPreparationSlot()
{

}

SLOT_RESULT CDemonHunterPreparationSlot::Begin(int _iMode)
{
	// Check Enable
	if(!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("PREPARATION.ogg"));

	// Hate
	m_pOwner->GetStat()->iHate += 30;
	if(m_pOwner->GetStat()->iHate > m_pOwner->GetStat()->iMaxHate)
		m_pOwner->GetStat()->iHate = m_pOwner->GetStat()->iMaxHate;

	CDemonHunter_Preparation_DecalEffect* pDecalEffect = new CDemonHunter_Preparation_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecalEffect);

	CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDecalEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterPreparationSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterPreparationSlot::End()
{
	return SLOT_RESULT_NULL;
}
