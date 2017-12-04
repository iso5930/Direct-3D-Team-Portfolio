#include "StdAfx.h"
#include "DemonHunterEvasiveFireSlot.h"

CDemonHunterEvasiveFireSlot::CDemonHunterEvasiveFireSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_EVASIVE_FIRE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterEvasiveFireSlot::~CDemonHunterEvasiveFireSlot()
{
}

SLOT_RESULT CDemonHunterEvasiveFireSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
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
		CUIMgr::GetInstance()->CreateTextMessage(_T("다른 무기가 필요합니다."));	
		return SLOT_RESULT_IMPOSSIBLE_WEAFON;
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("EVASIVE_FIRE.ogg"));


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

	// Mode
	m_iMode = _iMode;

	// Hate
	m_pOwner->GetStat()->iHate += 4;
	if(m_pOwner->GetStat()->iHate > m_pOwner->GetStat()->iMaxHate)
		m_pOwner->GetStat()->iHate = m_pOwner->GetStat()->iMaxHate;

	// FarAttackArrowEffect
	CDemonHunter_FarAttack_ArrowEffect* pFarAttackArrowEffect = new CDemonHunter_FarAttack_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir * 1000.0f));
	m_pOwner->GetLayer()->AddObject(pFarAttackArrowEffect, LAYER_TYPE_EFFECT);


	Bone WeaponBone;
	switch(m_iMode)
	{
	case 0:
		Mode0(WeaponBone);
		break;

	case 1:
		Mode1(WeaponBone);
		break;
	}
	
	//Arrow
	CDemonHunter_EvasiveFire_ArrowEffect* pArrowEffect = new CDemonHunter_EvasiveFire_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y;
	pArrowEffect->Initialize();

	//Arrow
	pArrowEffect = new CDemonHunter_EvasiveFire_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	// TransformCom
	pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y + D3DXToRadian(22.5f);
	pArrowEffect->Initialize();

	//Arrow
	pArrowEffect = new CDemonHunter_EvasiveFire_ArrowEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pArrowEffect, LAYER_TYPE_EFFECT);

	// TransformCom
	pTransformCom = (CTransformCom*)pArrowEffect->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y + D3DXToRadian(-22.5f);
	pArrowEffect->Initialize();

	/*
	//Effect
	float fDist = 700.f;

	vector<CObject*> vecFindMonster;
	m_pOwner->GetLayer()->FindObjects(vecFindMonster, _T("Monster"), LAYER_TYPE_MONSTER);

	for(size_t i = 0; i < vecFindMonster.size(); ++i)
	{
		CTransformCom* pMonsterInfo = (CTransformCom*)vecFindMonster[i]->GetComponent(COM_TYPE_TRANSFORM);
		
		D3DXVECTOR3 vDist = pMonsterInfo->m_vPos - m_pTransformCom->m_vPos;

		float fLenght = D3DXVec3Length(&vDist);
	}
	*/

	CDemonHunter_EvasiveFire_DummyEffect* pDummyEffect = new CDemonHunter_EvasiveFire_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);

	pTransformCom = (CTransformCom*)pDummyEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + vDir * 100.f;
	pDummyEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterEvasiveFireSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterEvasiveFireSlot::End()
{
	return SLOT_RESULT_NULL;
}

void CDemonHunterEvasiveFireSlot::Mode0(Bone& _WeaponBone)
{
	ZeroMemory(&_WeaponBone , sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "right_weapon");
	_WeaponBone.mWorld = _WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
}

void CDemonHunterEvasiveFireSlot::Mode1(Bone& _WeaponBone)
{
	ZeroMemory(&_WeaponBone , sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	_WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
	_WeaponBone.mWorld = _WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;
}