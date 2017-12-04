#include "StdAfx.h"
#include "MonkDashingStrikeSlot.h"

CMonkDashingStrikeSlot::CMonkDashingStrikeSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_TECHNIQUES;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_DASHING_STRIKE;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// ChargeTime 
	m_fChargeTime = 8.0f;

	// MaxCharge
	m_iMaxCharge = 2;

	// Charge
	m_iCharge = 0;

	// Range
	m_fRange = 9999.f;

}

CMonkDashingStrikeSlot::~CMonkDashingStrikeSlot()
{

}

SLOT_RESULT CMonkDashingStrikeSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Charge
	if (m_iCharge <= 0)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("이 기술을 사용하려면 충전이 필요합니다."));
		return SLOT_RESULT_CHARGE_EMPTY;
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

	CSoundMgr::GetInstance()->PlaySoundForPlayer(_T("DASHING_STRIKE.ogg"));

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
		
	// Begin
	CSlot::Begin(_iMode);

	// Charge
	--m_iCharge;

	CMonk_DashingStrike_DummyEffect* pDummyEffect = new CMonk_DashingStrike_DummyEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(pDummyEffect, LAYER_TYPE_EFFECT);
	pDummyEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkDashingStrikeSlot::Action()
{
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkDashingStrikeSlot::End()
{
	return SLOT_RESULT_NULL;
}
