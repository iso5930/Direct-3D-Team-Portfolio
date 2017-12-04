#include "StdAfx.h"
#include "Barbarian_Male_1HT_Idle.h"

CBarbarian_Male_1HT_Idle::CBarbarian_Male_1HT_Idle(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HT_IDLE;

	// Mode
	m_iMode = 0;

}

CBarbarian_Male_1HT_Idle::~CBarbarian_Male_1HT_Idle(void)
{
}

void CBarbarian_Male_1HT_Idle::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);


}

CPlayerState* CBarbarian_Male_1HT_Idle::Action()
{
	for (int i = 0 ; i < SKILL_TYPE_END ; ++i)
	{
		if (m_pOwner->IsMez(i))
		{
			return new CMonk_Male_1HS_Mez(i , D3DXVECTOR3(0.f , 0.f , 0.f ));
		}
	}
	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CPlayerState* CBarbarian_Male_1HT_Idle::Mode0()
{
	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	if (iSlotNum != -1 && iSlotNum == m_pOwner->GetLastPushSlotNum())
	{
		if (m_pOwner->GetPickType() == MOUSE_OVER_TYPE_MONSTER)
		{	
			if(IsSlotRange(m_pOwner->GetLastPushSlotNum()))
				return SlotAction(m_pOwner->GetLastPushSlotNum());

			return NULL;
		}		
	}

	// If None Input..
	if(iSlotNum == -1)
	{
		m_pOwner->SetPickObject(NULL);
		m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE);
		m_pOwner->SetLastPushSlotNum(iSlotNum);
		return NULL;
	}

	// Move
	if(iSlotNum == 4 && false == (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
	{
		if(CInputMgr::GetInstance()->GetPickPos() != NULL)
		{
			int iPickType = CPlayerState::OverObjectPick(); 
			if(iPickType == MOUSE_OVER_TYPE_END)
			{
				m_iMode = 0;
				return NULL;
			}
			else if (iPickType == MOUSE_OVER_TYPE_MONSTER)
			{

			}
			else
			{	
				m_iMode = 1;
				return NULL;
			}
		}	
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return NULL;
}



CPlayerState* CBarbarian_Male_1HT_Idle::Mode1()
{
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

		if(Equals(fDotZ, 1.0f, MAX_EPSILON))
		{
			if(fDotX > 0.0f)
				m_pTransformCom->m_vAngle.y += acosf(fDotZ);
			else
				m_pTransformCom->m_vAngle.y -= acosf(fDotZ);

			return new CBarbarian_Male_1HT_Run(m_pOwner->GetLastPushSlotNum());
		}
		else
		{
			if(fDotX > 0.0f)
				m_pTransformCom->m_vAngle.y += 20.0f * CTimeMgr::GetInstance()->GetDeltaTime();
			else
				m_pTransformCom->m_vAngle.y -= 20.0f * CTimeMgr::GetInstance()->GetDeltaTime();
		}
	}
	else
	{

		PickObjectEvent();
		m_iMode = 0 ;
	}

	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(iSlotNum == -1)
	{
		if (m_pOwner->GetPickType() == MOUSE_OVER_TYPE_MONSTER)
		{	
			if (IsSlotRange(m_pOwner->GetLastPushSlotNum()))
				return SlotAction(m_pOwner->GetLastPushSlotNum());
			else
				return NULL;
		}

		m_pOwner->SetLastPushSlotNum(iSlotNum);
		return NULL;	

	}

	// Move
	if(iSlotNum == 4 && false == (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
	{
		int iPickType = CPlayerState::OverObjectPick(); 
		if(iPickType == MOUSE_OVER_TYPE_END)
		{
			m_iMode = 0;
			return NULL;
		}
		else if (iPickType == MOUSE_OVER_TYPE_MONSTER)
		{

		}
		else
		{	
			m_iMode = 1;
			return NULL;
		}

	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return NULL;
}

CPlayerState* CBarbarian_Male_1HT_Idle::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		m_pOwner->SetPickObject(NULL);
		m_pOwner->SetPickType(MOUSE_OVER_TYPE_NONE);
		m_pOwner->SetLastPushSlotNum(SLOT_PUSH_TYPE_NONE);
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
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

	case SLOT_ID_BARBARIAN_ANCIENT_SPEAR:			// ����� �ۻ�
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

	return NULL;

}

bool CBarbarian_Male_1HT_Idle::IsSlotRange(int _iIndex)
{
	//���� Ű ���� 
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

	// ��ų�� �Ÿ� Ȯ�� ���Ÿ� / �ٰŸ�
	if (!Equals(m_pOwner->GetSlot(_iIndex)->GetRange(), 9999.f, MAX_EPSILON))
	{
		//slot�� �׳� ����Ҽ��ִ��� üũ
		// ��밡���ϸ� return tre;

		//Pick�� ���Ͷ�� 
		if (m_pOwner->GetPickType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransform =  (CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM);
			D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
			vLength.y = 0.f;

			// �Ÿ��� Ȯ���ϰ� �Ÿ��� �ʰ��ϸ� Move �ƴϸ� slot::Begin()
			if (D3DXVec3Length( &vLength ) > m_pOwner->GetSlot(_iIndex)->GetRange())
			{
				m_pPathFindCom->Move(&pTransform->m_vPos);
				m_iMode = 1;
				return false;
			}
		}
		//���Ͱ� �ƴ϶�� 
		else
		{	
			if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
			{
				CTransformCom* pTransform =  (CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM);
				D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
				vLength.y = 0.f;

				// �Ÿ��� Ȯ���ϰ� �Ÿ��� �ʰ��ϸ� Move �ƴϸ� slot::Begin()
				if (D3DXVec3Length( &vLength ) < m_pOwner->GetSlot(_iIndex)->GetRange())
				{
					return true;
				}
			}

			CPlayerState::AttackMode();
			m_iMode = 1;
			return false;
		}
	}
	return true;
}
