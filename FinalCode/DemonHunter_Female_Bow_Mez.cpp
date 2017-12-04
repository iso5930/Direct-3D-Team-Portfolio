#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Mez.h"

CDemonHunter_Female_Bow_Mez::CDemonHunter_Female_Bow_Mez(int _iMez , D3DXVECTOR3& _vPos)
{
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_MEZ;

	m_fTime = 0.f; 
	
	m_iMez = _iMez;

	m_vPos = _vPos;

	m_vOldColor = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
}

CDemonHunter_Female_Bow_Mez::~CDemonHunter_Female_Bow_Mez(void)
{
}

void CDemonHunter_Female_Bow_Mez::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation Mez 기본 애니메이션 
	m_pOwner->SetAnimation(3);

	// Clear
	m_pPathFindCom->Clear();

	m_vOldColor = ((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor;

}

CPlayerState* CDemonHunter_Female_Bow_Mez::Action()
{
	switch (m_iMez)
	{
	case SKILL_TYPE_ENTANGLE:
		return Mode0();
	case SKILL_TYPE_FULL:
		return Mode1();
	case SKILL_TYPE_PUSH:
		return Mode2();
	case SKILL_TYPE_STUN: 
		return Mode3();
	}

	return new CDemonHunter_Female_Bow_Idle;
}


CPlayerState* CDemonHunter_Female_Bow_Mez::Mode0()
{
	if (!m_pOwner->IsMez(m_iMez))
	{
		return new CDemonHunter_Female_Bow_Idle;
	}

	int iSlotNum = CPlayerState::UsingKeyMouse();

	if (iSlotNum == -1)
	{
		return NULL;
	}

	if (IsSlotRange( iSlotNum ))
		return SlotAction(iSlotNum);
	

	return NULL;
}

CPlayerState* CDemonHunter_Female_Bow_Mez::Mode1()
{
	return new CDemonHunter_Female_Bow_Knockback(m_vPos, 1000.f);
}

CPlayerState* CDemonHunter_Female_Bow_Mez::Mode2()
{
	return new CDemonHunter_Female_Bow_Knockback(m_vPos, 1000.f);
}

CPlayerState* CDemonHunter_Female_Bow_Mez::Mode3()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	
	((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = D3DXVECTOR4(0.f , 1.f , 1.f , 1.f );

	if (m_fTime > 1.0f )
	{
		((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = m_vOldColor;
		return new CDemonHunter_Female_Bow_Idle;	
	}

	return NULL;
}

CPlayerState* CDemonHunter_Female_Bow_Mez::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_DEMONHUNTER_VAULT ||	m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_DEMONHUNTER_STRAFE	)
	{
		return NULL;
	}

	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case  SLOT_ID_DEMONHUNTER_PUNCH:
		return NULL;

	case SLOT_ID_DEMONHUNTER_GRENADES:
		return new CDemonHunter_Female_Bow_Impale;

	case SLOT_ID_DEMONHUNTER_CHAKRAM:
		return new CDemonHunter_Female_Bow_Impale;

	case SLOT_ID_DEMONHUNTER_FAR_ATTACK:
		return new CDemonHunter_Female_Bow_Attack;		

	case SLOT_ID_DEMONHUNTER_NEAR_ATTACK:
		return NULL;

	case SLOT_ID_DEMONHUNTER_MAGIC_ATTACK:
		return NULL;			

	case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN: // 연막
		return new CDemonHunter_Female_Bow_Buff;

	case SLOT_ID_DEMONHUNTER_SHADOW_POWER: // 어둠의힘
		return new CDemonHunter_Female_Bow_Buff;

	case SLOT_ID_DEMONHUNTER_PREPARATION: // 전투준비
		return new CDemonHunter_Female_Bow_Buff;

	case SLOT_ID_DEMONHUNTER_VAULT:  // 도약
		return new CDemonHunter_Female_Bow_BackFlip;

	case SLOT_ID_DEMONHUNTER_COMPANION: // 동료소환
		return new CDemonHunter_Female_Bow_Companion;

	case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH: // 죽음의 표식
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_SENTRY: // 자동쇠뇌
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:	//부채
		return new CDemonHunter_Female_Bow_FanOfKnives;

	case SLOT_ID_DEMONHUNTER_IMPALE:	//투검
		return new CDemonHunter_Female_Bow_Impale;

	case SLOT_ID_DEMONHUNTER_CALTROPS: // 쇄못 덫
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_SPIKE_TRAP: // 쐐기 덫
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
		return new CDemonHunter_Female_Bow_Attack;

	case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
		return new CDemonHunter_Female_Bow_Attack;

	case SLOT_ID_DEMONHUNTER_BOLA:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
		return new CDemonHunter_Female_Bow_Attack;

	case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
		return new CDemonHunter_Female_Bow_BolaSlot(_iIndex);

	case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_MULTISHOT:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
		return new CDemonHunter_Female_Bow_RainOfArrow;

	case SLOT_ID_DEMONHUNTER_STRAFE:
		return new CDemonHunter_Female_Bow_Strafe(_iIndex);


	}

	return NULL;
}

bool CDemonHunter_Female_Bow_Mez::IsSlotRange(int _iIndex)
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

			return false;
		}
	}
	return true;
}
