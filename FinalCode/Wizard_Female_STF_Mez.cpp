#include "StdAfx.h"
#include "Wizard_Female_STF_Mez.h"

CWizard_Female_STF_Mez::CWizard_Female_STF_Mez(int _iMez , D3DXVECTOR3& _vPos)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_STF_MEZ;

	m_fTime = 0.f; 
	
	m_iMez = _iMez;

	m_vPos = _vPos;

	m_vOldColor = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
}

CWizard_Female_STF_Mez::~CWizard_Female_STF_Mez(void)
{
}

void CWizard_Female_STF_Mez::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation Mez �⺻ �ִϸ��̼� 
	m_pOwner->SetAnimation(1);

	// Clear
	m_pPathFindCom->Clear();

	m_vOldColor = ((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor;

}

CPlayerState* CWizard_Female_STF_Mez::Action()
{
	switch (m_iMez)
	{
	case SKILL_TYPE_ENTANGLE:
		return Mode0();
	case SKILL_TYPE_FULL:
		return Mode1();
	case SKILL_TYPE_PUSH:
		return Mode2();
	case SKILL_TYPE_STUN: 
		return Mode3();
	}

	return new CWizard_Female_STF_Idle;
}


CPlayerState* CWizard_Female_STF_Mez::Mode0()
{
	if (!m_pOwner->IsMez(m_iMez))
	{
		return new CWizard_Female_STF_Idle;
	}

	int iSlotNum = CPlayerState::UsingKeyMouse();

	if (iSlotNum == -1)
	{
		return NULL;
	}

	if (IsSlotRange( iSlotNum ))
		return SlotAction(iSlotNum);
	

	return NULL;
}

CPlayerState* CWizard_Female_STF_Mez::Mode1()
{
	return new CWizard_Female_STF_Knockback(m_vPos, 1000.f);
}

CPlayerState* CWizard_Female_STF_Mez::Mode2()
{
	return new CWizard_Female_STF_Knockback(m_vPos, 1000.f);
}

CPlayerState* CWizard_Female_STF_Mez::Mode3()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	
	((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = D3DXVECTOR4(0.f , 1.f , 1.f , 1.f );

	if (m_fTime > 1.0f )
	{
		((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = m_vOldColor;
		return new CWizard_Female_STF_Idle;	
	}

	return NULL;
}

CPlayerState* CWizard_Female_STF_Mez::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_WIZARD_TELEPORT)
	{
		return NULL;
	}

	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch (m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case 	SLOT_ID_WIZARD_MAGIC_MISSILE:					// ����ź
		return  new CWizard_Female_STF_Attack; 

	case	SLOT_ID_WIZARD_SHOCK_PULSE:						// ���� ���
		return new CWizard_Female_STF_Directed;  

	case	SLOT_ID_WIZARD_SPECTRAL_BLADE:					// ������ Į��
		return new CWizard_Female_STF_AOE;

	case	SLOT_ID_WIZARD_ELECTROCUTE:						// ����
		return new CWizard_Female_STF_Channel(_iIndex);

	case	SLOT_ID_WIZARD_PUNCH:							// �ָ���
		return new CWizard_Female_STF_Attack;	

	case	SLOT_ID_WIZARD_NEAR_ATTACK:						// �ٰŸ� ����
		return new CWizard_Female_STF_Attack;

	case	SLOT_ID_WIZARD_FAR_ATTACK:						// ���Ÿ� ����
		return NULL;

	case	SLOT_ID_WIZARD_MAGIC_ATTACK:					// ������ �߻�
		return  new CWizard_Female_STF_Attack; 

	case	SLOT_ID_WIZARD_RAY_OF_FROST:					// ���� ����			
		return new CWizard_Female_STF_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_ARCANE_ORB:						// ���� ����	
		return new CWizard_Female_STF_Directed;				

	case	SLOT_ID_WIZARD_ARCANE_TORRENT:					// ���� �ݷ�	
		return new CWizard_Female_STF_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_DISINTEGRATE:					// �Ŀ�					
		return new CWizard_Female_STF_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_FROST_NOVA:						// ������				
		return new CWizard_Female_STF_AOE;					

	case	SLOT_ID_WIZARD_DIAMOND_SKIN:					// ���̾Ƹ�� �Ǻ�		
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_SLOW_TIME:						// ���� ����			
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_TELEPORT:						// �����̵�	
		return new CWizard_Female_STF_Teleport;				

	case	SLOT_ID_WIZARD_WAVE_OF_FORCE:					// ���� �ĵ�			
		return new CWizard_Female_STF_AOE2;						

	case	SLOT_ID_WIZARD_ENERGY_TWISTER:					// ���� ���� �ٶ�		
		return new CWizard_Female_STF_AOE;						

	case	SLOT_ID_WIZARD_HYDRA:							// �����				
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_METEOR:							// � ����			
		return new CWizard_Female_STF_AOE;					

	case	SLOT_ID_WIZARD_BLIZZARD:						// ������				
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_ICE_ARMOR:						// ���� ����
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_STORM_ARMOR:						// õ�� ����
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_MAGIC_WEAPON:					// ���� ����
		return new CWizard_Female_STF_AOE;					

	case	SLOT_ID_WIZARD_FAMILIAR:						// �翪��
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_ENERGY_ARMOR:					// ���� ����	
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_EXPLOSIVE_BLAST:					// ������ ����
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_MIRROR_IMAGE:					// �н�
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_ARCHON:							// ����		
		return new CWizard_Female_STF_Summon;				

	}

	return NULL;
}

bool CWizard_Female_STF_Mez::IsSlotRange(int _iIndex)
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

			return false;
		}
	}
	return true;
}
