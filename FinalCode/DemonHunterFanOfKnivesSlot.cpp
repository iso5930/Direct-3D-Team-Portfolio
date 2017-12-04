#include "StdAfx.h"
#include "DemonHunterFanOfKnivesSlot.h"

CDemonHunterFanOfKnivesSlot::CDemonHunterFanOfKnivesSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_DEMONHUNTER_DEVICES;

	// SlotID
	m_eSlotID = SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES;

	// CooldownTime
	m_fCooldownTime = 10.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// Range
	m_fRange = 9999.f;

}

CDemonHunterFanOfKnivesSlot::~CDemonHunterFanOfKnivesSlot()
{
}

SLOT_RESULT CDemonHunterFanOfKnivesSlot::Begin(int _iMode)
{
	// Check Enable
	if(!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
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

		CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("FAN_OF_KNIVES.ogg"));

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

	// Mode
	m_iMode = _iMode;

	for(int i = 0; i < 16; ++i)
	{
		float fAngle = (22.5f * i);

		D3DXVECTOR3 vKnivesDir(0.f, 0.f, 1.f);

		D3DXMATRIX matRotY;
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(fAngle));
		D3DXVec3TransformCoord(&vKnivesDir, &vKnivesDir, &matRotY);

		CDemonHunter_FanOfKnives_KnivesEffect* pEffect = new CDemonHunter_FanOfKnives_KnivesEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner, &(vKnivesDir * 1000.f));
		m_pOwner->GetLayer()->AddObject(pEffect, LAYER_TYPE_EFFECT);

		CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
		pTransformCom->m_vPos = m_pTransformCom->m_vPos + D3DXVECTOR3(0.f, 60.f, 0.f) + vKnivesDir * 30.f;
		pTransformCom->m_vAngle.y = D3DXToRadian(fAngle);
		pTransformCom->m_vAngle.x = D3DXToRadian(180.f);
		pEffect->Initialize();
	}

	CDemonHunter_FanOfKnives_DecalEffect* pEffect = new CDemonHunter_FanOfKnives_DecalEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pEffect, LAYER_TYPE_EFFECT);

	CTransformCom* pTransformCom = (CTransformCom*)pEffect->GetComponent(COM_TYPE_TRANSFORM);
	pTransformCom->m_vPos = m_pTransformCom->m_vPos;
	pEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterFanOfKnivesSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CDemonHunterFanOfKnivesSlot::End()
{
	return SLOT_RESULT_NULL;
}