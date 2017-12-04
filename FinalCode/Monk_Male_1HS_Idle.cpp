#include "StdAfx.h"
#include "Monk_Male_1HS_Idle.h"

CMonk_Male_1HS_Idle::CMonk_Male_1HS_Idle(void)
{
	m_eStateType = STATE_TYPE_MONK_MALE_1HS_IDLE;

	// Mode
	m_iMode = 0;

}

CMonk_Male_1HS_Idle::~CMonk_Male_1HS_Idle(void)
{
}

void CMonk_Male_1HS_Idle::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(1);

}

CPlayerState* CMonk_Male_1HS_Idle::Action()
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

CPlayerState* CMonk_Male_1HS_Idle::Mode0()
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

CPlayerState* CMonk_Male_1HS_Idle::Mode1()
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

			return new CMonk_Male_1HS_Run(m_pOwner->GetLastPushSlotNum());
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

CPlayerState* CMonk_Male_1HS_Idle::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
		case SLOT_ID_MONK_FISTS_OF_THUNDER:						// õ���ָ�
			return new CMonk_Male_1HS_Lightning_01;
		case SLOT_ID_MONK_DEADLY_REACH: 						// ���� ����
			return new CMonk_Male_1HS_LongReach_01;
		case SLOT_ID_MONK_CRIPPLING_WAVE: 						// ������ �ĵ�
			return new CMonk_Male_1HS_DebilitatingBlows_01;
		case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS: 			// õ���ǹ�
			return new CMonk_Male_1HS_RapidStrikes_01;
		case SLOT_ID_MONK_PUNCH: 								// �ָ���
			return new CMonk_Male_1HS_Attack;
		case SLOT_ID_MONK_NEAR_ATTACK: 							// �ٰŸ� ����
			return new CMonk_Male_1HS_Attack;
		case SLOT_ID_MONK_FAR_ATTACK: 							// ���Ÿ� ����
			break;
		case SLOT_ID_MONK_MAGIC_ATTACK: 						// ������ �߻�
			break;	
		case SLOT_ID_MONK_LASHING_TAIL_KICK: 					// �ݴ�����
			return new CMonk_Male_1HS_LashingTail;	
		case SLOT_ID_MONK_TEMPEST_RUSH: 						// ��ǳ ����
			return new CMonk_Male_1HS_Hobble_Run(_iIndex);
		case SLOT_ID_MONK_WAVE_OF_LIGHT: 						// ���� �ĵ�
			return new CMonk_Male_1HS_WaveofLight;	
		case SLOT_ID_MONK_BLINDING_FLASH: 						// ���ν� ����
			return new CMonk_Male_1HS_Buff;
		case SLOT_ID_MONK_BREATH_OF_HEAVEN: 					// õ���� ����
			return new CMonk_Male_1HS_Buff;	
		case SLOT_ID_MONK_SERENITY: 							// ���
			return new CMonk_Male_1HS_Buff;	
		case SLOT_ID_MONK_INNER_SANCTUARY: 						// ������ �Ƚ�ó
			return new CMonk_Male_1HS_Buff;		
		case SLOT_ID_MONK_DASHING_STRIKE: 						// ����Ÿ
			return new CMonk_Male_1HS_DashingStrike;	
		case SLOT_ID_MONK_EXPLODING_PALM: 						// ���� ���
			return new CMonk_Male_1HS_Lightning_03;	
		case SLOT_ID_MONK_SWEEPING_WIND: 						// �ָ���
			return new CMonk_Male_1HS_CelestialWheel;
		case SLOT_ID_MONK_CYCLONE_STRIKE: 						// �����
			return new CMonk_Male_1HS_Lethal_Decoy;
		case SLOT_ID_MONK_SEVEN_SIDED_STRIKE: 					// ĥ�� ����
			return new CMonk_Male_1HS_Buff;
		case SLOT_ID_MONK_MYSTIC_ALLY: 							// �ű��� ��
			return new CMonk_Male_1HS_Buff;	
		case SLOT_ID_MONK_MANTRA_OF_SALVATION: 					// ������ ����
			return new CMonk_Male_1HS_Buff;	
		case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION: 				// ������ ����
			return new CMonk_Male_1HS_Buff;	
		case SLOT_ID_MONK_MANTRA_OF_HEALING: 					// ġ���� ����
			return new CMonk_Male_1HS_Buff;	
		case SLOT_ID_MONK_MANTRA_OF_CONVICTION: 				// �ų��� ����
			return new CMonk_Male_1HS_Buff;	
	}

	return NULL;	
}	

bool CMonk_Male_1HS_Idle::IsSlotRange(int _iIndex)
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
