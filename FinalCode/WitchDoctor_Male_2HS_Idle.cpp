#include "StdAfx.h"
#include "WitchDoctor_Male_2HS_Idle.h"

CWitchDoctor_Male_2HS_Idle::CWitchDoctor_Male_2HS_Idle(void)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HS_IDLE;

	// Mode
	m_iMode = 0;

}

CWitchDoctor_Male_2HS_Idle::~CWitchDoctor_Male_2HS_Idle(void)
{
}

void CWitchDoctor_Male_2HS_Idle::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(4);

}

CPlayerState* CWitchDoctor_Male_2HS_Idle::Action()
{
	for (int i = 0 ; i < SKILL_TYPE_END ; ++i)
	{
		if (m_pOwner->IsMez(i))
		{
			return new CWitchDoctor_Male_2HS_Mez(i , D3DXVECTOR3(0.f , 0.f , 0.f ));
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

CPlayerState* CWitchDoctor_Male_2HS_Idle::Mode0()
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

CPlayerState* CWitchDoctor_Male_2HS_Idle::Mode1()
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

			return new CWitchDoctor_Male_2HS_Run(m_pOwner->GetLastPushSlotNum());
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

CPlayerState* CWitchDoctor_Male_2HS_Idle::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
		
	case SLOT_ID_WITCHDOCTOR_POISON_DART:			// ��ħ
		return new CWitchDoctor_Male_2HS_Blow;
	case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:		// ��ü �Ź�
		return new CWitchDoctor_Male_2HS_FireBall;
	case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:		// ���� �β���
		return new CWitchDoctor_Male_2HS_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_FIREBOMB:				// ����ź
		return new CWitchDoctor_Male_2HS_FireBall;
	case SLOT_ID_WITCHDOCTOR_PUNCH:					// �ָ���
		return new CWitchDoctor_Male_2HS_Attack;
	case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:			// �ٰŸ� ����
		return new CWitchDoctor_Male_2HS_Attack;
	case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:			// ���Ÿ� ����
		return new CWitchDoctor_Male_2HS_Attack;
	case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:			// ������ �߻�
		return new CWitchDoctor_Male_2HS_Attack;
	case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:		// ������ �վƱ�
		return new CWitchDoctor_Male_2HS_FireBall;
	case SLOT_ID_WITCHDOCTOR_FIREBATS:				// �ҹ���
		return new CWitchDoctor_Male_2HS_Channel;
	case SLOT_ID_WITCHDOCTOR_HAUNT:					// ȥ�� ���
		return new CWitchDoctor_Male_2HS_Horrify;
	case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:			// �޶ѱ� ��
		return new CWitchDoctor_Male_2HS_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:	// ���� �鰳 ��ȯ
		return new CWitchDoctor_Male_2HS_Summon;
	case SLOT_ID_WITCHDOCTOR_HORRIFY:				// ����
		return new CWitchDoctor_Male_2HS_Horrify;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:			// ȥ�� ����
		return new CWitchDoctor_Male_2HS_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_HEX:					// �ּ�
		return new CWitchDoctor_Male_2HS_Summon;
	case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:			// ȥ�� ��Ȯ
		return new CWitchDoctor_Male_2HS_Soul_Harvest;
	case SLOT_ID_WITCHDOCTOR_SACRIFICE:				// ���
		return new CWitchDoctor_Male_2HS_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:		// ��ȥ��
		return new CWitchDoctor_Male_2HS_Horrify;
	case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:		// ���� ����
		return new CWitchDoctor_Male_2HS_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:		// ȥ�� ����
		return new CWitchDoctor_Male_2HS_FastCast;
	case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:			// �꼺 ����
		return new CWitchDoctor_Male_2HS_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:			// ������ ��
		return new CWitchDoctor_Male_2HS_Summon;		
	case SLOT_ID_WITCHDOCTOR_GARGANTUAN:			// ��ġ
		return new CWitchDoctor_Male_2HS_Summon;
	case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:		// ������� �εμ�
		return new CWitchDoctor_Male_2HS_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:			// ����� ����
		return new CWitchDoctor_Male_2HS_FlayerArmy;	
	
	}
	
	return NULL;
}

bool CWitchDoctor_Male_2HS_Idle::IsSlotRange(int _iIndex)
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
