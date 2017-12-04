#include "StdAfx.h"
#include "DemonHunterCaltropsSlot.h"

CDemonHunterCaltropsSlot::CDemonHunterCaltropsSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_DEFENSIVE;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_CALTROPS;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterCaltropsSlot::~CDemonHunterCaltropsSlot()
{
}

SLOT_RESULT CDemonHunterCaltropsSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Control
	if(m_pOwner->GetStat()->iControl < 6 * (1.0f - m_pOwner->GetReducedControlConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ �����մϴ�."));
		return SLOT_RESULT_CONTROL_EMPTY;
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("CALTROPS.ogg"));

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

	// Control
	m_pOwner->GetStat()->iControl -= int(6 * (1.0f - m_pOwner->GetReducedControlConsumption()));

	CDemonHunter_Caltrops_DecalEffect* pDecalEffect = new CDemonHunter_Caltrops_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDecalEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pDecalEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pDecalEffect->Initialize();

	CDemonHunter_Caltrops_SpikeEffect* pSpikeEffect = new CDemonHunter_Caltrops_SpikeEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pSpikeEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pSpikeEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pSpikeEffect->Initialize();

	CDemonHunter_Caltrops_FireEffect* pFireEffect = new CDemonHunter_Caltrops_FireEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pFireEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pFireEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 30.f, 0.f);
	pFireEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterCaltropsSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterCaltropsSlot::End()
{
	return SLOT_RESULT_NULL;
}
