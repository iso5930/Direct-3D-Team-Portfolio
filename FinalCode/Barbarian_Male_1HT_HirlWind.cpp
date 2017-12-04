#include "StdAfx.h"
#include "Barbarian_Male_1HT_HirlWind.h"

CBarbarian_Male_1HT_HirlWind::CBarbarian_Male_1HT_HirlWind(int _iPushSlot)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_HIRLWIND;

	m_iMode = 0;

	m_iPushSlot = _iPushSlot;
}

CBarbarian_Male_1HT_HirlWind::~CBarbarian_Male_1HT_HirlWind(void)
{
	m_pOwner->GetSlot(m_iPushSlot)->End();
}

void CBarbarian_Male_1HT_HirlWind::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(28);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CBarbarian_Male_1HT_HirlWind::Action()
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

CPlayerState* CBarbarian_Male_1HT_HirlWind::Mode0()
{
	if(m_pAnimController->m_dFrameTime <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_1HT_HirlWind(m_iPushSlot);
	}

	return NULL;

}

CPlayerState* CBarbarian_Male_1HT_HirlWind::Mode1()
{
	return new CBarbarian_Male_1HT_Idle;
}

CPlayerState* CBarbarian_Male_1HT_HirlWind::SlotAction(int _iIndex)
{
	CSlot* pSlot = m_pOwner->GetSlot(_iIndex);

	//������ 0   �޼� 1
	if(pSlot->Begin(0) != SLOT_RESULT_NULL)
	{
		return new CBarbarian_Male_1HT_Idle;
	}

	switch(pSlot->GetSlotID())
	{
	case SLOT_ID_BARBARIAN_BASH:					// �ķ�ġ��
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_1HT_Attack;
			else
				return new CBarbarian_Male_1HT_Cleave02;
		}


	case SLOT_ID_BARBARIAN_CLEAVE:					// ������
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_1HT_Cleave01;
			else
				return new CBarbarian_Male_1HT_Cleave02;
		}

	case SLOT_ID_BARBARIAN_FRENZY:					// ����
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_1HT_Attack;
			else
				return new CBarbarian_Male_1HT_Cleave02;
		}

	case SLOT_ID_BARBARIAN_WEAPON_THROW:			// ���� ��ô
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_1HT_Attack;
			else
				return new CBarbarian_Male_1HT_Cleave02;
		}

	case SLOT_ID_BARBARIAN_PUNCH:					// �ָ���
		return new CBarbarian_Male_1HT_Attack;

	case SLOT_ID_BARBARIAN_NEAR_ATTACK:				// �ٰŸ� ����
		{
			int iRand = rand() % 2; 
			if( 0 == iRand )
				return new CBarbarian_Male_1HT_Attack;
			else
				return new CBarbarian_Male_1HT_Cleave02;
		}

	case SLOT_ID_BARBARIAN_FAR_ATTACK:				// ���Ÿ� ����
		return NULL;

	case SLOT_ID_BARBARIAN_MAGIC_ATTACK:			// ������ �߻�
		return NULL;

	case SLOT_ID_BARBARIAN_HAMMER_OF_THE_ANCIENTS:	// ������ ��ġ
		return new CBarbarian_Male_1HT_Revenge;

	case SLOT_ID_BARBARIAN_REND:					// �м�
		return new CBarbarian_Male_1HT_Cleave02;

	case SLOT_ID_BARBARIAN_SEISMIC_SLAM:			// ���� ��Ÿ
		return new CBarbarian_Male_1HT_Revenge;

	case SLOT_ID_BARBARIAN_WHIRLWIND:				// �ҿ뵹��
		return new CBarbarian_Male_1HT_HirlWind(_iIndex);

	case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:			// ������ �ۻ�
		return new CBarbarian_Male_1HT_Attack;

	case SLOT_ID_BARBARIAN_GROUND_STOMP:			// �� ������
		return  new CBarbarian_Male_1HT_FootStomp;

	case SLOT_ID_BARBARIAN_LEAP:					// ���� ����
		return  new CBarbarian_Male_1HT_LeapAttack_Air;

	case SLOT_ID_BARBARIAN_SPRINT:					// ����
		return new CBarbarian_Male_1HT_Buff;

	case SLOT_ID_BARBARIAN_IGNORE_PAIN:				// ���� ����
		return new CBarbarian_Male_1HT_Buff;

	case SLOT_ID_BARBARIAN_OVERPOWER:				// ����
		return new CBarbarian_Male_1HT_Cleave02;

	case SLOT_ID_BARBARIAN_REVENGE:					// ����
		return new CBarbarian_Male_1HT_Cleave02;

	case SLOT_ID_BARBARIAN_FURIOUS_CHARGE:			// �ͷ��� ����
		return  new CBarbarian_Male_1HT_Furious_Charge_Loop;

	case SLOT_ID_BARBARIAN_THREATENING_SHOUT:		// ������ ��ħ
		return new CBarbarian_Male_1HT_Buff;

	case SLOT_ID_BARBARIAN_BATTLE_RAGE:				// ���� �ݳ�
		return new CBarbarian_Male_1HT_Buff;

	case SLOT_ID_BARBARIAN_WAR_CRY:					// ������ �Լ�
		return new CBarbarian_Male_1HT_Buff;

	case SLOT_ID_BARBARIAN_EARTHQUAKE:				// ����
		return  new CBarbarian_Male_1HT_LeapAttack_End;

	case SLOT_ID_BARBARIAN_CALL_OF_THE_ANCIENTS:	// ������ ��ȯ
		return new CBarbarian_Male_1HT_Buff;

	case SLOT_ID_BARBARIAN_WRATH_OF_THE_BERSERKER:	// �������� ����
		return new CBarbarian_Male_1HT_Buff;

	}

	return new CBarbarian_Male_1HT_Idle;

}