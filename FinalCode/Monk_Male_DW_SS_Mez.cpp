#include "StdAfx.h"
#include "Monk_Male_DW_SS_Mez.h"

CMonk_Male_DW_SS_Mez::CMonk_Male_DW_SS_Mez(int _iMez , D3DXVECTOR3& _vPos)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SS_MEZ;

	m_fTime = 0.f; 
	
	m_iMez = _iMez;

	m_vPos = _vPos;

	m_vOldColor = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
}

CMonk_Male_DW_SS_Mez::~CMonk_Male_DW_SS_Mez(void)
{
}

void CMonk_Male_DW_SS_Mez::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation Mez �⺻ �ִϸ��̼� 
	m_pOwner->SetAnimation(6);

	// Clear
	m_pPathFindCom->Clear();

	m_vOldColor = ((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor;

}

CPlayerState* CMonk_Male_DW_SS_Mez::Action()
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

	return new CMonk_Male_DW_SS_Idle;
}


CPlayerState* CMonk_Male_DW_SS_Mez::Mode0()
{
	if (!m_pOwner->IsMez(m_iMez))
	{
		return new CMonk_Male_DW_SS_Idle;
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

CPlayerState* CMonk_Male_DW_SS_Mez::Mode1()
{
	return new CMonk_Male_DW_SS_Knockback(m_vPos, 1000.f);
}

CPlayerState* CMonk_Male_DW_SS_Mez::Mode2()
{
	return new CMonk_Male_DW_SS_Knockback(m_vPos, 1000.f);
}

CPlayerState* CMonk_Male_DW_SS_Mez::Mode3()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	
	((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = D3DXVECTOR4(0.f , 1.f , 1.f , 1.f );

	if (m_fTime > 1.0f )
	{
		((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = m_vOldColor;
		return new CMonk_Male_DW_SS_Idle;	
	}

	return NULL;
}

CPlayerState* CMonk_Male_DW_SS_Mez::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_MONK_DASHING_STRIKE ||
		m_pOwner->GetSlot(_iIndex)->GetSlotID() == SLOT_ID_MONK_TEMPEST_RUSH)
	{
		return NULL;
	}

	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}


	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case SLOT_ID_MONK_FISTS_OF_THUNDER:						// õ���ָ�
		return new CMonk_Male_DW_SS_Lightning_01;
	case SLOT_ID_MONK_DEADLY_REACH: 						// ���� ����
		return new CMonk_Male_DW_SS_LongReach_01;
	case SLOT_ID_MONK_CRIPPLING_WAVE: 						// ������ �ĵ�
		return new CMonk_Male_DW_SS_DebilitatingBlows_01;
	case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS: 			// õ���ǹ�
		return new CMonk_Male_DW_SS_RapidStrikes_01;
	case SLOT_ID_MONK_PUNCH: 								// �ָ���
		return new CMonk_Male_DW_SS_Attack_L;
	case SLOT_ID_MONK_NEAR_ATTACK: 							// �ٰŸ� ����
		return new CMonk_Male_DW_SS_Attack_L;
	case SLOT_ID_MONK_FAR_ATTACK: 							// ���Ÿ� ����
		break;
	case SLOT_ID_MONK_MAGIC_ATTACK: 						// ������ �߻�
		break;	
	case SLOT_ID_MONK_LASHING_TAIL_KICK: 					// �ݴ�����
		return new CMonk_Male_DW_SS_LashingTail;	
	case SLOT_ID_MONK_TEMPEST_RUSH: 						// ��ǳ ����
		return new CMonk_Male_DW_SS_Hobble_Run(_iIndex);
	case SLOT_ID_MONK_WAVE_OF_LIGHT: 						// ���� �ĵ�
		return new CMonk_Male_DW_SS_WaveofLight;	
	case SLOT_ID_MONK_BLINDING_FLASH: 						// ���ν� ����
		return new CMonk_Male_DW_SS_Buff;
	case SLOT_ID_MONK_BREATH_OF_HEAVEN: 					// õ���� ����
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_SERENITY: 							// ���
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_INNER_SANCTUARY: 						// ������ �Ƚ�ó
		return new CMonk_Male_DW_SS_Buff;		
	case SLOT_ID_MONK_DASHING_STRIKE: 						// ����Ÿ
		return new CMonk_Male_DW_SS_DashingStrike;	
	case SLOT_ID_MONK_EXPLODING_PALM: 						// ���� ���
		return new CMonk_Male_DW_SS_Attack_L;	
	case SLOT_ID_MONK_SWEEPING_WIND: 						// �ָ���
		return new CMonk_Male_DW_SS_CelestialWheel;
	case SLOT_ID_MONK_CYCLONE_STRIKE: 						// �����
		return new CMonk_Male_DW_SS_Lethal_Decoy;
	case SLOT_ID_MONK_SEVEN_SIDED_STRIKE: 					// ĥ�� ����
		return new CMonk_Male_DW_SS_Buff;
	case SLOT_ID_MONK_MYSTIC_ALLY: 							// �ű��� ��
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_SALVATION: 					// ������ ����
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION: 				// ������ ����
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_HEALING: 					// ġ���� ����
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_CONVICTION: 				// �ų��� ����
		return new CMonk_Male_DW_SS_Buff;	
	}



	return NULL;
}

bool CMonk_Male_DW_SS_Mez::IsSlotRange(int _iIndex)
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
