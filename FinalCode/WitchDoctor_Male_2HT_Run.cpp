#include "StdAfx.h"
#include "WitchDoctor_Male_2HT_Run.h"

CWitchDoctor_Male_2HT_Run::CWitchDoctor_Male_2HT_Run(int _iSlotPush)
{
	m_eStateType = STATE_TYPE_WITCHDOCTOR_MALE_2HT_RUN;

	// SlotPush
	m_iSlotPush = _iSlotPush;
}

CWitchDoctor_Male_2HT_Run::~CWitchDoctor_Male_2HT_Run(void)
{
}

void CWitchDoctor_Male_2HT_Run::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(12);

	// MoveEnable
	m_pPathFindCom->Enable();
}

CPlayerState* CWitchDoctor_Male_2HT_Run::Action()
{
	if (m_pOwner->GetPickType() != MOUSE_OVER_TYPE_MONSTER)
		return Mode0();
	else
		return Mode1();

	return NULL;
}

CPlayerState* CWitchDoctor_Male_2HT_Run::Mode0()
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
		return new CWitchDoctor_Male_2HT_Idle;
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
			return new CWitchDoctor_Male_2HT_Idle;
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

CPlayerState* CWitchDoctor_Male_2HT_Run::Mode1()
{
	if (m_pOwner->GetPickObject() == NULL)
	{
		return new CWitchDoctor_Male_2HT_Idle;
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
			return new CWitchDoctor_Male_2HT_Idle;
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
				return new CWitchDoctor_Male_2HT_Idle;
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

CPlayerState* CWitchDoctor_Male_2HT_Run::SlotAction(int _iIndex)
{
	if (m_pOwner->GetSlot(_iIndex)->Begin(0) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(m_pOwner->GetSlot(_iIndex)->GetSlotID())
	{

	case SLOT_ID_WITCHDOCTOR_POISON_DART:			// 독침
		return new CWitchDoctor_Male_2HT_Blow;
	case SLOT_ID_WITCHDOCTOR_CORPSE_SPIDERS:		// 시체 거미
		return new CWitchDoctor_Male_2HT_FireBall;
	case SLOT_ID_WITCHDOCTOR_PLAGUE_OF_TOADS:		// 역병 두꺼비
		return new CWitchDoctor_Male_2HT_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_FIREBOMB:				// 불폭탄
		return new CWitchDoctor_Male_2HT_FireBall;
	case SLOT_ID_WITCHDOCTOR_PUNCH:					// 주먹질
		return new CWitchDoctor_Male_2HT_Attack;
	case SLOT_ID_WITCHDOCTOR_NEAR_ATTACK:			// 근거리 공격
		return new CWitchDoctor_Male_2HT_Attack;
	case SLOT_ID_WITCHDOCTOR_FAR_ATTACK:			// 원거리 공격
		return new CWitchDoctor_Male_2HT_Attack;
	case SLOT_ID_WITCHDOCTOR_MAGIC_ATTACK:			// 마법봉 발사
		return new CWitchDoctor_Male_2HT_Attack;
	case SLOT_ID_WITCHDOCTOR_GRASP_OF_THE_DEAD:		// 망자의 손아귀
		return new CWitchDoctor_Male_2HT_FireBall;
	case SLOT_ID_WITCHDOCTOR_FIREBATS:				// 불박쥐
		return new CWitchDoctor_Male_2HT_Channel;
	case SLOT_ID_WITCHDOCTOR_HAUNT:					// 혼령 출몰
		return new CWitchDoctor_Male_2HT_Horrify;
	case SLOT_ID_WITCHDOCTOR_LOCUST_SWARM:			// 메뚜기 떼
		return new CWitchDoctor_Male_2HT_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_SUMMON_ZOMBIE_DOGS:	// 좀비 들개 소환
		return new CWitchDoctor_Male_2HT_Summon;
	case SLOT_ID_WITCHDOCTOR_HORRIFY:				// 공포
		return new CWitchDoctor_Male_2HT_Horrify;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_WALK:			// 혼령 걸음
		return new CWitchDoctor_Male_2HT_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_HEX:					// 주술
		return new CWitchDoctor_Male_2HT_Summon;
	case SLOT_ID_WITCHDOCTOR_SOUL_HARVEST:			// 혼령 수확
		return new CWitchDoctor_Male_2HT_Soul_Harvest;
	case SLOT_ID_WITCHDOCTOR_SACRIFICE:				// 희생
		return new CWitchDoctor_Male_2HT_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_MASS_CONFUSION:		// 대혼란
		return new CWitchDoctor_Male_2HT_Horrify;
	case SLOT_ID_WITCHDOCTOR_ZOMBIE_CHARGER:		// 돌진 좀비
		return new CWitchDoctor_Male_2HT_Summon_Charger;
	case SLOT_ID_WITCHDOCTOR_SPIRIT_BARRAGE:		// 혼령 공세
		return new CWitchDoctor_Male_2HT_FastCast;
	case SLOT_ID_WITCHDOCTOR_ACID_CLOUD:			// 산성 구름
		return new CWitchDoctor_Male_2HT_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_WALL_OF_DEATH:			// 죽음의 벽
		return new CWitchDoctor_Male_2HT_Summon;		
	case SLOT_ID_WITCHDOCTOR_GARGANTUAN:			// 덩치
		return new CWitchDoctor_Male_2HT_Summon;
	case SLOT_ID_WITCHDOCTOR_BIG_BAD_VOODOO:		// 대재앙의 부두술
		return new CWitchDoctor_Male_2HT_AcidCloud_barf;
	case SLOT_ID_WITCHDOCTOR_FETISH_ARMY:			// 우상족 군대
		return new CWitchDoctor_Male_2HT_FlayerArmy;	

	}

	return NULL;
}

bool CWitchDoctor_Male_2HT_Run::IsSlotRange(int _iIndex)
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
