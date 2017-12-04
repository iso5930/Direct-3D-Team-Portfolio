#include "StdAfx.h"
#include "WizardElectrocuteSlot.h"

CWizardElectrocuteSlot::CWizardElectrocuteSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_ELECTROCUTE;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// TickTime
	m_fTickTime =  0.0f;

	// Range
	m_fRange = 9999.f;

	m_iSoundNum = 0;
}

CWizardElectrocuteSlot::~CWizardElectrocuteSlot()
{

}

SLOT_RESULT CWizardElectrocuteSlot::Begin(int _iMode)
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

	m_iSoundNum = CSoundMgr::GetInstance()->PlaySoundForPlayerBGM(_T("ELECTROCUTE_Loop.ogg"));

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

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardElectrocuteSlot::Action()
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

	m_fTickTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fTickTime > 0.05f)
	{
		m_fTickTime = 0.f;

		D3DXVECTOR3 vLightDir = vPos - (m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f));
		float fDist = D3DXVec3Length(&vLightDir);
		D3DXVec3Normalize(&vLightDir, &vLightDir);

		float fAngle = D3DXVec3Dot(&vLightDir, &vDir);
		fAngle = acosf(fAngle);

		CWizard_Electrocute_LightningEffect* pLightningEffect = new CWizard_Electrocute_LightningEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pLightningEffect, LAYER_TYPE_EFFECT);
		
		CTransformCom* pTransformCom = (CTransformCom*)pLightningEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f) + vLightDir * fDist / 2.f; 
		pTransformCom->m_vAngle.x = D3DXToRadian(90.f) - fAngle;
		pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
		pTransformCom->m_vSize.y = fDist;
		pLightningEffect->Initialize();

		//번개 생성.
		CWizard_Electrocute_HitEffect* pHitEffect = new CWizard_Electrocute_HitEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pHitEffect, LAYER_TYPE_EFFECT);

		pTransformCom = (CTransformCom*)pHitEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos + D3DXVECTOR3(0.f, 1.f, 0.f);
		pTransformCom->m_vAngle.x = D3DXToRadian(90.f);
		pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
		pHitEffect->Initialize();
	}

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardElectrocuteSlot::End()
{

	CSoundMgr::GetInstance()->StopSoundForPlayerBGM(m_iSoundNum);

	return SLOT_RESULT_NULL;
}
