#include "StdAfx.h"
#include "WitchDoctorPoisonDartSlot.h"

CWitchDoctorPoisonDartSlot::CWitchDoctorPoisonDartSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_WITCHDOCTOR_PRIMARY;

	// SlotID
	m_eSlotID = SLOT_ID_WITCHDOCTOR_POISON_DART;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CWitchDoctorPoisonDartSlot::~CWitchDoctorPoisonDartSlot()
{
}

SLOT_RESULT CWitchDoctorPoisonDartSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	D3DXVECTOR3 vPos;
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
	
	CWitchDocter_PoionDartEffect* pPosionDartEffect = new CWitchDocter_PoionDartEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vDir));
	m_pOwner->GetLayer()->AddObject(pPosionDartEffect, LAYER_TYPE_EFFECT);

	Bone WeaponBone;		
	ZeroMemory(&WeaponBone , sizeof(Bone));
	CDynamicMesh* pDynamicMesh = NULL;

	CBufferCom* pBufferCom = (CBufferCom*)m_pOwner->GetComponent(COM_TYPE_BUFFER);
	pDynamicMesh = (CDynamicMesh*)pBufferCom->m_BufferVec[2];
	WeaponBone.pFrame = (MeshFrame*)D3DXFrameFind(pDynamicMesh->m_pRootFrame, "left_weapon");
	WeaponBone.mWorld = WeaponBone.pFrame->mCombinedMatrix * m_pTransformCom->m_mWorld;

	// TransformCom
	CTransformCom* pTransformCom = (CTransformCom*)pPosionDartEffect->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVec3TransformCoord(&pTransformCom->m_vPos  , &pTransformCom->m_vPos ,  &WeaponBone.mWorld);
	pTransformCom->m_vPos = pTransformCom->m_vPos + (vDir * 5) ;
	pTransformCom->m_vSize = D3DXVECTOR3(2.f , 2.f , 2.f) ;
	pTransformCom->m_vAngle = m_pTransformCom->m_vAngle;

	pPosionDartEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorPoisonDartSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CWitchDoctorPoisonDartSlot::End()
{
	return SLOT_RESULT_NULL;
}
