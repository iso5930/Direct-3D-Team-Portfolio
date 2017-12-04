#include "StdAfx.h"
#include "Barbarian_Male_DW_HirlWind.h"

CBarbarian_Male_DW_HirlWind::CBarbarian_Male_DW_HirlWind(int _iPushSlot)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_DW_HIRLWIND;

	m_iMode = 0;

	m_iPushSlot = _iPushSlot;
}

CBarbarian_Male_DW_HirlWind::~CBarbarian_Male_DW_HirlWind(void)
{
	m_pOwner->GetSlot(m_iPushSlot)->End();
}

void CBarbarian_Male_DW_HirlWind::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(24);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_DW_HirlWind::Action()
{
	int iSlotNum = CPlayerState::UsingKeyMouse();

	if (iSlotNum == -1 )
	{
		++m_iMode;
	}
	else if(iSlotNum == m_iPushSlot)
	{
		if (m_pOwner->GetSlot(m_iPushSlot)->Action() != SLOT_RESULT_NULL)
		{
			++m_iMode;
		}
	}
	else
		return SlotAction(iSlotNum);


	if (CInputMgr::GetInstance()->GetPickPos() != NULL)
	{
		vector<CObject*> pFindObjects;
		CDynamicProb* pDynamicProb;
		CNaviCell* pNextCell;

		D3DXVECTOR3 vDir = *CInputMgr::GetInstance()->GetPickPos() - m_pTransformCom->m_vPos;
		D3DXVec3Normalize(&vDir , &vDir);

		D3DXVECTOR3 vNextPos  =	 m_pTransformCom->m_vPos + ( vDir * CTimeMgr::GetInstance()->GetDeltaTime() * 300.f);

		m_pOwner->GetLayer()->FindObjects(pFindObjects, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);
		for(size_t i = 0; i < pFindObjects.size(); ++i)
		{
			pDynamicProb = (CDynamicProb*)pFindObjects[i];

			pDynamicProb->Intersect(&m_pTransformCom->m_vPos ,m_pPathFindCom->m_pCell , &vNextPos , &pNextCell );
			m_pTransformCom->m_vPos = vNextPos;
			m_pPathFindCom->m_pCell = pNextCell;

		}	
		pFindObjects.clear();

		CStaticProb* pStaticProb;
		m_pOwner->GetLayer()->FindObjects(pFindObjects, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);
		for(size_t i = 0; i < pFindObjects.size(); ++i)
		{
			pStaticProb = (CStaticProb*)pFindObjects[i];

			pStaticProb->Intersect(&m_pTransformCom->m_vPos ,m_pPathFindCom->m_pCell , &vNextPos , &pNextCell );
			m_pTransformCom->m_vPos = vNextPos;
			m_pPathFindCom->m_pCell = pNextCell;

		}pFindObjects.clear();
	}

	if(m_pAnimController->m_dFrameTime - 0.15 >= m_pAnimController->GetTrackPos())
	{
		return NULL;
	}

	if(0 == m_iMode)
		return Mode0();
	else
		return Mode1();


	return NULL;
}

CPlayerState* CBarbarian_Male_DW_HirlWind::Mode0()
{
	if(m_pAnimController->m_dFrameTime <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_DW_HirlWind(m_iPushSlot);
	}

	return NULL;

}

CPlayerState* CBarbarian_Male_DW_HirlWind::Mode1()
{
	return new CBarbarian_Male_DW_Idle;
}

CPlayerState* CBarbarian_Male_DW_HirlWind::SlotAction(int _iIndex)
{
	CSlot* pSlot = m_pOwner->GetSlot(_iIndex);

	//오른손 0   왼손 1
	if(pSlot->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(pSlot->GetSlotID())
	{
	case SLOT_ID_BARBARIAN_BASH:					// 후려치기
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_DW_Attack_R;
			else
				return new CBarbarian_Male_DW_Attack_L;
		}


	case SLOT_ID_BARBARIAN_CLEAVE:					// 가르기
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_DW_Cleave01;
			else
				return new CBarbarian_Male_DW_Cleave02;
		}

	case SLOT_ID_BARBARIAN_FRENZY:					// 광분
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_DW_Attack_R;
			else
				return new CBarbarian_Male_DW_Attack_L;
		}

	case SLOT_ID_BARBARIAN_WEAPON_THROW:			// 무기 투척
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_DW_Attack_R;
			else
				return new CBarbarian_Male_DW_Attack_L;
		}

	case SLOT_ID_BARBARIAN_PUNCH:					// 주먹질
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_DW_Attack_R;
			else
				return new CBarbarian_Male_DW_Attack_L;
		}


	case SLOT_ID_BARBARIAN_NEAR_ATTACK:				// 근거리 공격
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_DW_Attack_R;
			else
				return new CBarbarian_Male_DW_Attack_L;
		}

	case SLOT_ID_BARBARIAN_FAR_ATTACK:				// 원거리 공격
		return NULL;

	case SLOT_ID_BARBARIAN_MAGIC_ATTACK:			// 마법봉 발사
		return NULL;

	case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:	// 선조의 망치
		return new CBarbarian_Male_DW_Revenge;

	case SLOT_ID_BARBARIAN_REND:					// 분쇄
		return new CBarbarian_Male_DW_Cleave02;

	case SLOT_ID_BARBARIAN_SEISMIC_SLAM:			// 대지 강타
		return new CBarbarian_Male_DW_Revenge;

	case SLOT_ID_BARBARIAN_WHIRLWIND:				// 소용돌이
		return new CBarbarian_Male_DW_HirlWind(_iIndex);

	case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:			// 고대의 작살
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_DW_Attack_R;
			else
				return new CBarbarian_Male_DW_Attack_L;
		}

	case SLOT_ID_BARBARIAN_GROUND_STOMP:			// 발 구르기
		return  new CBarbarian_Male_DW_FootStomp;

	case SLOT_ID_BARBARIAN_LEAP:					// 도약 공격
		return  new CBarbarian_Male_DW_LeapAttack_Air;

	case SLOT_ID_BARBARIAN_SPRINT:					// 질주
		return new CBarbarian_Male_DW_Buff;

	case SLOT_ID_BARBARIAN_IGNORE_PAIN:				// 고통 감내
		return new CBarbarian_Male_DW_Buff;

	case SLOT_ID_BARBARIAN_OVERPOWER:				// 제압
		return new CBarbarian_Male_DW_Cleave02;

	case SLOT_ID_BARBARIAN_REVENGE:					// 보복
		return new CBarbarian_Male_DW_Cleave02;

	case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:			// 맹렬한 돌진
		return  new CBarbarian_Male_DW_Furious_Charge_Loop;

	case SLOT_ID_BARBARIAN_THREATENING_SHOUT:		// 위협의 외침
		return new CBarbarian_Male_DW_Buff;

	case SLOT_ID_BARBARIAN_BATTLE_RAGE:				// 전투 격노
		return new CBarbarian_Male_DW_Buff;

	case SLOT_ID_BARBARIAN_WAR_CRY:					// 전장의 함성
		return new CBarbarian_Male_DW_Buff;

	case SLOT_ID_BARBARIAN_EARTHQUAKE:				// 지진
		return  new CBarbarian_Male_DW_LeapAttack_End;

	case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:	// 선조의 귀환
		return new CBarbarian_Male_DW_Buff;

	case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:	// 광전사의 진노
		return new CBarbarian_Male_DW_Buff;

	}
	return NULL;

}
