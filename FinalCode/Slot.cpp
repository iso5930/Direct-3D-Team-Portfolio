#include "StdAfx.h"
#include "Slot.h"

CSlot::CSlot()
{
	// Mode 
	m_iMode = 0;
	
	// Owner
	m_pOwner = NULL;

	// TransformCom
	m_pTransformCom = NULL;

	// SlotType
	m_eSlotType = SLOT_TYPE_END;

	// SlotID
	m_eSlotID = SLOT_ID_END;

	// Enable
	m_bEnable = true;

	// Time
	m_fTime = 0.0f;

	// CooldownTime
	m_fCooldownTime = 0.0f;

	// CooldownTime
	m_fChargingTime = 0.0f;

	// ChargeTime
	m_fChargeTime = 0.0f;

	// Charge
	m_iCharge = 0;

	// MaxCharge
	m_iMaxCharge = 0;

	// Range 
	m_fRange = 0.f;
	
}

CSlot::~CSlot()
{
}


SLOT_RESULT CSlot::Begin(int _iMode)
{
	m_fTime = 0.0f;
	m_bEnable = false;

	return SLOT_RESULT_NULL;
}

SLOT_RESULT CSlot::Action()
{
	return SLOT_RESULT_NULL;
}

void CSlot::SetOwner(CPlayer* _pOwner)
{
	m_pOwner = _pOwner;
	m_pTransformCom = (CTransformCom*)m_pOwner->GetComponent(COM_TYPE_TRANSFORM);
}

float CSlot::GetCooldownTime()
{
	return m_fCooldownTime * m_pOwner->GetReducedCooldownTime();
}

float CSlot::GetRange()
{
	if(true == (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
	{
		return 9999.f;
	}
	else
	{
		if (m_pOwner->GetPickType() == MOUSE_OVER_TYPE_MONSTER)
		{
			if (m_pOwner->GetPickObject()->IsDestroy())
			{
				return 9999.f;
			}

			CCollisionCom* pCollCom =  (CCollisionCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_COLLISION);
			if (pCollCom == NULL)
			{
				m_pOwner->SetPickObject(NULL);
				m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE);
				return 1.f ;
			}
			return m_fRange + pCollCom->m_pCollisionSphere->fRadius ;
		}
		else 
		{
			CObject* pFind = NULL;
			CMouse*	pMouse = NULL;
			m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
			pMouse = (CMouse*)pFind;
			
			if(pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
			{
				CCollisionCom* pCollCom =  (CCollisionCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_COLLISION);
				return m_fRange + pCollCom->m_pCollisionSphere->fRadius ;
			}
		}

		return m_fRange;
	}		
}

int CSlot::Update()
{
	Charge();

	if(m_bEnable == true)
		return 0;

	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	if(m_fTime > m_fCooldownTime * (1.0f - m_pOwner->GetReducedCooldownTime()))
		m_bEnable = true;

	return 0;
}

int CSlot::Charge()
{
	if (m_iMaxCharge == 0  || m_iMaxCharge == m_iCharge )
	{
		return 0;
	}

	m_fChargingTime += CTimeMgr::GetInstance()->GetDeltaTime(); 
	
	if (m_fChargingTime > m_fChargeTime * (1.0f - m_pOwner->GetReducedCooldownTime()))
	{
		m_fChargingTime = 0.f ; 
		++m_iCharge;
		
		if (m_iMaxCharge < m_iCharge )
		{
			m_iCharge = m_iMaxCharge;
		}
	}

	return 0;
}

SLOT_RESULT CSlot::Condition()
{
	return SLOT_RESULT_NULL;
}
