#include "StdAfx.h"
#include "DemonHunter_Female_CB1_Run.h"

CDemonHunter_Female_CB1_Run::CDemonHunter_Female_CB1_Run(int _iSlotPush)
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_RUN;

	// SlotPush
	m_iSlotPush = _iSlotPush;

}

CDemonHunter_Female_CB1_Run::~CDemonHunter_Female_CB1_Run()
{
}

void CDemonHunter_Female_CB1_Run::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(6);

	// MoveEnable
	m_pPathFindCom->Enable();
}

CPlayerState* CDemonHunter_Female_CB1_Run::Action()
{
	// SlotPush
	if(m_pOwner->GetPickType() != MOUSE_OVER_TYPE_MONSTER)
		return Mode0();
	else
		return Mode1();

	return NULL;
}



CPlayerState* CDemonHunter_Female_CB1_Run::Mode0()
{
	// Dir
	D3DXVECTOR3 vDir = m_pPathFindCom->m_vDst - m_pTransformCom->m_vPos;
	if(!Equals(vDir.x, 0.0f, MIN_EPSILON) || !Equals(vDir.z, 0.0f, MIN_EPSILON))
	{
		// Normalize
		vDir.y = 0.0f;
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
	}

	// If CurPos is DstPos.. return
	if(Equals(m_pPathFindCom->m_vDst.x, m_pTransformCom->m_vPos.x, MAX_EPSILON) && Equals(m_pPathFindCom->m_vDst.z, m_pTransformCom->m_vPos.z, MAX_EPSILON))
	{
		PickObjectEvent();
		return new CDemonHunter_Female_CB1_Idle;
	}

	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(iSlotNum == -1)
	{	
		m_pOwner->SetLastPushSlotNum(iSlotNum);
		return NULL;
	}

	// Move
	if(iSlotNum == 4 && false == (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
	{
		int iPickType = CPlayerState::OverObjectPick(); 
		if(iPickType == MOUSE_OVER_TYPE_END)
		{
			return new CDemonHunter_Female_CB1_Idle;
		}
		else if (iPickType == MOUSE_OVER_TYPE_MONSTER)
		{

		}
		else
		{				
			return NULL;
		}
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return NULL;
}

CPlayerState* CDemonHunter_Female_CB1_Run::Mode1()
{
	if (m_pOwner->GetPickObject() == NULL)
	{
		return new CDemonHunter_Female_CB1_Idle;
	}

	D3DXVECTOR3 vDir = m_pPathFindCom->m_vDst - m_pTransformCom->m_vPos;
	if(!Equals(vDir.x, 0.0f, MIN_EPSILON) || !Equals(vDir.z, 0.0f, MIN_EPSILON))
	{
		// Normalize
		vDir.y = 0.0f;
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
	}

	CTransformCom* pTransform =  (CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
	vLength.y = 0.f;

	if (m_pOwner->GetLastPushSlotNum() != -1  && D3DXVec3Length( &vLength ) <= m_pOwner->GetSlot(m_pOwner->GetLastPushSlotNum())->GetRange() )
	{

		CPlayerState* pPlayerState = SlotAction(m_pOwner->GetLastPushSlotNum());

		if (pPlayerState == NULL)
		{
			return new CDemonHunter_Female_CB1_Idle;
		}

		return pPlayerState;
	}

	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(iSlotNum == -1)
	{
		m_pPathFindCom->Move(&pTransform->m_vPos);
		return NULL;
	}
	// Move
	if(iSlotNum == 4 && false == (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
	{
		if (m_pOwner->GetLastPushSlotNum() !=  iSlotNum)
		{
			int iPickType = CPlayerState::OverObjectPick(); 
			if(iPickType == MOUSE_OVER_TYPE_END)
			{
				return new CDemonHunter_Female_CB1_Idle;
			}
			else if (iPickType == MOUSE_OVER_TYPE_MONSTER)
			{

			}
			else
			{				
				return NULL;
			}
		}
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return NULL;
}

CPlayerState* CDemonHunter_Female_CB1_Run::SlotAction( int _iIndex )
{
	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case  SLOT_ID_DEMONHUNTER_PUNCH:
		return NULL;

	case SLOT_ID_DEMONHUNTER_GRENADES:
		return new CDemonHunter_Female_CB1_Impale;

	case SLOT_ID_DEMONHUNTER_CHAKRAM:
		return new CDemonHunter_Female_CB1_Impale;

	case SLOT_ID_DEMONHUNTER_FAR_ATTACK:
		return new CDemonHunter_Female_CB1_Attack;

	case SLOT_ID_DEMONHUNTER_NEAR_ATTACK:
		return NULL;

	case SLOT_ID_DEMONHUNTER_MAGIC_ATTACK:
		return NULL;			

	case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN: // 연막	
		KeyMouseStop(_iIndex);
		return NULL;	

	case SLOT_ID_DEMONHUNTER_SHADOW_POWER: // 어둠의힘	
		KeyMouseStop(_iIndex);
		return NULL;	

	case SLOT_ID_DEMONHUNTER_PREPARATION: // 전투준비	
		KeyMouseStop(_iIndex);
		return NULL;	

	case SLOT_ID_DEMONHUNTER_VAULT:  // 도약
		return new CDemonHunter_Female_CB1_BackFlip;

	case SLOT_ID_DEMONHUNTER_COMPANION: // 동료소환
		return new CDemonHunter_Female_CB1_Companion;

	case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH: // 죽음의 표식
		return new CDemonHunter_Female_CB1_Caltrop;

	case SLOT_ID_DEMONHUNTER_SENTRY: // 자동쇠뇌
		return new CDemonHunter_Female_CB1_Caltrop;

	case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:	//부채	
		KeyMouseStop(_iIndex);
		return NULL;	

	case SLOT_ID_DEMONHUNTER_IMPALE:	//투검
		return new CDemonHunter_Female_CB1_Impale;

	case SLOT_ID_DEMONHUNTER_CALTROPS: // 쇄못 덫
		return new CDemonHunter_Female_CB1_Caltrop;

	case SLOT_ID_DEMONHUNTER_SPIKE_TRAP: // 쐐기 덫
		return new CDemonHunter_Female_CB1_Caltrop;

	case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
		return new CDemonHunter_Female_CB1_Attack;

	case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
		return new CDemonHunter_Female_CB1_Attack;

	case SLOT_ID_DEMONHUNTER_BOLA:
		return new CDemonHunter_Female_CB1_MultiShot;

	case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
		return new CDemonHunter_Female_CB1_Attack;

	case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
		return new CDemonHunter_Female_CB1_BolaSlot(_iIndex);

	case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
		return new CDemonHunter_Female_CB1_MultiShot;

	case SLOT_ID_DEMONHUNTER_MULTISHOT:
		return new CDemonHunter_Female_CB1_MultiShot;

	case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
		return new CDemonHunter_Female_CB1_MultiShot;

	case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
		return new CDemonHunter_Female_CB1_RainOfArrow;

	case SLOT_ID_DEMONHUNTER_STRAFE:
		return new CDemonHunter_Female_CB1_Strafe(_iIndex);
	}

	return NULL;
}

bool CDemonHunter_Female_CB1_Run::IsSlotRange(int _iIndex)
{
	//눌린 키 저장 
	m_pOwner->SetLastPushSlotNum(_iIndex);

	CObject* pFind = NULL;
	CMouse*	pMouse = NULL;
	m_pOwner->GetLayer()->FindObject(pFind , _T("Mouse"), LAYER_TYPE_MOUSE);
	pMouse = (CMouse*)pFind;

	if (KeyMouseDown(_iIndex))
	{
		m_pOwner->SetPickObject(pMouse->GetOverObject());
		m_pOwner->SetPickType(pMouse->GetMouseOverType());
	}

	// 스킬의 거리 확인 원거리 / 근거리
	if (!Equals(m_pOwner->GetSlot(_iIndex)->GetRange(), 9999.f, MAX_EPSILON))
	{
		//slot의 그냥 사용할수있는지 체크
		// 사용가능하면 return tre;

		//Pick가 몬스터라면 
		if (m_pOwner->GetPickType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransform =  (CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM);
			D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
			vLength.y = 0.f;

			// 거리를 확인하고 거리가 초과하면 Move 아니면 slot::Begin()
			if (D3DXVec3Length( &vLength ) > m_pOwner->GetSlot(_iIndex)->GetRange())
			{
				m_pPathFindCom->Move(&pTransform->m_vPos);
				return false;
			}
		}
		//몬스터가 아니라면 
		else
		{	
			if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
			{
				CTransformCom* pTransform =  (CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM);
				D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
				vLength.y = 0.f;

				// 거리를 확인하고 거리가 초과하면 Move 아니면 slot::Begin()
				if (D3DXVec3Length( &vLength ) < m_pOwner->GetSlot(_iIndex)->GetRange())
				{
					return true;
				}
			}

			CPlayerState::AttackMode();
			return false;
		}
	}
	return true;
}
