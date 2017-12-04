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

	// SetAnimation Mez 기본 애니메이션 
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

	case SLOT_ID_WITCHDOCTOR_POISON_DART:			// 독침
		return new CWitchDoctor_Male_Bow_Blow;
	case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:		// 시체 거미
		return new CWitchDoctor_Male_Bow_FireBall;
	case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:		// 역병 두꺼비
		return new CWitchDoctor_Male_Bow_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_FIREBOMB:				// 불폭탄
		return new CWitchDoctor_Male_Bow_FireBall;
	case SLOT_ID_WITCHDOCTOR_PUNCH:					// 주먹질
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:			// 근거리 공격
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:			// 원거리 공격
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:			// 마법봉 발사
		return new CWitchDoctor_Male_Bow_Attack;
	case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:		// 망자의 손아귀
		return new CWitchDoctor_Male_Bow_FireBall;
	case SLOT_ID_WITCHDOCTOR_FIREBATS:				// 불박쥐
		return new CWitchDoctor_Male_Bow_Channel;
	case SLOT_ID_WITCHDOCTOR_HAUNT:					// 혼령 출몰
		return new CWitchDoctor_Male_Bow_Horrify;
	case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:			// 메뚜기 떼
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:	// 좀비 들개 소환
		return new CWitchDoctor_Male_Bow_Summon;
	case SLOT_ID_WITCHDOCTOR_HORRIFY:				// 공포
		return new CWitchDoctor_Male_Bow_Horrify;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:			// 혼령 걸음
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_HEX:					// 주술
		return new CWitchDoctor_Male_Bow_Summon;
	case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:			// 혼령 수확
		return new CWitchDoctor_Male_Bow_Soul_Harvest;
	case SLOT_ID_WITCHDOCTOR_SACRIFICE:				// 희생
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:		// 대혼란
		return new CWitchDoctor_Male_Bow_Horrify;
	case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:		// 돌진 좀비
		return new CWitchDoctor_Male_Bow_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:		// 혼령 공세
		return new CWitchDoctor_Male_Bow_FastCast;
	case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:			// 산성 구름
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:			// 죽음의 벽
		return new CWitchDoctor_Male_Bow_Summon;		
	case SLOT_ID_WITCHDOCTOR_GARGANTUAN:			// 덩치
		return new CWitchDoctor_Male_Bow_Summon;
	case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:		// 대재앙의 부두술
		return new CWitchDoctor_Male_Bow_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:			// 우상족 군대
		return new CWitchDoctor_Male_Bow_FlayerArmy;	

	}

	return NULL;
}

bool CWitchDoctor_Male_Bow_Mez::IsSlotRange(int _iIndex)
{
	//눌린 키 저장 
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

	// 스킬의 거리 확인 원거리 / 근거리
	if (!Equals(m_pOwner->GetSlot(_iIndex)->GetRange(), 9999.f, MAX_EPSILON))
	{
		//slot의 그냥 사용할수있는지 체크
		// 사용가능하면 return tre;

		//Pick가 몬스터라면 
		if (m_pOwner->GetPickType() == MOUSE_OVER_TYPE_MONSTER)
		{
			CTransformCom* pTransform =  (CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM);
			D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
			vLength.y = 0.f;

			// 거리를 확인하고 거리가 초과하면 Move 아니면 slot::Begin()
			if (D3DXVec3Length( &vLength ) > m_pOwner->GetSlot(_iIndex)->GetRange())
			{
				m_pPathFindCom->Move(&pTransform->m_vPos);
				return false;
			}
		}
		//몬스터가 아니라면 
		else
		{	
			if (pMouse->GetMouseOverType() == MOUSE_OVER_TYPE_MONSTER)
			{
				CTransformCom* pTransform =  (CTransformCom*)pMouse->GetOverObject()->GetComponent(COM_TYPE_TRANSFORM);
				D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
				vLength.y = 0.f;

				// 거리를 확인하고 거리가 초과하면 Move 아니면 slot::Begin()
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
