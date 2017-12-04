#include "StdAfx.h"
#include "BarbarianLeapSlot.h"

CBarbarianLeapSlot::CBarbarianLeapSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_LEAP;

	// CooldownTime
	m_fCooldownTime = 10.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CBarbarianLeapSlot::~CBarbarianLeapSlot()
{
}

SLOT_RESULT CBarbarianLeapSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	if (CInputMgr::GetInstance()->GetPickPos() == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));
		return SLOT_RESULT_ERROR_PICK;
	}

	// Check Rage
	if(m_pOwner->GetStat()->iRage < 15 * (1.0f - m_pOwner->GetReducedRageConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("분노가 부족 합니다."));
		return SLOT_RESULT_RAGE_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Rage
	m_pOwner->GetStat()->iRage -= int(15 * (1.0f - m_pOwner->GetReducedRageConsumption()));

	// Dir
	D3DXVECTOR3 vDir =  *CInputMgr::GetInstance()->GetPickPos() - m_pTransformCom->m_vPos;
	vDir.y = 0.0f;
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

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianLeapSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianLeapSlot::End()
{
	return SLOT_RESULT_NULL;
}
