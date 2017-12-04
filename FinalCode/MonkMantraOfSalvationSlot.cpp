#include "StdAfx.h"
#include "MonkMantraOfSalvationSlot.h"

CMonkMantraOfSalvationSlot::CMonkMantraOfSalvationSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_MANTRAS;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_MANTRA_OF_SALVATION;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkMantraOfSalvationSlot::~CMonkMantraOfSalvationSlot()
{
}

SLOT_RESULT CMonkMantraOfSalvationSlot::Begin(int _iMode)
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

	
	CMonk_MantraOfSalvation_OuterDecalEffect* pOuterEffect = new CMonk_MantraOfSalvation_OuterDecalEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pOuterEffect, LAYER_TYPE_EFFECT);
	pOuterEffect->Initialize();	

	CMonk_MantraOfSalvation_DecalEffect* pEffect = new CMonk_MantraOfSalvation_DecalEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pEffect, LAYER_TYPE_EFFECT);
	pEffect->Initialize();

	CMonk_MantraOfSalvation_CreateEffect* pCreateEffect = new CMonk_MantraOfSalvation_CreateEffect(_T("Mantra"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pCreateEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pCreateEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pCreateEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfSalvationSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkMantraOfSalvationSlot::End()
{
	return SLOT_RESULT_NULL;
}
