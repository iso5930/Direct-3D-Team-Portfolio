#include "StdAfx.h"
#include "DemonHunterSentrySlot.h"

CDemonHunterSentrySlot::CDemonHunterSentrySlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_DEVICES;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_SENTRY;

	// CooldownTime
	m_fCooldownTime = 0.f;

	// Time
	m_fTime = 0.0f;

	// ChargeTime	
	m_fChargeTime = 8.f;

	// Charge
	m_iCharge = 0;

	// MaxCharge
	m_iMaxCharge = 2;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterSentrySlot::~CDemonHunterSentrySlot()
{
}

SLOT_RESULT CDemonHunterSentrySlot::Begin(int _iMode)
{
	// Check Enable
	if(!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Charge
	if (m_iCharge <= 0)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 기술을 사용하려면 충전이 필요합니다."));
		return SLOT_RESULT_CHARGE_EMPTY;
	}

	// Check Hate
	if(m_pOwner->GetStat()->iHate < 20 * (1.0f - m_pOwner->GetReducedHateConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("증오가 부족합니다."));
		return SLOT_RESULT_HATE_EMPTY;
	}

	if (CInputMgr::GetInstance()->GetPickPos() == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
		return SLOT_RESULT_ERROR_PICK;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Dir
	D3DXVECTOR3 vDir = *CInputMgr::GetInstance()->GetPickPos() - m_pTransformCom->m_vPos;
	D3DXVec3Normalize(&vDir, &vDir);

	// DotX
	float fDotX = D3DXVec3Dot(&-m_pTransformCom->m_vAxisX, &vDir);
	fDotX = RevisionDot(fDotX);

	// DotZ
	float fDotZ = D3DXVec3Dot(&-m_pTransformCom->m_vAxisZ, &vDir);
	fDotZ = RevisionDot(fDotZ);

	if(fDotX > 0.0f)
		m_pTransformCom->m_vAngle.y += acosf(fDotZ);
	else
		m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
	// Charge
	--m_iCharge;

	// Stat
	m_pOwner->GetStat()->iHate -= int(20 * (1.0f - m_pOwner->GetReducedHateConsumption()));

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SENTRY.ogg"));

	// Mode
	m_iMode = _iMode;

	vector<CObject*> vecFindObject;
	m_pOwner->GetLayer()->FindObjects(vecFindObject, _T("Sentry"), LAYER_TYPE_EFFECT);

	if(vecFindObject.size() >= 2)
		((CDemonHunter_Sentry_SentryEffect*)vecFindObject[0])->SentryDestory();

	CDemonHunter_Sentry_SentryEffect* pSentryEffect = new CDemonHunter_Sentry_SentryEffect(_T("Sentry"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pSentryEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pSentryEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = *CInputMgr::GetInstance()->GetPickPos();
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
	pSentryEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterSentrySlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterSentrySlot::End()
{
	return SLOT_RESULT_NULL;
}
