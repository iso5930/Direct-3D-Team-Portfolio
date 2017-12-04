#include "StdAfx.h"
#include "WitchDoctorCorpseSpidersSlot.h"

CWitchDoctorCorpseSpidersSlot::CWitchDoctorCorpseSpidersSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorCorpseSpidersSlot::~CWitchDoctorCorpseSpidersSlot()
{
}

SLOT_RESULT CWitchDoctorCorpseSpidersSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Pick
	D3DXVECTOR3 vPos;
	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			vPos =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("��ȿ���� ���� �����Դϴ�."));	
			return SLOT_RESULT_ERROR_PICK;
		}
		else
			vPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		vPos = pTransformCom->m_vPos;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Dir
	D3DXVECTOR3 vDir = vPos - m_pTransformCom->m_vPos;
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

	CWitchDoctorCorpseSpidersEffect* pCorpseSpidersEffect = new	CWitchDoctorCorpseSpidersEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, *CInputMgr::GetInstance()->GetPickPos());
	m_pOwner->GetLayer()->AddObject(pCorpseSpidersEffect, LAYER_TYPE_EFFECT);


	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pCorpseSpidersEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vPos.y += 50.f;
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

	pCorpseSpidersEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorCorpseSpidersSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorCorpseSpidersSlot::End()
{
	return SLOT_RESULT_NULL;
}
