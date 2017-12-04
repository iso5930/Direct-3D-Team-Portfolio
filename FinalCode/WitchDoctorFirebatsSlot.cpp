#include "StdAfx.h"
#include "WitchDoctorFirebatsSlot.h"

CWitchDoctorFirebatsSlot::CWitchDoctorFirebatsSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_FIREBATS;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// TickTime
	m_fTickTime = 0.0f;

	m_fEffectTime = 0.0f;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorFirebatsSlot::~CWitchDoctorFirebatsSlot()
{
}

SLOT_RESULT CWitchDoctorFirebatsSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Mana
	if (m_pOwner->GetStat()->iMana < 125 * (1.0f - m_pOwner->GetReducedManaConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("마나가 부족합니다."));
		return SLOT_RESULT_MANA_EMPTY;
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

	// Mana
	m_pOwner->GetStat()->iMana -= int(125 * (1.0f - m_pOwner->GetReducedManaConsumption()));

	m_fTickTime = 0.0f;

	CWitchDoctor_FireBatsEffect* pFireBatstEffect = new CWitchDoctor_FireBatsEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vDir);
	m_pOwner->GetLayer()->AddObject(pFireBatstEffect, LAYER_TYPE_EFFECT);

	Bone WeaponBone;		
	ZeroMemory(&WeaponBone , sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
	WeaponBone.mWorld = WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pFireBatstEffect->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pTransformCom->m_vPos.y += 100.f;
	pTransformCom->m_vAngle.x += D3DX_PI / 2.f ;  
	pTransformCom->m_vAngle.z += 1.57f;  

	pFireBatstEffect->Initialize();



	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorFirebatsSlot::Action()
{
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
	
	// TickTime
	m_fTickTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if (m_fTickTime > 0.5f)
	{
		m_fTickTime = 0.0f;

		// Check Mana
		if (m_pOwner->GetStat()->iMana < 62 * (1.0f - m_pOwner->GetReducedManaConsumption()))
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("마나가 부족합니다."));
			return SLOT_RESULT_MANA_EMPTY;
		}

		// Mana
		m_pOwner->GetStat()->iMana -= int(62 * (1.0f - m_pOwner->GetReducedManaConsumption()));
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
	
	m_fEffectTime += CTimeMgr::GetInstance()->GetDeltaTime();

	if (m_fEffectTime >= 0.05f)
	{
		m_fEffectTime = 0.0f;
 		D3DXMATRIX metTemp ;
 		D3DXMatrixIsIdentity(&metTemp);
 		D3DXMatrixRotationY(&metTemp ,D3DXToRadian(rand() % 20 - 10));
	 	
 		D3DXVec3TransformNormal(&vDir , &vDir , &metTemp);

		CWitchDoctor_FireBatsEffect* pFireBatstEffect = new CWitchDoctor_FireBatsEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, vDir);
		m_pOwner->GetLayer()->AddObject(pFireBatstEffect, LAYER_TYPE_EFFECT);

		Bone WeaponBone;		
		ZeroMemory(&WeaponBone , sizeof(Bone));
		CDynamicMesh* pDynamicMesh = NULL;

		CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
		pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
		WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
		WeaponBone.mWorld = WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

		// TransformCom
		CTransformCom* pTransformCom = (CTransformCom*)pFireBatstEffect->GetComponent(COM_TYPE_TRANSFORM);
		D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
		//pTransformCom->m_vPos = m_pTransformCom->m_vPos ;
		//pTransformCom->m_vPos.y += 100.f;

		pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;
		pTransformCom->m_vAngle.x += D3DX_PI / 2.f ;  
		
		pFireBatstEffect->Initialize();
	}


	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorFirebatsSlot::End()
{
	return SLOT_RESULT_NULL;
}
