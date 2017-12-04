#include "StdAfx.h"
#include "BarbarianWhirlwindSlot.h"

CBarbarianWhirlwindSlot::CBarbarianWhirlwindSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_BARBARIAN_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_BARBARIAN_WHIRLWIND;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = 0.0f;

	// Range
	m_fRange = 9999.f;

}

CBarbarianWhirlwindSlot::~CBarbarianWhirlwindSlot()
{
}

SLOT_RESULT CBarbarianWhirlwindSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Rage
	if(m_pOwner->GetStat()->iRage < 10 * (1.0f - m_pOwner->GetReducedRageConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("�г밡 ���� �մϴ�."));
		return SLOT_RESULT_RAGE_EMPTY;
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

	// Rage
	m_pOwner->GetStat()->iRage -= int(10 * (1.0f - m_pOwner->GetReducedRageConsumption()));

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianWhirlwindSlot::Action()
{
	CSlot::Action();
	
	// Check Pick
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();


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

	// Check Rage
	if(m_fTime > 0.5f)
	{
		m_fTime = 0.0f;

		if(m_pOwner->GetStat()->iRage < 5 * (1.0f - m_pOwner->GetReducedRageConsumption()))
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("�г밡 ���� �մϴ�."));
			return SLOT_RESULT_RAGE_EMPTY;
		}

		m_pOwner->GetStat()->iRage -= int(5 * (1.0f - m_pOwner->GetReducedRageConsumption()));
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

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CBarbarianWhirlwindSlot::End()
{
	return SLOT_RESULT_NULL;
}