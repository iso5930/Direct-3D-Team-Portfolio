#include "StdAfx.h"
#include "DemonHunterClusterArrowSlot.h"

CDemonHunterClusterArrowSlot::CDemonHunterClusterArrowSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_ARCHERY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_CLUSTER_ARROW;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = 0.0f;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterClusterArrowSlot::~CDemonHunterClusterArrowSlot()
{
}

SLOT_RESULT CDemonHunterClusterArrowSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Weapon
	bool bCheckWeapon = false;
	DWORD dwBow = WEAPON_ID_BOW | WEAPON_ID_CROSSBOW | WEAPON_ID_HANDXBOW;

	if(CItemMgr::GetInstance()->GetItemInEquip(9) != NULL && (CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & dwBow))
		bCheckWeapon = true;
	else if(CItemMgr::GetInstance()->GetItemInEquip(11) != NULL && (CItemMgr::GetInstance()->GetItemInEquip(11)->dwItemID & dwBow))
		bCheckWeapon = true;

	if(bCheckWeapon == false)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("�ٸ� ���Ⱑ �ʿ��մϴ�."));	
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
	}

	// Check Hate
	if(m_pOwner->GetStat()->iHate < 40 * (1.0f - m_pOwner->GetReducedHateConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ �����մϴ�."));
		return SLOT_RESULT_HATE_EMPTY;
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


	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("CLUSTER_ARROW.ogg"));

	// Dir
	D3DXVECTOR3 vDir = vPos - m_pTransformCom->m_vPos;
	D3DXVECTOR3 vNewDir = vDir;
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVec3Normalize(&vNewDir, &vNewDir);


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
	m_pOwner->GetStat()->iHate -= int(40 * (1.0f - m_pOwner->GetReducedHateConsumption()));	

	//3�� ����.
		
	CDemonHunter_ClusterArrow_ArrowEffect* pArrowEffect = new CDemonHunter_ClusterArrow_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, CInputMgr::GetInstance()->GetPickPos());
	m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 80.f, 0.f);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pArrowEffect->Initialize();

	pArrowEffect = new CDemonHunter_ClusterArrow_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, CInputMgr::GetInstance()->GetPickPos());
	m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 70.f, 0.f) - (vNewDir * 50.f);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pArrowEffect->Initialize();

	pArrowEffect = new CDemonHunter_ClusterArrow_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, CInputMgr::GetInstance()->GetPickPos());
	m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 90.f, 0.f) - (vNewDir * 60.f);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pArrowEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterClusterArrowSlot::Action()
{
	

	return SLOT_RESULT_NULL;

}

SLOT_RESULT CDemonHunterClusterArrowSlot::End()
{
	return SLOT_RESULT_NULL;
}
