#include "StdAfx.h"
#include "WizardSlowTimeSlot.h"

CWizardSlowTimeSlot::CWizardSlowTimeSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_SLOW_TIME;

	// ColldownTime
	m_fCooldownTime = 15.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardSlowTimeSlot::~CWizardSlowTimeSlot()
{
}

SLOT_RESULT CWizardSlowTimeSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
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
			CUIMgr::GetInstance()->CreateTextMessage(_T("유효하지 않은 지역입니다."));	
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SLOW_TIME.ogg"));

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

	CWizard_SlowTime_AreaEffect* pAreaEffect = new CWizard_SlowTime_AreaEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pAreaEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTansformCom = (CTransformCom*)pAreaEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTansformCom->m_vPos = vPos;
	pTansformCom->m_vSize = D3DXVECTOR3(2.f, 2.f, 2.f);
	pAreaEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardSlowTimeSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardSlowTimeSlot::End()
{
	return SLOT_RESULT_NULL;
}
