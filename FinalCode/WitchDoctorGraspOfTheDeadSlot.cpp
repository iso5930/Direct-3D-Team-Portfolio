#include "StdAfx.h"
#include "WitchDoctorGraspOfTheDeadSlot.h"

CWitchDoctorGraspOfTheDeadSlot::CWitchDoctorGraspOfTheDeadSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD;

	// CooldownTime 
	m_fCooldownTime = 8.f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorGraspOfTheDeadSlot::~CWitchDoctorGraspOfTheDeadSlot()
{
}

SLOT_RESULT CWitchDoctorGraspOfTheDeadSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	if(CInputMgr::GetInstance()->GetPickPos() == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("��ȿ���� ���� �����Դϴ�."));	
		return SLOT_RESULT_ERROR_PICK;
	}

	// Check Mana
	if (m_pOwner->GetStat()->iMana < 150 * (1.0f - m_pOwner->GetReducedManaConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ �����մϴ�."));
		return SLOT_RESULT_MANA_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Mana
	m_pOwner->GetStat()->iMana -= int(150 * (1.0f - m_pOwner->GetReducedManaConsumption()));

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

SLOT_RESULT CWitchDoctorGraspOfTheDeadSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorGraspOfTheDeadSlot::End()
{
	return SLOT_RESULT_NULL;
}
