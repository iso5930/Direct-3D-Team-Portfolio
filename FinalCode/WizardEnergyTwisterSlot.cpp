#include "StdAfx.h"
#include "WizardEnergyTwisterSlot.h"

CWizardEnergyTwisterSlot::CWizardEnergyTwisterSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WIZARD_FORCE;

	// SlotID
	m_eSlotID = SLOT_ID_WIZARD_ENERGY_TWISTER;

	// ColldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWizardEnergyTwisterSlot::~CWizardEnergyTwisterSlot()
{
}

SLOT_RESULT CWizardEnergyTwisterSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Vision
	if (m_pOwner->GetStat()->iVision < 16 * (1.0f - m_pOwner->GetReducedVisionConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("�������� �����մϴ�."));
		return SLOT_RESULT_VISION_EMPTY;
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("ENERGY_TWISTER1.ogg"));
	CSoundMgr::GetInstance()->PlaySoundForPlayerSkill(_T("ENERGY_TWISTER2.ogg"));

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

	// Vision
	m_pOwner->GetStat()->iVision -= int(16 * (1.0f - m_pOwner->GetReducedVisionConsumption()));


	CWizard_EnergyTwister_TornadoEffect* pTornadoEffect = new CWizard_EnergyTwister_TornadoEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 100.f));
	m_pOwner->GetLayer()->AddObject(pTornadoEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pTornadoEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vPos;
	pTornadoEffect->Initialize();
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardEnergyTwisterSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWizardEnergyTwisterSlot::End()
{
	return SLOT_RESULT_NULL;
}
