#include "StdAfx.h"
#include "WizardHydraSlot.h"

CWizardHydraSlot::CWizardHydraSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_FORCE;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_HYDRA;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}



CWizardHydraSlot::~CWizardHydraSlot()
{
}

SLOT_RESULT CWizardHydraSlot::Begin(int _iMode)
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

	// Check Vision
	if (m_pOwner->GetStat()->iVision < 15 * (1.0f - m_pOwner->GetReducedVisionConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("비전력이 부족합니다."));
		return SLOT_RESULT_VISION_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Vision
	m_pOwner->GetStat()->iVision -= int(15 * (1.0f - m_pOwner->GetReducedVisionConsumption()));

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("HYDRA.ogg"));

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

	vector<CObject*> vecFindObject;
	m_pOwner->GetLayer()->FindObjects(vecFindObject, _T("Hydra"), LAYER_TYPE_EFFECT);

	if(vecFindObject.size() != 0)
	{
		for(size_t i = 0; i < vecFindObject.size(); ++i)
		{
			((CWizard_Hydra_HydraEffect*)vecFindObject[i])->HydraDestory();
		}

		vecFindObject.clear();

		m_pOwner->GetLayer()->FindObjects(vecFindObject, _T("Hydra_Decal"), LAYER_TYPE_EFFECT);
		if(vecFindObject.size() != 0)
		{
			vecFindObject[0]->Destroy();
		}		
	}

	for(int i = 0; i < 3; ++i)
	{
		D3DXVECTOR3 vUp(1.f, 0.f, 0.f);
		float		fAngle = D3DXToRadian(i * 120.f);
		D3DXMATRIX	matRotY;
		D3DXMatrixRotationY(&matRotY, fAngle);
		D3DXVec3TransformNormal(&vUp, &vUp, &matRotY);

		CWizard_Hydra_HydraEffect* pHydraEffect = new CWizard_Hydra_HydraEffect(_T("Hydra"), OBJ_TYPE_DYNAMIC, m_pOwner);
		m_pOwner->GetLayer()->AddObject(pHydraEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pHydraEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = vPos + vUp * 40.f;
		pTransformCom->m_vAngle.y = fAngle - D3DXToRadian(90.f);
		pHydraEffect->Initialize();
	}

	CWizard_Hydra_FireDecalEffect* pDecalEffect = new CWizard_Hydra_FireDecalEffect(_T("Hydra_Decal"), OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vPos;
	pDecalEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardHydraSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardHydraSlot::End()
{
	return SLOT_RESULT_NULL;
}
