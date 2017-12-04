#include "StdAfx.h"
#include "MonkMantraOfRetributionSlot.h"

CMonkMantraOfRetributionSlot::CMonkMantraOfRetributionSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_MANTRAS;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_MANTRA_OF_RETRIBUTION;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkMantraOfRetributionSlot::~CMonkMantraOfRetributionSlot()
{
}

SLOT_RESULT CMonkMantraOfRetributionSlot::Begin(int _iMode)
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

	//생성
	vector<CObject*> vecFindObject;
	m_pOwner->GetLayer()->FindObjects(vecFindObject, _T("Mantra"), LAYER_TYPE_EFFECT);
	
	if(vecFindObject.size() != 0)
	{
		for(size_t i = 0; i < vecFindObject.size(); ++i)
		{
			vecFindObject[i]->Destroy();
		}
	}

	CMonk_MantraOfRetribution_DecalEffect* pRetributionEffect = new CMonk_MantraOfRetribution_DecalEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pRetributionEffect, LAYER_TYPE_EFFECT);
	pRetributionEffect->Initialize();

	CMonk_MantraOfRetribution_FlashDecalEffect* pFlahsDecalEffect = new CMonk_MantraOfRetribution_FlashDecalEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pFlahsDecalEffect, LAYER_TYPE_EFFECT);
	pFlahsDecalEffect->Initialize();

	CMonk_MantraOfRetribution_CreateEffect* pParticleEffect = new CMonk_MantraOfRetribution_CreateEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pParticleEffect, LAYER_TYPE_EFFECT);
	pParticleEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfRetributionSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfRetributionSlot::End()
{
	return SLOT_RESULT_NULL;
}
