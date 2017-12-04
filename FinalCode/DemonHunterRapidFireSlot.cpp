#include "StdAfx.h"
#include "DemonHunterRapidFireSlot.h"

CDemonHunterRapidFireSlot::CDemonHunterRapidFireSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_RAPID_FIRE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = 0.0f;

	// TickTime;
	m_fTickTime = 0.0f;

	// ����Ʈ ���� �ð�
	m_fCreateTime = 0.0f;

	// Range
	m_fRange = 9999.f;

	m_vPos = D3DXVECTOR3(0.f ,0.f ,0.f);

}

CDemonHunterRapidFireSlot::~CDemonHunterRapidFireSlot()
{
}

SLOT_RESULT CDemonHunterRapidFireSlot::Begin(int _iMode)
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
	if(m_pOwner->GetStat()->iHate < 20 * (1.0f - m_pOwner->GetReducedHateConsumption()))
	{
		
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ �����մϴ�."));
		return SLOT_RESULT_HATE_EMPTY;
	}

	// Check Pick
	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			m_vPos =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("��ȿ���� ���� �����Դϴ�."));	
			return SLOT_RESULT_ERROR_PICK;
		}
		else
			m_vPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		m_vPos = pTransformCom->m_vPos;
	}

	// Begin
	CSlot::Begin(_iMode);

	// Mode
	m_iMode = _iMode;

	// Hate
	m_pOwner->GetStat()->iHate -= int(20 * (1.0f - m_pOwner->GetReducedHateConsumption()));

	// TickTime
	m_fTickTime = 0.0f ;

	switch(m_iMode)
	{
	case 0:
		Mode0(); // ������
		break;

	case 1:
		Mode1(); // �޼�
		break;
	}
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterRapidFireSlot::Action()
{
	if(!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("������ ��� �� �� �����ϴ�."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	m_fTickTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if (CItemMgr::GetInstance()->GetItemInEquip(9) == NULL)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("�ٸ� ���Ⱑ �ʿ��մϴ�."));	
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
	}

	if(!(CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID == WEAPON_ID_BOW || CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID == WEAPON_ID_CROSSBOW || CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID == WEAPON_ID_HANDXBOW ))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("�ٸ� ���Ⱑ �ʿ��մϴ�."));	
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
	}
	
	// Check Pick
	if(m_pOwner->GetPickObject() == NULL)
	{
		CObject* pFind = NULL;
		CMouse*	pMouse = NULL;
		m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
		pMouse = (CMouse*)pFind;

		if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransformCom = (CTransformCom*)pMouse->GetOverObject() ->GetComponent(COM_TYPE_TRANSFORM);
			m_vPos =  pTransformCom->m_vPos;
		}
		else if (CInputMgr::GetInstance()->GetPickPos() == NULL)
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("��ȿ���� ���� �����Դϴ�."));	
			return SLOT_RESULT_ERROR_PICK;
		}
		else
			m_vPos = *CInputMgr::GetInstance()->GetPickPos();
	}
	else
	{
		CTransformCom* pTransformCom = (CTransformCom*)m_pOwner->GetPickObject() ->GetComponent(COM_TYPE_TRANSFORM);
		m_vPos = pTransformCom->m_vPos;
	}

	// Check Hate
	if (m_fTickTime > 1.0f)
	{
		m_fTickTime = 0.f;

		if(m_pOwner->GetStat()->iHate < 3 * (1.0f - m_pOwner->GetReducedHateConsumption()))
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("������ �����մϴ�."));
			return SLOT_RESULT_HATE_EMPTY;
		}

		// Hate
		m_pOwner->GetStat()->iHate -= int(3 * (1.0f - m_pOwner->GetReducedHateConsumption()));
	}
	
	m_fCreateTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if(m_fCreateTime < 0.05f )
	{
		return SLOT_RESULT_NULL;
	}
	m_fCreateTime -= rand() % 50 / 1000.f; 

	switch(m_iMode)
	{
	case 0:
		Mode0(); // ������
		break;

	case 1:
		Mode1(); // �޼�
		break;
	}
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterRapidFireSlot::End()
{
	return SLOT_RESULT_NULL;
}

void CDemonHunterRapidFireSlot::Mode0( )
{

	// Dir
	D3DXVECTOR3 vDir = m_vPos - m_pTransformCom->m_vPos;
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

	CDemonHunter_RapidFire_ArrowEffect* pFarAttackArrowEffect = new CDemonHunter_RapidFire_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.0f));
	m_pOwner->GetLayer()->AddObject(pFarAttackArrowEffect, LAYER_TYPE_EFFECT);

	Bone WeaponBone; 
	ZeroMemory(&WeaponBone , sizeof(Bone));

	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	
	WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
	WeaponBone.mWorld = WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	D3DXVECTOR3 vRand = D3DXVECTOR3(0.f , 0.f , 0.f);
	vRand.x = rand() % 200 / 10.f - 10.0f;
	vRand.y = rand() % 200 / 10.f - 10.0f;

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pFarAttackArrowEffect->GetComponent(COM_TYPE_TRANSFORM);

	pTransformCom->m_vPos += vRand;
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vPos = pTransformCom->m_vPos + (vDir * 50);
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

	pFarAttackArrowEffect->Initialize();
}

void CDemonHunterRapidFireSlot::Mode1()
{

	// Dir
	D3DXVECTOR3 vDir = m_vPos - m_pTransformCom->m_vPos;
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

	CDemonHunter_RapidFire_ArrowEffect* pFarAttackArrowEffect = new CDemonHunter_RapidFire_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.0f));
	m_pOwner->GetLayer()->AddObject(pFarAttackArrowEffect, LAYER_TYPE_EFFECT);

	Bone WeaponBone; 
	ZeroMemory(&WeaponBone , sizeof(Bone));

	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];

	WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon"); 
	WeaponBone.mWorld = WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	D3DXVECTOR3 vRand = D3DXVECTOR3(0.f , 0.f , 0.f);
	vRand.x = rand() % 200 / 10.f - 10.0f;
	vRand.y = rand() % 200 / 10.f - 10.0f;

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pFarAttackArrowEffect->GetComponent(COM_TYPE_TRANSFORM);

	pTransformCom->m_vPos += vRand;
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vPos = pTransformCom->m_vPos + (vDir * 50);
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

	pFarAttackArrowEffect->Initialize();
}
