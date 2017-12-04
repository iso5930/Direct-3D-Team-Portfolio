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

	// SetAnimation Mez 기본 애니메이션 
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
	case 	SLOT_ID_WIZARD_MAGIC_MISSILE:					// 마력탄
		return  new CWizard_Female_STF_Attack; 

	case	SLOT_ID_WIZARD_SHOCK_PULSE:						// 전기 충격
		return new CWizard_Female_STF_Directed;  

	case	SLOT_ID_WIZARD_SPECTRAL_BLADE:					// 저승의 칼날
		return new CWizard_Female_STF_AOE;

	case	SLOT_ID_WIZARD_ELECTROCUTE:						// 감전
		return new CWizard_Female_STF_Channel(_iIndex);

	case	SLOT_ID_WIZARD_PUNCH:							// 주먹질
		return new CWizard_Female_STF_Attack;	

	case	SLOT_ID_WIZARD_NEAR_ATTACK:						// 근거리 공격
		return new CWizard_Female_STF_Attack;

	case	SLOT_ID_WIZARD_FAR_ATTACK:						// 원거리 공격
		return NULL;

	case	SLOT_ID_WIZARD_MAGIC_ATTACK:					// 마법봉 발사
		return  new CWizard_Female_STF_Attack; 

	case	SLOT_ID_WIZARD_RAY_OF_FROST:					// 서리 광선			
		return new CWizard_Female_STF_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_ARCANE_ORB:						// 비전 보주	
		return new CWizard_Female_STF_Directed;				

	case	SLOT_ID_WIZARD_ARCANE_TORRENT:					// 비전 격류	
		return new CWizard_Female_STF_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_DISINTEGRATE:					// 파열					
		return new CWizard_Female_STF_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_FROST_NOVA:						// 서릿발				
		return new CWizard_Female_STF_AOE;					

	case	SLOT_ID_WIZARD_DIAMOND_SKIN:					// 다이아몬드 피부		
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_SLOW_TIME:						// 감속 지대			
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_TELEPORT:						// 순간이동	
		return new CWizard_Female_STF_Teleport;				

	case	SLOT_ID_WIZARD_WAVE_OF_FORCE:					// 힘의 파동			
		return new CWizard_Female_STF_AOE2;						

	case	SLOT_ID_WIZARD_ENERGY_TWISTER:					// 마력 돌개 바람		
		return new CWizard_Female_STF_AOE;						

	case	SLOT_ID_WIZARD_HYDRA:							// 히드라				
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_METEOR:							// 운석 낙하			
		return new CWizard_Female_STF_AOE;					

	case	SLOT_ID_WIZARD_BLIZZARD:						// 눈보라				
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_ICE_ARMOR:						// 얼음 갑옷
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_STORM_ARMOR:						// 천둥 갑옷
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_MAGIC_WEAPON:					// 마법 무기
		return new CWizard_Female_STF_AOE;					

	case	SLOT_ID_WIZARD_FAMILIAR:						// 사역마
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_ENERGY_ARMOR:					// 마력 갑옷	
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_EXPLOSIVE_BLAST:					// 에너지 폭발
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_MIRROR_IMAGE:					// 분신
		return new CWizard_Female_STF_Summon;				

	case	SLOT_ID_WIZARD_ARCHON:							// 마인		
		return new CWizard_Female_STF_Summon;				

	}

	return NULL;
}

bool CWizard_Female_STF_Mez::IsSlotRange(int _iIndex)
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
