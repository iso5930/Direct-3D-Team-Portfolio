#include "StdAfx.h"
#include "Wizard_Female_Bow_Channel.h"

CWizard_Female_Bow_Channel::CWizard_Female_Bow_Channel(int _iPushSlot)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_BOW_CHANNEL;

	// PushSlot
	m_iPushSlot = _iPushSlot;

	// Mode
	m_iMode = 0;

	// Time
	m_fTime = 0.f;
}

CWizard_Female_Bow_Channel::~CWizard_Female_Bow_Channel(void)
{
	m_pOwner->GetSlot(m_iPushSlot)->End();

	if (m_iMode == 1)
	{
		m_pOwner->SetAnimationMode(0);
	}
}

void CWizard_Female_Bow_Channel::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(13);

	// Clear
	m_pPathFindCom->Clear();
}
CPlayerState* CWizard_Female_Bow_Channel::Action()
{
	if(m_pAnimController->m_dFrameTime - 0.25 <= m_pAnimController->GetTrackPos())
	{
		return new CWizard_Female_Bow_Idle;	
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

CPlayerState* CWizard_Female_Bow_Channel::Mode0()
{
	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(m_pOwner->GetLastPushSlotNum() == iSlotNum)
	{
		if(m_pOwner->GetSlot(iSlotNum)->Action() == SLOT_RESULT_NULL)
		{
			//애니메이션 멈춤시간
			if (0.311 > m_pAnimController->GetTrackPos())
				return NULL;

			m_pOwner->SetAnimationMode(2);
			++m_iMode;
		}
		else
		{
			return new CWizard_Female_Bow_Idle;
		}

		return NULL;
	}

	if ( -1 == iSlotNum )
	{
		return new CWizard_Female_Bow_Idle;
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return new CWizard_Female_Bow_Run(m_pOwner->GetLastPushSlotNum());
};

CPlayerState* CWizard_Female_Bow_Channel::Mode1()
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
			return new CWizard_Female_1HS_Idle;
		}
	}

	if ( -1 == iSlotNum )
	{
		return new CWizard_Female_1HS_Idle;
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return new CWizard_Female_1HS_Run(m_pOwner->GetLastPushSlotNum());
}

CPlayerState* CWizard_Female_Bow_Channel::SlotAction(int _iIndex)
{
	CSlot* pSlot = m_pOwner->GetSlot(_iIndex);

	if(pSlot->Begin(_iIndex) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(pSlot->GetSlotID())
	{
	case 	SLOT_ID_WIZARD_MAGIC_MISSILE:						// 마력탄	
		return new CWizard_Female_Bow_Attack;					
																
	case	SLOT_ID_WIZARD_SHOCK_PULSE:							// 전기 충격
		return new CWizard_Female_Bow_Directed;			
																
	case	SLOT_ID_WIZARD_SPECTRAL_BLADE:						// 저승의 칼날
		return new CWizard_Female_Bow_AOE;						
																
	case	SLOT_ID_WIZARD_ELECTROCUTE:							// 감전
		return new CWizard_Female_Bow_Channel(_iIndex);			
																
	case	SLOT_ID_WIZARD_PUNCH:								// 주먹질
		return NULL;											
																
	case	SLOT_ID_WIZARD_NEAR_ATTACK:							// 근거리 공격
		return NULL;											
																
	case	SLOT_ID_WIZARD_FAR_ATTACK:							// 원거리 공격
		return new CWizard_Female_Bow_Range_Attack;				
																
	case	SLOT_ID_WIZARD_MAGIC_ATTACK:						// 마법봉 발사
		return NULL;											
																
	case	SLOT_ID_WIZARD_RAY_OF_FROST:						// 서리 광선	
		return new CWizard_Female_Bow_Channel(_iIndex);			
																
	case	SLOT_ID_WIZARD_ARCANE_ORB:							// 비전 보주	
		return new CWizard_Female_Bow_Directed;					
																
	case	SLOT_ID_WIZARD_ARCANE_TORRENT:						// 비전 격류	
		return new CWizard_Female_Bow_Channel(_iIndex);			
																
	case	SLOT_ID_WIZARD_DISINTEGRATE:						// 파열			
		return new CWizard_Female_Bow_Channel(_iIndex);			
																
	case	SLOT_ID_WIZARD_FROST_NOVA:							// 서릿발	
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_DIAMOND_SKIN:						// 다이아몬드 
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_SLOW_TIME:							// 감속 지대	
		return new CWizard_Female_Bow_Summon;					
																
	case	SLOT_ID_WIZARD_TELEPORT:							// 순간이동	
		return new CWizard_Female_Bow_Teleport;					
																
	case	SLOT_ID_WIZARD_WAVE_OF_FORCE:						// 힘의 파동	
		return new CWizard_Female_Bow_AOE2;							
																
	case	SLOT_ID_WIZARD_ENERGY_TWISTER:						// 마력 돌개 바
		return new CWizard_Female_Bow_AOE;							
																
	case	SLOT_ID_WIZARD_HYDRA:								// 히드라		
		return new CWizard_Female_Bow_Summon;					
																
	case	SLOT_ID_WIZARD_METEOR:								// 운석 낙하	
		return new CWizard_Female_Bow_AOE;						
																
	case	SLOT_ID_WIZARD_BLIZZARD:							// 눈보라		
		return new CWizard_Female_Bow_Summon;					
																
	case	SLOT_ID_WIZARD_ICE_ARMOR:							// 얼음 갑옷
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_STORM_ARMOR:							// 천둥 갑옷
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_MAGIC_WEAPON:						// 마법 무기
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_FAMILIAR:							// 사역마
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_ENERGY_ARMOR:						// 마력 갑옷	
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_EXPLOSIVE_BLAST:						// 에너지 폭발
		KeyMouseStop(_iIndex);
		return NULL;											
																
	case	SLOT_ID_WIZARD_MIRROR_IMAGE:						// 분신
		return new CWizard_Female_Bow_Summon;					
																
	case	SLOT_ID_WIZARD_ARCHON:								// 마인		
		return new CWizard_Female_Bow_Summon;					
	}															
																
	return NULL;												
}																
																
bool CWizard_Female_Bow_Channel::IsSlotRange(int _iIndex)
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

			CPlayerState::AttackMode();
			return false;
		}
	}
	return true;
}
