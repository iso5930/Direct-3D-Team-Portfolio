#include "StdAfx.h"
#include "DemonHunterSpikeTrapSlot.h"

CDemonHunterSpikeTrapSlot::CDemonHunterSpikeTrapSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_DEVICES;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_SPIKE_TRAP;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterSpikeTrapSlot::~CDemonHunterSpikeTrapSlot()
{
}

SLOT_RESULT CDemonHunterSpikeTrapSlot::Begin(int _iMode)
{
	// Check Enable
	if(!m_bEnable)
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

	// Check Hate
	if(m_pOwner->GetStat()->iHate < 14 * (1.0f - m_pOwner->GetReducedHateConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ �����մϴ�."));
		return SLOT_RESULT_HATE_EMPTY;
	}

	// Begin
	CSlot::Begin(_iMode);


	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("CALTROPS.ogg"));


	// Hate
	m_pOwner->GetStat()->iHate -= int(14 * (1.0f - m_pOwner->GetReducedHateConsumption()));

	// Dir
	D3DXVECTOR3 vDir = vPos - m_pTransformCom->m_vPos;
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

		
	CDemonHunter_SpikeTrap_TrapEffect* pTrapEffect = new CDemonHunter_SpikeTrap_TrapEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pTrapEffect, LAYER_TYPE_EFFECT);
	
	CTransformCom* pTransformCom = (CTransformCom*)pTrapEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = vPos;
	pTrapEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterSpikeTrapSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterSpikeTrapSlot::End()
{
	return SLOT_RESULT_NULL;
}
