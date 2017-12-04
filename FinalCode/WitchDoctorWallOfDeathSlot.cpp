#include "StdAfx.h"
#include "WitchDoctorWallOfDeathSlot.h"

CWitchDoctorWallOfDeathSlot::CWitchDoctorWallOfDeathSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_DECAY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH;

	// CooldownTime
	m_fCooldownTime = 8.f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorWallOfDeathSlot::~CWitchDoctorWallOfDeathSlot()
{
}

SLOT_RESULT CWitchDoctorWallOfDeathSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	if(CInputMgr::GetInstance()->GetPickPos() == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
		return SLOT_RESULT_ERROR_PICK;
	}

	// Begin
	CSlot::Begin(_iMode);

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

SLOT_RESULT CWitchDoctorWallOfDeathSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorWallOfDeathSlot::End()
{
	return SLOT_RESULT_NULL;
}
