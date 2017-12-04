#include "StdAfx.h"
#include "DemonHunter_Female_CB1_BolaSlot.h"

CDemonHunter_Female_CB1_BolaSlot::CDemonHunter_Female_CB1_BolaSlot(int _iPushSlot)
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_CB1_BOLASLOT;
	
	// PushSlot
	m_iPushSlot = _iPushSlot;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.0f;

}

CDemonHunter_Female_CB1_BolaSlot::~CDemonHunter_Female_CB1_BolaSlot()
{
	m_pOwner->GetSlot(m_iPushSlot)->End();

	if (m_iMode == 1)
	{
		m_pOwner->SetAnimationMode(0);
	}
}	

void CDemonHunter_Female_CB1_BolaSlot::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(17);

	// Clear
	m_pPathFindCom->Clear();
}


CPlayerState* CDemonHunter_Female_CB1_BolaSlot::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CDemonHunter_Female_CB1_Idle;
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

CPlayerState* CDemonHunter_Female_CB1_BolaSlot::Mode0()
{
	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(m_pOwner->GetLastPushSlotNum() == iSlotNum)
	{
		if(m_pOwner->GetSlot(iSlotNum)->Action() == SLOT_RESULT_NULL)
		{
			//�ִϸ��̼� ����ð�
			if (0.1 > m_pAnimController->GetTrackPos())
				return NULL;

			m_pOwner->SetAnimationMode(2);
			++m_iMode;
		}
		else
		{
			return new CDemonHunter_Female_CB1_Idle;
		}

		return NULL;
	}

	if ( -1 == iSlotNum )
	{
		return new CDemonHunter_Female_CB1_Idle;
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return new CDemonHunter_Female_CB1_Run(m_pOwner->GetLastPushSlotNum());

};

CPlayerState* CDemonHunter_Female_CB1_BolaSlot::Mode1()
{
	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(m_pOwner->GetLastPushSlotNum() == iSlotNum)
	{
		if(m_pOwner->GetSlot(iSlotNum)->Action() == SLOT_RESULT_NULL)
		{
			return NULL;
		}
		else
		{
			return new CDemonHunter_Female_CB1_Idle;
		}
	}

	if ( -1 == iSlotNum )
	{
		return new CDemonHunter_Female_CB1_Idle;
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return new CDemonHunter_Female_CB1_Run(m_pOwner->GetLastPushSlotNum());

}


CPlayerState* CDemonHunter_Female_CB1_BolaSlot::SlotAction(int _iIndex)
{
	CSlot* pSlot = m_pOwner->GetSlot(_iIndex);

	//������ 0   �޼� 1
	if(pSlot->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(pSlot->GetSlotID())
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

	case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN: // ����	
		KeyMouseStop(_iIndex);
		return NULL;			

	case SLOT_ID_DEMONHUNTER_SHADOW_POWER: // �������	
		KeyMouseStop(_iIndex);
		return NULL;			

	case SLOT_ID_DEMONHUNTER_PREPARATION: // �����غ�	
		KeyMouseStop(_iIndex);
		return NULL;

	case SLOT_ID_DEMONHUNTER_VAULT:  // ����
		return new CDemonHunter_Female_CB1_BackFlip;

	case SLOT_ID_DEMONHUNTER_COMPANION: // �����ȯ
		return new CDemonHunter_Female_CB1_Companion;

	case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH: // ������ ǥ��
		return new CDemonHunter_Female_CB1_Caltrop;

	case SLOT_ID_DEMONHUNTER_SENTRY: // �ڵ����
		return new CDemonHunter_Female_CB1_Caltrop;

	case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:	//��ä	
		KeyMouseStop(_iIndex);
		return NULL;

	case SLOT_ID_DEMONHUNTER_IMPALE:	//����
		return new CDemonHunter_Female_CB1_Impale;

	case SLOT_ID_DEMONHUNTER_CALTROPS: // ��� ��
		return new CDemonHunter_Female_CB1_Caltrop;

	case SLOT_ID_DEMONHUNTER_SPIKE_TRAP: // ���� ��
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

bool CDemonHunter_Female_CB1_BolaSlot::IsSlotRange(int _iIndex)
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
			return false;
		}
	}
	return true;
}	
