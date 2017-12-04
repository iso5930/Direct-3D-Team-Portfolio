#include "StdAfx.h"
#include "Wizard_Female_1HS_Orb_Channel.h"

CWizard_Female_1HS_Orb_Channel::CWizard_Female_1HS_Orb_Channel(int _iPushSlot)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_ORB_CHANNEL ;

	// PushSlot
	m_iPushSlot = _iPushSlot;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.f;
}

CWizard_Female_1HS_Orb_Channel::~CWizard_Female_1HS_Orb_Channel(void)
{
	m_pOwner->GetSlot(m_iPushSlot)->End();

	if (m_iMode == 1)
	{
		m_pOwner->SetAnimationMode(0);
	}
}

void CWizard_Female_1HS_Orb_Channel::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(14);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CWizard_Female_1HS_Orb_Channel::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_1HS_Orb_Idle;	
	}

	switch (m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();

	}

	return NULL;
}

CPlayerState* CWizard_Female_1HS_Orb_Channel::Mode0()
{
	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(m_pOwner->GetLastPushSlotNum() == iSlotNum)
	{
		if(m_pOwner->GetSlot(iSlotNum)->Action() == SLOT_RESULT_NULL)
		{
			//�ִϸ��̼� ����ð�
			if (0.311 > m_pAnimController->GetTrackPos())
				return NULL;

			m_pOwner->SetAnimationMode(2);
			++m_iMode;
		}
		else
		{
			return new CWizard_Female_1HS_Orb_Idle;
		}

		return NULL;
	}

	if ( -1 == iSlotNum )
	{
		return new CWizard_Female_1HS_Orb_Idle;
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return new CWizard_Female_1HS_Orb_Run(m_pOwner->GetLastPushSlotNum());
};

CPlayerState* CWizard_Female_1HS_Orb_Channel::Mode1()
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
			return new CWizard_Female_1HS_Orb_Idle;
		}
	}

	if ( -1 == iSlotNum )
	{
		return new CWizard_Female_1HS_Orb_Idle;
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return new CWizard_Female_1HS_Orb_Run(m_pOwner->GetLastPushSlotNum());
}

CPlayerState* CWizard_Female_1HS_Orb_Channel::SlotAction(int _iIndex)
{
	if(m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch (m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case 	SLOT_ID_WIZARD_MAGIC_MISSILE:					// ����ź
		if (CItemMgr::GetInstance()->GetItemInEquip(9) != NULL && CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & WEAPON_ID_WAND)
		{
			int iRand = 0;
			iRand = rand() % 2;
			if (iRand ==0 )
				return new CWizard_Female_Wand_Orb_Attack;
			else
				return  new CWizard_Female_1HS_Orb_Attack; 
		}
		else
			return  new CWizard_Female_1HS_Orb_Attack; 

	case	SLOT_ID_WIZARD_SHOCK_PULSE:						// ���� ���
		return new CWizard_Female_1HS_Orb_Directed;  

	case	SLOT_ID_WIZARD_SPECTRAL_BLADE:					// ������ Į��
		return new CWizard_Female_1HS_Orb_AOE;

	case	SLOT_ID_WIZARD_ELECTROCUTE:						// ����
		return new CWizard_Female_1HS_Orb_Channel(_iIndex);

	case	SLOT_ID_WIZARD_PUNCH:							// �ָ���
		return new CWizard_Female_1HS_Orb_Attack;	

	case	SLOT_ID_WIZARD_NEAR_ATTACK:						// �ٰŸ� ����
		return new CWizard_Female_1HS_Orb_Attack;

	case	SLOT_ID_WIZARD_FAR_ATTACK:						// ���Ÿ� ����
		return NULL;

	case	SLOT_ID_WIZARD_MAGIC_ATTACK:					// ������ �߻�
		if (CItemMgr::GetInstance()->GetItemInEquip(9) != NULL && CItemMgr::GetInstance()->GetItemInEquip(9)->dwItemID & WEAPON_ID_WAND)
		{
			int iRand = 0;
			iRand = rand() % 2;
			if (iRand ==0 )
				return new CWizard_Female_Wand_Orb_Attack;
			else
				return  new CWizard_Female_1HS_Orb_Attack; 
		}
		else
			return  new CWizard_Female_1HS_Orb_Attack; 

	case	SLOT_ID_WIZARD_RAY_OF_FROST:					// ���� ����			
		return new CWizard_Female_1HS_Orb_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_ARCANE_ORB:						// ���� ����	
		return new CWizard_Female_1HS_Orb_Directed;				

	case	SLOT_ID_WIZARD_ARCANE_TORRENT:					// ���� �ݷ�	
		return new CWizard_Female_1HS_Orb_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_DISINTEGRATE:					// �Ŀ�					
		return new CWizard_Female_1HS_Orb_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_FROST_NOVA:						// ������				
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_DIAMOND_SKIN:					// ���̾Ƹ�� �Ǻ�		
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_SLOW_TIME:						// ���� ����			
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_TELEPORT:						// �����̵�	
		return new CWizard_Female_1HS_Orb_Teleport;				

	case	SLOT_ID_WIZARD_WAVE_OF_FORCE:					// ���� �ĵ�			
		return new CWizard_Female_1HS_Orb_AOE2;						

	case	SLOT_ID_WIZARD_ENERGY_TWISTER:					// ���� ���� �ٶ�		
		return new CWizard_Female_1HS_Orb_AOE;						

	case	SLOT_ID_WIZARD_HYDRA:							// �����				
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_METEOR:							// � ����			
		return new CWizard_Female_1HS_Orb_AOE;					

	case	SLOT_ID_WIZARD_BLIZZARD:						// ������				
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_ICE_ARMOR:						// ���� ����
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_STORM_ARMOR:						// õ�� ����
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_MAGIC_WEAPON:					// ���� ����
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_FAMILIAR:						// �翪��
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_ENERGY_ARMOR:					// ���� ����
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_EXPLOSIVE_BLAST:					// ������ ����
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_MIRROR_IMAGE:					// �н�
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_ARCHON:							// ����		
		return new CWizard_Female_1HS_Orb_Summon;				


	}

	return NULL;	

}

bool CWizard_Female_1HS_Orb_Channel::IsSlotRange(int _iIndex)
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
