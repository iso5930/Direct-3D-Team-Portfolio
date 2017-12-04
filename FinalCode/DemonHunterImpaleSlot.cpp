#include "StdAfx.h"
#include "DemonHunterImpaleSlot.h"

CDemonHunterImpaleSlot::CDemonHunterImpaleSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_IMPALE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterImpaleSlot::~CDemonHunterImpaleSlot()
{
}

SLOT_RESULT CDemonHunterImpaleSlot::Begin(int _iMode)
{
	// Check Enable
	if(!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Hate
	if(m_pOwner->GetStat()->iHate < 20 * (1.0f - m_pOwner->GetReducedHateConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("증오가 부족합니다."));
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("IMPALE.ogg"));



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
	m_pOwner->GetStat()->iHate -= int(20 * (1.0f - m_pOwner->GetReducedHateConsumption()));

	// Mode
	m_iMode = _iMode;

	//KnivesEffect
	CDemonHunter_Impale_KnivesEffect* pKnivesEffect = new CDemonHunter_Impale_KnivesEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, D3DXVECTOR3(vDir * 1000.f));
	m_pOwner->GetLayer()->AddObject(pKnivesEffect, LAYER_TYPE_EFFECT);
	
	//Transform
	CTransformCom* pTransformCom = (CTransformCom*)pKnivesEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.0f, 70.0f, 0.0f);
	pTransformCom->m_vAngle.y = m_pTransformCom->m_vAngle.y/* - D3DXToRadian(90.f)*/;
	
	pKnivesEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterImpaleSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterImpaleSlot::End()
{
	return SLOT_RESULT_NULL;
}
