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

	// SetAnimation Mez 기본 애니메이션 
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
	case SLOT_ID_MONK_FISTS_OF_THUNDER:						// 천둥주먹
		return new CMonk_Male_DW_SS_Lightning_01;
	case SLOT_ID_MONK_DEADLY_REACH: 						// 연속 격파
		return new CMonk_Male_DW_SS_LongReach_01;
	case SLOT_ID_MONK_CRIPPLING_WAVE: 						// 마비의 파동
		return new CMonk_Male_DW_SS_DebilitatingBlows_01;
	case SLOT_ID_MONK_WAY_OF_THE_HUNDRED_FISTS: 			// 천지권법
		return new CMonk_Male_DW_SS_RapidStrikes_01;
	case SLOT_ID_MONK_PUNCH: 								// 주먹질
		return new CMonk_Male_DW_SS_Attack_L;
	case SLOT_ID_MONK_NEAR_ATTACK: 							// 근거리 공격
		return new CMonk_Male_DW_SS_Attack_L;
	case SLOT_ID_MONK_FAR_ATTACK: 							// 원거리 공격
		break;
	case SLOT_ID_MONK_MAGIC_ATTACK: 						// 마법봉 발사
		break;	
	case SLOT_ID_MONK_LASHING_TAIL_KICK: 					// 반달차기
		return new CMonk_Male_DW_SS_LashingTail;	
	case SLOT_ID_MONK_TEMPEST_RUSH: 						// 폭풍 질주
		return new CMonk_Male_DW_SS_Hobble_Run(_iIndex);
	case SLOT_ID_MONK_WAVE_OF_LIGHT: 						// 빛의 파동
		return new CMonk_Male_DW_SS_WaveofLight;	
	case SLOT_ID_MONK_BLINDING_FLASH: 						// 눈부신 섬광
		return new CMonk_Male_DW_SS_Buff;
	case SLOT_ID_MONK_BREATH_OF_HEAVEN: 					// 천상의 숨결
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_SERENITY: 							// 평안
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_INNER_SANCTUARY: 						// 내면의 안식처
		return new CMonk_Male_DW_SS_Buff;		
	case SLOT_ID_MONK_DASHING_STRIKE: 						// 진격타
		return new CMonk_Male_DW_SS_DashingStrike;	
	case SLOT_ID_MONK_EXPLODING_PALM: 						// 폭발 장법
		return new CMonk_Male_DW_SS_Attack_L;	
	case SLOT_ID_MONK_SWEEPING_WIND: 						// 휘몰이
		return new CMonk_Male_DW_SS_CelestialWheel;
	case SLOT_ID_MONK_CYCLONE_STRIKE: 						// 용오름
		return new CMonk_Male_DW_SS_Lethal_Decoy;
	case SLOT_ID_MONK_SEVEN_SIDED_STRIKE: 					// 칠면 공격
		return new CMonk_Male_DW_SS_Buff;
	case SLOT_ID_MONK_MYSTIC_ALLY: 							// 신기한 벗
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_SALVATION: 					// 구원의 진언
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION: 				// 응보의 진언
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_HEALING: 					// 치유의 진언
		return new CMonk_Male_DW_SS_Buff;	
	case SLOT_ID_MONK_MANTRA_OF_CONVICTION: 				// 신념의 진언
		return new CMonk_Male_DW_SS_Buff;	
	}



	return NULL;
}

bool CMonk_Male_DW_SS_Mez::IsSlotRange(int _iIndex)
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
