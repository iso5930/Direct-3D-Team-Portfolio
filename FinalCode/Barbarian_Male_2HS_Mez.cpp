#include "StdAfx.h"
#include "Barbarian_Male_2HS_Mez.h"

CBarbarian_Male_2HS_Mez::CBarbarian_Male_2HS_Mez(int _iMez , D3DXVECTOR3& _vPos)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HS_MEZ;

	m_fTime = 0.f; 
	
	m_iMez = _iMez;

	m_vPos = _vPos;

	m_vOldColor = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
}

CBarbarian_Male_2HS_Mez::~CBarbarian_Male_2HS_Mez(void)
{
}

void CBarbarian_Male_2HS_Mez::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation Mez 기본 애니메이션 
	m_pOwner->SetAnimation(2);

	// Clear
	m_pPathFindCom->Clear();

	m_vOldColor = ((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor;

}

CPlayerState* CBarbarian_Male_2HS_Mez::Action()
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

	return new CBarbarian_Male_2HS_Idle;
}


CPlayerState* CBarbarian_Male_2HS_Mez::Mode0()
{
	if (!m_pOwner->IsMez(m_iMez))
	{
		return new CBarbarian_Male_2HS_Idle;
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

CPlayerState* CBarbarian_Male_2HS_Mez::Mode1()
{
	return new CBarbarian_Male_2HS_Knockback_Loop(m_vPos, 1000.f);
}

CPlayerState* CBarbarian_Male_2HS_Mez::Mode2()
{
	return new CBarbarian_Male_2HS_Knockback_Loop(m_vPos, 1000.f);
}

CPlayerState* CBarbarian_Male_2HS_Mez::Mode3()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	
	((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = D3DXVECTOR4(0.f , 1.f , 1.f , 1.f );

	if (m_fTime > 1.0f )
	{
		((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = m_vOldColor;
		return new CBarbarian_Male_2HS_Idle;	
	}

	return NULL;
}

CPlayerState* CBarbarian_Male_2HS_Mez::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_BARBARIAN_LEAP ||
		m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_BARBARIAN_FURIOUS_CHARGE ||
		m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_BARBARIAN_WHIRLWIND
		)
	{
		return NULL;

	}

	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case SLOT_ID_BARBARIAN_BASH:					// 후려치기
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_2HS_Attack;
			else
				return new CBarbarian_Male_2HS_Cleave02;
		}
	case SLOT_ID_BARBARIAN_CLEAVE:					// 가르기
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_2HS_Cleave01;
			else
				return new CBarbarian_Male_2HS_Cleave02;
		}

	case SLOT_ID_BARBARIAN_FRENZY:					// 광분
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_2HS_Attack;
			else
				return new CBarbarian_Male_2HS_Cleave02;
		}

	case SLOT_ID_BARBARIAN_WEAPON_THROW:			// 무기 투척
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_2HS_Attack;
			else
				return new CBarbarian_Male_2HS_Cleave02;
		}

	case SLOT_ID_BARBARIAN_PUNCH:					// 주먹질
		return new CBarbarian_Male_2HS_Attack;

	case SLOT_ID_BARBARIAN_NEAR_ATTACK:				// 근거리 공격
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_2HS_Attack;
			else
				return new CBarbarian_Male_2HS_Cleave02;
		}

	case SLOT_ID_BARBARIAN_FAR_ATTACK:				// 원거리 공격
		return NULL;

	case SLOT_ID_BARBARIAN_MAGIC_ATTACK:			// 마법봉 발사
		return NULL;

	case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:	// 선조의 망치
		return new CBarbarian_Male_2HS_Revenge;

	case SLOT_ID_BARBARIAN_REND:					// 분쇄
		return new CBarbarian_Male_2HS_Cleave02;

	case SLOT_ID_BARBARIAN_SEISMIC_SLAM:			// 대지 강타
		return new CBarbarian_Male_2HS_Revenge;

	case SLOT_ID_BARBARIAN_WHIRLWIND:				// 소용돌이
		return new CBarbarian_Male_2HS_HirlWind(_iIndex);

	case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:			// 고대의 작살
		return new CBarbarian_Male_2HS_Attack;

	case SLOT_ID_BARBARIAN_GROUND_STOMP:			// 발 구르기
		return  new CBarbarian_Male_2HS_FootStomp;

	case SLOT_ID_BARBARIAN_LEAP:					// 도약 공격
		return  new CBarbarian_Male_2HS_LeapAttack_Air;

	case SLOT_ID_BARBARIAN_SPRINT:					// 질주
		return new CBarbarian_Male_2HS_Buff;

	case SLOT_ID_BARBARIAN_IGNORE_PAIN:				// 고통 감내
		return new CBarbarian_Male_2HS_Buff;

	case SLOT_ID_BARBARIAN_OVERPOWER:				// 제압
		return new CBarbarian_Male_2HS_Cleave02;

	case SLOT_ID_BARBARIAN_REVENGE:					// 보복
		return new CBarbarian_Male_2HS_Cleave02;

	case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:			// 맹렬한 돌진
		return  new CBarbarian_Male_2HS_Furious_Charge_Loop;

	case SLOT_ID_BARBARIAN_THREATENING_SHOUT:		// 위협의 외침
		return new CBarbarian_Male_2HS_Buff;

	case SLOT_ID_BARBARIAN_BATTLE_RAGE:				// 전투 격노
		return new CBarbarian_Male_2HS_Buff;

	case SLOT_ID_BARBARIAN_WAR_CRY:					// 전장의 함성
		return new CBarbarian_Male_2HS_Buff;

	case SLOT_ID_BARBARIAN_EARTHQUAKE:				// 지진
		return  new CBarbarian_Male_2HS_LeapAttack_End;

	case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:	// 선조의 귀환
		return new CBarbarian_Male_2HS_Buff;

	case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:	// 광전사의 진노
		return new CBarbarian_Male_2HS_Buff;
	}

	return NULL;
}

bool CBarbarian_Male_2HS_Mez::IsSlotRange(int _iIndex)
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
