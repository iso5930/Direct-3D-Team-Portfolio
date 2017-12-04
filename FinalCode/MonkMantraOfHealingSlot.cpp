#include "StdAfx.h"
#include "MonkMantraOfHealingSlot.h"

CMonkMantraOfHealingSlot::CMonkMantraOfHealingSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_MANTRAS;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_MANTRA_OF_HEALING;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkMantraOfHealingSlot::~CMonkMantraOfHealingSlot()
{
}

SLOT_RESULT CMonkMantraOfHealingSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Effort
	if(m_pOwner->GetStat()->iEffort < 50 * (1.0f - m_pOwner->GetReducedEffortConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("공력이 부족합니다."));
		return SLOT_RESULT_EFFORT_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("MANTRA.ogg"));

	// Effort
	m_pOwner->GetStat()->iEffort -= int(50 * (1.0f - m_pOwner->GetReducedEffortConsumption()));

	// AddBuff
	m_pOwner->AddBuff(new Buff(BUFF_TYPE_MONK_MANTRA , 3600.f));

	vector<CObject*> vecFindObject;
	m_pOwner->GetLayer()->FindObjects(vecFindObject, _T("Mantra"), LAYER_TYPE_EFFECT);

	if(vecFindObject.size() != 0)
	{
		for(size_t i = 0; i < vecFindObject.size(); ++i)
		{
			vecFindObject[i]->Destroy();
		}
	}

	CMonk_MantraOfHealing_NovaEffect* pNovaEffect = new CMonk_MantraOfHealing_NovaEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pNovaEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pNovaEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 100.f, 0.f);
	pNovaEffect->Initialize();

	CMonk_MantraOfHealing_DecalEffect* pDecalEffect = new CMonk_MantraOfHealing_DecalEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);
	pDecalEffect->Initialize();

	CMonk_MantraOfHealing_FlashCecalEffect* pGlowEffect = new CMonk_MantraOfHealing_FlashCecalEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pGlowEffect, LAYER_TYPE_EFFECT);
	pGlowEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfHealingSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfHealingSlot::End()
{
	return SLOT_RESULT_NULL;
}
