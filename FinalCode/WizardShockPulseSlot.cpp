#include "StdAfx.h"
#include "WizardShockPulseSlot.h"

CWizardShockPulseSlot::CWizardShockPulseSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_SHOCK_PULSE;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardShockPulseSlot::~CWizardShockPulseSlot()
{
}

SLOT_RESULT CWizardShockPulseSlot::Begin(int _iMode)
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("SHOCK_PULSE.ogg"));

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

	for(int i = 0; i < 3; ++i)
	{
		float fLenght = 500.f;
		float fAngle = D3DXToRadian(float(rand() % 90) - 45.f);

		D3DXVECTOR3 vDir2;
		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, fAngle);
		D3DXVec3TransformNormal(&vDir2, &vDir, &matRotY);
		D3DXVECTOR3 vDestPos = m_pTransformCom->m_vPos + (vDir2 * fLenght);

		CWizard_ShockPulse_DummyEffect* pDummyEffect = new CWizard_ShockPulse_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vDestPos);
		m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pDummyEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + (vDir2 * 10.f);
		pDummyEffect->Initialize();
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardShockPulseSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardShockPulseSlot::End()
{
	return SLOT_RESULT_NULL;
}
