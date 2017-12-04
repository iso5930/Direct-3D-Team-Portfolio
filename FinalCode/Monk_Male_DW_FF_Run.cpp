#include "StdAfx.h"
#include "Monk_Male_DW_FF_Run.h"

CMonk_Male_DW_FF_Run::CMonk_Male_DW_FF_Run(int _iSlotPush)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_FF_RUN;

	// SlotPush
	m_iSlotPush = _iSlotPush;

}

CMonk_Male_DW_FF_Run::~CMonk_Male_DW_FF_Run(void)
{
}

void CMonk_Male_DW_FF_Run::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(37);

	// MoveEnable
	m_pPathFindCom->Enable();
}

CPlayerState* CMonk_Male_DW_FF_Run::Action()
{
	if (m_pOwner->GetPickType() != MOUSE_OVER_TYPE_MONSTER)
		return Mode0();
	else
		return Mode1();

	return NULL;
}

CPlayerState* CMonk_Male_DW_FF_Run::Mode0()
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
		return new CMonk_Male_DW_FF_Idle;
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
			return new CMonk_Male_DW_FF_Idle;
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

CPlayerState* CMonk_Male_DW_FF_Run::Mode1()
{
	if (m_pOwner->GetPickObject() == NULL)
	{
		return new CMonk_Male_DW_FF_Idle;
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
			return new CMonk_Male_DW_FF_Idle ;
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
				return new CMonk_Male_DW_FF_Idle;
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

CPlayerState* CMonk_Male_DW_FF_Run::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case SLOT_ID_MONK_FISTS_OF_THUNDER:						// õ���ָ�
		return new CMonk_Male_DW_FF_Lightning_01;
	case SLOT_ID_MONK_DEADLY_REACH: 						// ���� ����
		return new CMonk_Male_DW_FF_LongReach_01;
	case SLOT_ID_MONK_CRIPPLING_WAVE: 						// ������ �ĵ�
		return new CMonk_Male_DW_FF_DebilitatingBlows_01;
	case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS: 			// õ���ǹ�
		return new CMonk_Male_DW_FF_RapidStrikes_01;
	case SLOT_ID_MONK_PUNCH: 								// �ָ���
		return new CMonk_Male_DW_FF_Attack_L;
	case SLOT_ID_MONK_NEAR_ATTACK: 							// �ٰŸ� ����
		return new CMonk_Male_DW_FF_Attack_L;
	case SLOT_ID_MONK_FAR_ATTACK: 							// ���Ÿ� ����
		break;
	case SLOT_ID_MONK_MAGIC_ATTACK: 						// ������ �߻�
		break;	
	case SLOT_ID_MONK_LASHING_TAIL_KICK: 					// �ݴ�����
		return new CMonk_Male_DW_FF_LashingTail;	
	case SLOT_ID_MONK_TEMPEST_RUSH: 						// ��ǳ ����
		return new CMonk_Male_DW_FF_Hobble_Run(_iIndex);
	case SLOT_ID_MONK_WAVE_OF_LIGHT: 						// ���� �ĵ�
		return new CMonk_Male_DW_FF_WaveofLight;	
	case SLOT_ID_MONK_BLINDING_FLASH: 						// ���ν� ����	
		KeyMouseStop(_iIndex);
		break;
	case SLOT_ID_MONK_BREATH_OF_HEAVEN: 					// õ���� ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_SERENITY: 							// ���	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_INNER_SANCTUARY: 						// ������ �Ƚ�ó
		return new CMonk_Male_DW_FF_Buff;		
	case SLOT_ID_MONK_DASHING_STRIKE: 						// ����Ÿ
		return new CMonk_Male_DW_FF_DashingStrike;	
	case SLOT_ID_MONK_EXPLODING_PALM: 						// ���� ���
		return new CMonk_Male_DW_FF_Attack_L;	
	case SLOT_ID_MONK_SWEEPING_WIND: 						// �ָ���
		return new CMonk_Male_DW_FF_CelestialWheel;
	case SLOT_ID_MONK_CYCLONE_STRIKE: 						// �����
		return new CMonk_Male_DW_FF_Lethal_Decoy;
	case SLOT_ID_MONK_SEVEN_SIDED_STRIKE: 					// ĥ�� ����
		return new CMonk_Male_DW_FF_Buff;
	case SLOT_ID_MONK_MYSTIC_ALLY: 							// �ű��� ��	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_SALVATION: 					// ������ ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION: 				// ������ ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_HEALING: 					// ġ���� ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_CONVICTION: 				// �ų��� ����	
		KeyMouseStop(_iIndex);
		break;	
	}

	return NULL;	
}

bool CMonk_Male_DW_FF_Run::IsSlotRange(int _iIndex)
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
