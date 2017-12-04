#include "StdAfx.h"
#include "MonkTempestRushSlot.h"

CMonkTempestRushSlot::CMonkTempestRushSlot()
{
	// SlotType
	m_eSlotType = SLOT_TYPE_MONK_SECONDARY;

	// SlotID
	m_eSlotID = SLOT_ID_MONK_TEMPEST_RUSH;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// Time
	m_fTime = m_fCooldownTime;

	// TickTime;
	m_fTickTime = 0.0f;

	// Range
	m_fRange = 9999.f;

	
	m_pStaffEffect = NULL;

	m_iSoundMgr = 0;

}

CMonkTempestRushSlot::~CMonkTempestRushSlot()
{
}

SLOT_RESULT CMonkTempestRushSlot::Begin(int _iMode)
{
	// Check Enable
	if (!m_bEnable)
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("아직은 사용 할 수 없습니다."));
		return SLOT_RESULT_COOLDOWN_TIEM;
	}

	// Check Effort
	if(m_pOwner->GetStat()->iEffort < 30 * (1.0f - m_pOwner->GetReducedEffortConsumption()))
	{
		CUIMgr::GetInstance()->CreateTextMessage(_T("공력이 부족합니다."));
		return SLOT_RESULT_EFFORT_EMPTY;
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

	m_iSoundMgr = CSoundMgr::GetInstance()->PlaySoundForPlayerBGM(_T("TEMPEST_RUSH_Loop.ogg"));



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

	// Effort
	m_pOwner->GetStat()->iEffort -= int(30 * (1.0f - m_pOwner->GetReducedEffortConsumption()));

	// TickTime
	m_fTickTime = 0.0f;


	m_pStaffEffect = new CMonk_TempestRush_StaffEffect(NULL, OBJ_TYPE_DYNAMIC, m_pOwner);
	m_pOwner->GetLayer()->AddObject(m_pStaffEffect, LAYER_TYPE_EFFECT);
	m_pStaffEffect->Initialize();

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkTempestRushSlot::Action()
{
	m_fTickTime += CTimeMgr::GetInstance()->GetDeltaTime();
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

	if (m_fTickTime > 0.5f)
	{
		m_fTickTime = 0.0f;

		if(m_pOwner->GetStat()->iEffort < 30 * (1.0f - m_pOwner->GetReducedEffortConsumption()))
		{
			CUIMgr::GetInstance()->CreateTextMessage(_T("공력이 부족합니다."));
			return SLOT_RESULT_EFFORT_EMPTY;
		}

		m_pOwner->GetStat()->iEffort -= int(30 * (1.0f - m_pOwner->GetReducedEffortConsumption()));
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
	
	return SLOT_RESULT_NULL;
}

SLOT_RESULT CMonkTempestRushSlot::End()
{
	m_fTickTime = 0.0f; 

	if(m_pStaffEffect != NULL)
	{
		m_pStaffEffect->Destroy();
		m_pStaffEffect = NULL;
	}

	CSoundMgr::GetInstance()->StopSoundForPlayerBGM(m_iSoundMgr);

	return SLOT_RESULT_NULL;
}
