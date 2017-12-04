#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Idle.h"

CDemonHunter_Female_Bow_Idle::CDemonHunter_Female_Bow_Idle()
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_IDLE;

	// Mode
	m_iMode = 0;

}

CDemonHunter_Female_Bow_Idle::~CDemonHunter_Female_Bow_Idle()
{
}

void CDemonHunter_Female_Bow_Idle::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(3);
}

CPlayerState* CDemonHunter_Female_Bow_Idle::Action()
{
	for (int i = 0 ; i < SKILL_TYPE_END ; ++i)
	{
		if (m_pOwner->IsMez(i))
		{
			return new CDemonHunter_Female_Bow_Mez(i , D3DXVECTOR3(0.f , 0.f , 0.f ));
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

CPlayerState* CDemonHunter_Female_Bow_Idle::Mode0()
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

CPlayerState* CDemonHunter_Female_Bow_Idle::Mode1()
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

			return new CDemonHunter_Female_Bow_Run(m_pOwner->GetLastPushSlotNum());
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

CPlayerState* CDemonHunter_Female_Bow_Idle::SlotAction(int _iIndex)
{
	CSlot* pSlot = m_pOwner->GetSlot(_iIndex);

	//������ 0   �޼� 1
	if(pSlot->Begin(1) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(pSlot->GetSlotID())
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

	case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN: // ����
		return new CDemonHunter_Female_Bow_Buff;

	case SLOT_ID_DEMONHUNTER_SHADOW_POWER: // �������
		return new CDemonHunter_Female_Bow_Buff;

	case SLOT_ID_DEMONHUNTER_PREPARATION: // �����غ�
		return new CDemonHunter_Female_Bow_Buff;

	case SLOT_ID_DEMONHUNTER_VAULT:  // ����
		return new CDemonHunter_Female_Bow_BackFlip;

	case SLOT_ID_DEMONHUNTER_COMPANION: // �����ȯ
		return new CDemonHunter_Female_Bow_Companion;

	case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH: // ������ ǥ��
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_SENTRY: // �ڵ����
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:	//��ä
		return new CDemonHunter_Female_Bow_FanOfKnives;

	case SLOT_ID_DEMONHUNTER_IMPALE:	//����
		return new CDemonHunter_Female_Bow_Impale;

	case SLOT_ID_DEMONHUNTER_CALTROPS: // ��� ��
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_SPIKE_TRAP: // ���� ��
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

bool CDemonHunter_Female_Bow_Idle::IsSlotRange(int _iIndex)
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
