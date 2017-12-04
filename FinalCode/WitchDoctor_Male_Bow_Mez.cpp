#include "StdAfx.h"
#include "WitchDoctor_Male_Bow_Mez.h"

CWitchDoctor_Male_Bow_Mez::CWitchDoctor_Male_Bow_Mez(int _iMez , D3DXVECTOR3& _vPos)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_BOW_MEZ;

	m_fTime = 0.f; 
	
	m_iMez = _iMez;

	m_vPos = _vPos;

	m_vOldColor = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
}

CWitchDoctor_Male_Bow_Mez::~CWitchDoctor_Male_Bow_Mez(void)
{
}

void CWitchDoctor_Male_Bow_Mez::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation Mez �⺻ �ִϸ��̼� 
	m_pOwner->SetAnimation(7);

	// Clear
	m_pPathFindCom->Clear();

	m_vOldColor = ((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor;

}

CPlayerState* CWitchDoctor_Male_Bow_Mez::Action()
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

	return new CWitchDoctor_Male_Bow_Idle;
}


CPlayerState* CWitchDoctor_Male_Bow_Mez::Mode0()
{
	if (!m_pOwner->IsMez(m_iMez))
	{
		return new CWitchDoctor_Male_Bow_Idle;
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

CPlayerState* CWitchDoctor_Male_Bow_Mez::Mode1()
{
	return new CWitchDoctor_Male_Bow_Knockback(m_vPos, 1000.f);
}

CPlayerState* CWitchDoctor_Male_Bow_Mez::Mode2()
{
	return new CWitchDoctor_Male_Bow_Knockback(m_vPos, 1000.f);
}

CPlayerState* CWitchDoctor_Male_Bow_Mez::Mode3()
{
	m_fTime += CTimeMgr::GetInstance()->GetDeltaTime();
	
	((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = D3DXVECTOR4(0.f , 1.f , 1.f , 1.f );

	if (m_fTime > 1.0f )
	{
		((CRenderCom*)m_pOwner->GetComponent(COM_TYPE_RENDER))->m_vColor = m_vOldColor;
		return new CWitchDoctor_Male_Bow_Idle;	
	}

	return NULL;
}

CPlayerState* CWitchDoctor_Male_Bow_Mez::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{

	case SLOT_ID_WITCHDOCTOR_POISON_DART:			// ��ħ
		return new CWitchDoctor_Male_Bow_Blow;
	case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:		// ��ü �Ź�
		return new CWitchDoctor_Male_Bow_FireBall;
	case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:		// ���� �β���
		return new CWitchDoctor_Male_Bow_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_FIREBOMB:				// ����ź
		return new CWitchDoctor_Male_Bow_FireBall;
	case SLOT_ID_WITCHDOCTOR_PUNCH:					// �ָ���
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:			// �ٰŸ� ����
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:			// ���Ÿ� ����
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:			// ������ �߻�
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:		// ������ �վƱ�
		return new CWitchDoctor_Male_Bow_FireBall;
	case SLOT_ID_WITCHDOCTOR_FIREBATS:				// �ҹ���
		return new CWitchDoctor_Male_Bow_Channel;
	case SLOT_ID_WITCHDOCTOR_HAUNT:					// ȥ�� ���
		return new CWitchDoctor_Male_Bow_Horrify;
	case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:			// �޶ѱ� ��
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:	// ���� �鰳 ��ȯ
		return new CWitchDoctor_Male_Bow_Summon;
	case SLOT_ID_WITCHDOCTOR_HORRIFY:				// ����
		return new CWitchDoctor_Male_Bow_Horrify;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:			// ȥ�� ����
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_HEX:					// �ּ�
		return new CWitchDoctor_Male_Bow_Summon;
	case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:			// ȥ�� ��Ȯ
		return new CWitchDoctor_Male_Bow_Soul_Harvest;
	case SLOT_ID_WITCHDOCTOR_SACRIFICE:				// ���
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:		// ��ȥ��
		return new CWitchDoctor_Male_Bow_Horrify;
	case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:		// ���� ����
		return new CWitchDoctor_Male_Bow_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:		// ȥ�� ����
		return new CWitchDoctor_Male_Bow_FastCast;
	case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:			// �꼺 ����
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:			// ������ ��
		return new CWitchDoctor_Male_Bow_Summon;		
	case SLOT_ID_WITCHDOCTOR_GARGANTUAN:			// ��ġ
		return new CWitchDoctor_Male_Bow_Summon;
	case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:		// ������� �εμ�
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:			// ����� ����
		return new CWitchDoctor_Male_Bow_FlayerArmy;	

	}

	return NULL;
}

bool CWitchDoctor_Male_Bow_Mez::IsSlotRange(int _iIndex)
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

			return false;
		}
	}
	return true;
}
