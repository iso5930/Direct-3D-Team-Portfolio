#include "StdAfx.h"
#include "Wizard_Female_1HS_Orb_Idle.h"

CWizard_Female_1HS_Orb_Idle::CWizard_Female_1HS_Orb_Idle(void)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_1HS_ORB_IDLE;

	// Mode
	m_iMode = 0;

}

CWizard_Female_1HS_Orb_Idle::~CWizard_Female_1HS_Orb_Idle(void)
{
}

void CWizard_Female_1HS_Orb_Idle::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(5);
}

CPlayerState* CWizard_Female_1HS_Orb_Idle::Action()
{
	for (int i = 0 ; i < SKILL_TYPE_END ; ++i)
	{
		if (m_pOwner->IsMez(i))
		{
			return new CWizard_Female_1HS_Orb_Mez(i , D3DXVECTOR3(0.f , 0.f , 0.f ));
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

CPlayerState* CWizard_Female_1HS_Orb_Idle::Mode0()
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

CPlayerState* CWizard_Female_1HS_Orb_Idle::Mode1()
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

			return new CWizard_Female_1HS_Orb_Run(m_pOwner->GetLastPushSlotNum());
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


CPlayerState* CWizard_Female_1HS_Orb_Idle::SlotAction(int _iIndex)
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
		return new CWizard_Female_1HS_Orb_AOE;					

	case	SLOT_ID_WIZARD_DIAMOND_SKIN:					// ���̾Ƹ�� �Ǻ�		
		return new CWizard_Female_1HS_Orb_Summon;				

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
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_STORM_ARMOR:						// õ�� ����
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_MAGIC_WEAPON:					// ���� ����
		return new CWizard_Female_1HS_Orb_AOE;					

	case	SLOT_ID_WIZARD_FAMILIAR:						// �翪��
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_ENERGY_ARMOR:					// ���� ����	
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_EXPLOSIVE_BLAST:					// ������ ����
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_MIRROR_IMAGE:					// �н�
		return new CWizard_Female_1HS_Orb_Summon;				

	case	SLOT_ID_WIZARD_ARCHON:							// ����		
		return new CWizard_Female_1HS_Orb_Summon;				

	}

	return NULL;	
}

bool CWizard_Female_1HS_Orb_Idle::IsSlotRange(int _iIndex)
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

