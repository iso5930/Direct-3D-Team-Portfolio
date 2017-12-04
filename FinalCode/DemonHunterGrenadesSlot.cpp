#include "StdAfx.h"
#include "DemonHunterGrenadesSlot.h"

CDemonHunterGrenadesSlot::CDemonHunterGrenadesSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_GRENADES;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterGrenadesSlot::~CDemonHunterGrenadesSlot()
{
}

SLOT_RESULT CDemonHunterGrenadesSlot::Begin(int _iMode)
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

	// Begin
	CSlot::Begin(_iMode);

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("GRENADES.ogg"));


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

	// Hate
	m_pOwner->GetStat()->iHate += 4;
	if(m_pOwner->GetStat()->iHate > m_pOwner->GetStat()->iMaxHate)
		m_pOwner->GetStat()->iHate = m_pOwner->GetStat()->iMaxHate;

	CDemonHunter_Grenades_GrenadesEffect* pGrenadesEffect = new CDemonHunter_Grenades_GrenadesEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vPos);
	m_pOwner->GetLayer()->AddObject(pGrenadesEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pGrenadesEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f);
	pGrenadesEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterGrenadesSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterGrenadesSlot::End()
{
	return SLOT_RESULT_NULL;
}
