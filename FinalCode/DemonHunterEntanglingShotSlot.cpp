#include "StdAfx.h"
#include "DemonHunterEntanglingShotSlot.h"

CDemonHunterEntanglingShotSlot::CDemonHunterEntanglingShotSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterEntanglingShotSlot::~CDemonHunterEntanglingShotSlot()
{
}

SLOT_RESULT CDemonHunterEntanglingShotSlot::Begin(int _iMode)
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

	// Begin
	CSlot::Begin(_iMode);

	// Hate
	m_pOwner->GetStat()->iHate += 4;
	if(m_pOwner->GetStat()->iHate > m_pOwner->GetStat()->iMaxHate)
		m_pOwner->GetStat()->iHate = m_pOwner->GetStat()->iMaxHate;

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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("ArrowAttack.ogg"));


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

	Bone WeaponBone; 

	CDemonHunter_EntanglingShot_ArrowEffect* pEntanglingShot_ArrowEffect = new CDemonHunter_EntanglingShot_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.0f));
	m_pOwner->GetLayer()->AddObject(pEntanglingShot_ArrowEffect, LAYER_TYPE_EFFECT);

	// Mode
	m_iMode = _iMode;

	switch(m_iMode)
	{
	case 0:
		Mode0(WeaponBone);
		break;
	case 1:
		Mode1(WeaponBone);
		break;
	}

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pEntanglingShot_ArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vPos = pTransformCom->m_vPos + (vDir);
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
	pEntanglingShot_ArrowEffect->Initialize();

	
	CDemonHunter_EntanglingShot_ArrowDistortionEffect* pDistortionEffect = new CDemonHunter_EntanglingShot_ArrowDistortionEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDistortionEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pDistortionEffect->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vPos = pTransformCom->m_vPos + (vDir * 10.f) + D3DXVECTOR3(0.f, 15.f, 0.f);
	pDistortionEffect->Initialize();
	

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterEntanglingShotSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterEntanglingShotSlot::End()
{
	return SLOT_RESULT_NULL;
}

void CDemonHunterEntanglingShotSlot::Mode0(Bone& _WeaponBone)
{
	// AxisZ
	ZeroMemory(&_WeaponBone , sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
	_WeaponBone.mWorld = _WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
}

void CDemonHunterEntanglingShotSlot::Mode1(Bone& _WeaponBone)
{
	ZeroMemory(&_WeaponBone , sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
	_WeaponBone.mWorld = _WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
}