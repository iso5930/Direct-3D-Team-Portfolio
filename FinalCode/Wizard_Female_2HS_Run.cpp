#include "StdAfx.h"
#include "Wizard_Female_2HS_Run.h"

CWizard_Female_2HS_Run::CWizard_Female_2HS_Run(int _iSlotPush)
{
	m_eStateType = STATE_TYPE_WIZARD_FEMALE_2HS_RUN;

	// SlotPush
	m_iSlotPush = _iSlotPush;

}

CWizard_Female_2HS_Run::~CWizard_Female_2HS_Run(void)
{
}

void CWizard_Female_2HS_Run::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(25);

	// PathFinCom
	m_pPathFindCom->Enable();
}

CPlayerState* CWizard_Female_2HS_Run::Action()
{
	if (m_pOwner->GetPickType() != MOUSE_OVER_TYPE_MONSTER)
		return Mode0();
	else
		return Mode1();


	return NULL;
}

CPlayerState* CWizard_Female_2HS_Run::Mode0()
{
	// Dir
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

		if(fDotX > 0.0f)
			m_pTransformCom->m_vAngle.y += acosf(fDotZ);
		else
			m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
	}

	// If CurPos is DstPos.. return
	if(Equals(m_pPathFindCom->m_vDst.x, m_pTransformCom->m_vPos.x, MAX_EPSILON) && Equals(m_pPathFindCom->m_vDst.z, m_pTransformCom->m_vPos.z, MAX_EPSILON))
	{
		PickObjectEvent();
		return new CWizard_Female_2HS_Idle;
	}

	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(iSlotNum == -1)
	{	
		m_pOwner->SetLastPushSlotNum(iSlotNum);
		return NULL;
	}

	// Move
	if(iSlotNum == 4 && false == (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
	{
		int iPickType = CPlayerState::OverObjectPick(); 
		if(iPickType == MOUSE_OVER_TYPE_END)
		{
			return new CWizard_Female_2HS_Idle;
		}
		else if (iPickType == MOUSE_OVER_TYPE_MONSTER)
		{

		}
		else
		{				
			return NULL;
		}
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return NULL;
}

CPlayerState* CWizard_Female_2HS_Run::Mode1()
{
	if (m_pOwner->GetPickObject() == NULL)
	{
		return new CWizard_Female_2HS_Idle;
	}

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

		if(fDotX > 0.0f)
			m_pTransformCom->m_vAngle.y += acosf(fDotZ);
		else
			m_pTransformCom->m_vAngle.y -= acosf(fDotZ);
	}

	CTransformCom* pTransform =  (CTransformCom*)m_pOwner->GetPickObject()->GetComponent(COM_TYPE_TRANSFORM);
	D3DXVECTOR3 vLength = m_pTransformCom->m_vPos - pTransform->m_vPos;
	vLength.y = 0.f;

	if (m_pOwner->GetLastPushSlotNum() != -1  && D3DXVec3Length( &vLength ) <= m_pOwner->GetSlot(m_pOwner->GetLastPushSlotNum())->GetRange() )
	{

		CPlayerState* pPlayerState = SlotAction(m_pOwner->GetLastPushSlotNum());

		if (pPlayerState == NULL)
		{
			return new CWizard_Female_2HS_Idle;
		}

		return pPlayerState;
	}

	// Find Priority Key and SlotNo
	int iSlotNum = CPlayerState::UsingKeyMouse();

	// If None Input..
	if(iSlotNum == -1)
	{
		m_pPathFindCom->Move(&pTransform->m_vPos);
		return NULL;
	}
	// Move
	if(iSlotNum == 4 && false == (CInputMgr::GetInstance()->KeyDown(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_LSHIFT) || CInputMgr::GetInstance()->KeyDown(DIK_RSHIFT) || CInputMgr::GetInstance()->KeyPress(DIK_RSHIFT)))
	{
		if (m_pOwner->GetLastPushSlotNum() !=  iSlotNum)
		{
			int iPickType = CPlayerState::OverObjectPick(); 
			if(iPickType == MOUSE_OVER_TYPE_END)
			{
				return new CWizard_Female_2HS_Idle;
			}
			else if (iPickType == MOUSE_OVER_TYPE_MONSTER)
			{

			}
			else
			{				
				return NULL;
			}
		}
	}

	if (IsSlotRange(iSlotNum))
		return SlotAction(iSlotNum);
	else
		return NULL;
}

CPlayerState* CWizard_Female_2HS_Run::SlotAction(int _iIndex)
{
	if(m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch (m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{
	case 	SLOT_ID_WIZARD_MAGIC_MISSILE:					// 마력탄
		return  new CWizard_Female_2HS_Attack; 

	case	SLOT_ID_WIZARD_SHOCK_PULSE:						// 전기 충격
		return new CWizard_Female_2HS_Directed;  

	case	SLOT_ID_WIZARD_SPECTRAL_BLADE:					// 저승의 칼날
		return new CWizard_Female_2HS_AOE;

	case	SLOT_ID_WIZARD_ELECTROCUTE:						// 감전
		return new CWizard_Female_2HS_Channel(_iIndex);

	case	SLOT_ID_WIZARD_PUNCH:							// 주먹질
		return NULL;	

	case	SLOT_ID_WIZARD_NEAR_ATTACK:						// 근거리 공격
		return new CWizard_Female_2HS_Attack;

	case	SLOT_ID_WIZARD_FAR_ATTACK:						// 원거리 공격
		return NULL;

	case	SLOT_ID_WIZARD_MAGIC_ATTACK:					// 마법봉 발사
		return NULL;

	case	SLOT_ID_WIZARD_RAY_OF_FROST:					// 서리 광선			
		return new CWizard_Female_2HS_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_ARCANE_ORB:						// 비전 보주	
		return new CWizard_Female_2HS_Directed;				

	case	SLOT_ID_WIZARD_ARCANE_TORRENT:					// 비전 격류	
		return new CWizard_Female_2HS_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_DISINTEGRATE:					// 파열					
		return new CWizard_Female_2HS_Channel(_iIndex);		

	case	SLOT_ID_WIZARD_FROST_NOVA:						// 서릿발	
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_DIAMOND_SKIN:					// 다이아몬드 피부		
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_SLOW_TIME:						// 감속 지대			
		return new CWizard_Female_2HS_Summon;				

	case	SLOT_ID_WIZARD_TELEPORT:						// 순간이동	
		return new CWizard_Female_2HS_Teleport;				

	case	SLOT_ID_WIZARD_WAVE_OF_FORCE:					// 힘의 파동			
		return new CWizard_Female_2HS_AOE2;						

	case	SLOT_ID_WIZARD_ENERGY_TWISTER:					// 마력 돌개 바람		
		return new CWizard_Female_2HS_AOE;						

	case	SLOT_ID_WIZARD_HYDRA:							// 히드라				
		return new CWizard_Female_2HS_Summon;				

	case	SLOT_ID_WIZARD_METEOR:							// 운석 낙하			
		return new CWizard_Female_2HS_AOE;					

	case	SLOT_ID_WIZARD_BLIZZARD:						// 눈보라				
		return new CWizard_Female_2HS_Summon;				

	case	SLOT_ID_WIZARD_ICE_ARMOR:						// 얼음 갑옷
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_STORM_ARMOR:						// 천둥 갑옷
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_MAGIC_WEAPON:					// 마법 무기
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_FAMILIAR:						// 사역마
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_ENERGY_ARMOR:					// 마력 갑옷	
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_EXPLOSIVE_BLAST:					// 에너지 폭발
		KeyMouseStop(_iIndex);
		return NULL;

	case	SLOT_ID_WIZARD_MIRROR_IMAGE:					// 분신
		return new CWizard_Female_2HS_Summon;				

	case	SLOT_ID_WIZARD_ARCHON:							// 마인		
		return new CWizard_Female_2HS_Summon;				

	}

	return NULL;

}

bool CWizard_Female_2HS_Run::IsSlotRange(int _iIndex)
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
