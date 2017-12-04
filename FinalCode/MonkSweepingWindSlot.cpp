#include "StdAfx.h"
#include "MonkSweepingWindSlot.h"

CMonkSweepingWindSlot::CMonkSweepingWindSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_TECHNIQUES;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_SWEEPING_WIND;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CMonkSweepingWindSlot::~CMonkSweepingWindSlot()
{
}

SLOT_RESULT CMonkSweepingWindSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Effort
	if(m_pOwner->GetStat()->iEffort < 75 * (1.0f - m_pOwner->GetReducedEffortConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("공력이 부족합니다."));
		return SLOT_RESULT_EFFORT_EMPTY;
	}

	// Mode
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SWEEPING_WIND.ogg"));

	// Effort
	m_pOwner->GetStat()->iEffort -= int(75 * (1.0f - m_pOwner->GetReducedEffortConsumption()));

	CObject* pObj = NULL;

	m_pOwner->GetLayer()->FindObject(pObj, _T("SweepingWind"), LAYER_TYPE_EFFECT);

	if(pObj != NULL)
	{
		pObj->Destroy();
	}

	CMonk_SweepingWind_RingEffect* pRingEffect = new CMonk_SweepingWind_RingEffect(_T("SweepingWind"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pRingEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pRingEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = D3DXVECTOR3(0.f, 10.f, 0.f);
	pRingEffect->Initialize();
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkSweepingWindSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkSweepingWindSlot::End()
{
	return SLOT_RESULT_NULL;
}
