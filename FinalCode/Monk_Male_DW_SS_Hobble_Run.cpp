#include "StdAfx.h"
#include "Monk_Male_DW_SS_Hobble_Run.h"

CMonk_Male_DW_SS_Hobble_Run::CMonk_Male_DW_SS_Hobble_Run(int _iPushSlot)
{
	m_eStateType = STATE_TYPE_MONK_MALE_DW_SS_HOBBLE_RUN;

	m_iPushSlot = _iPushSlot;

	m_iMode = 0;	
}

CMonk_Male_DW_SS_Hobble_Run::~CMonk_Male_DW_SS_Hobble_Run(void)
{
	m_pOwner->GetSlot(m_iPushSlot)->End();
}

void CMonk_Male_DW_SS_Hobble_Run::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(56);

	// Clear
	m_pPathFindCom->Clear();
}

CPlayerState* CMonk_Male_DW_SS_Hobble_Run::Action()
{
	switch(m_iMode)
	{
	case 0:
		return Mode0();

	case 1:
		return Mode1();
	}

	return NULL;
}

CPlayerState* CMonk_Male_DW_SS_Hobble_Run::Mode0()
{
	int iSlotNum = CPlayerState::UsingKeyMouse();

	if (iSlotNum == -1)
	{
		m_iMode = 1;
	}
	else if (iSlotNum == m_iPushSlot)
	{
		if(m_pOwner->GetSlot(m_iPushSlot)->Action() != SLOT_RESULT_NULL)
		{
			m_iMode = 1;
		}
	}
	else
	{
		CPlayerState* pState = SlotAction(iSlotNum);
		if (pState != NULL)
		{
			return pState;
		}
	}

	if (CInputMgr::GetInstance()->GetPickPos() != NULL)
	{
		vector<CObject*> pFindObjects;
		CDynamicProb* pDynamicProb;
		CNaviCell* pNextCell;

		D3DXVECTOR3 vDir = *CInputMgr::GetInstance()->GetPickPos() - m_pTransformCom->m_vPos;
		D3DXVec3Normalize(&vDir , &vDir);

		D3DXVECTOR3 vNextPos  =	 m_pTransformCom->m_vPos + ( vDir * CTimeMgr::GetInstance()->GetDeltaTime() * 300.f);

		m_pOwner->GetLayer()->FindObjects(pFindObjects, _T("DynamicProb"), LAYER_TYPE_DYNAMIC_PROB);
		for(size_t i = 0; i < pFindObjects.size(); ++i)
		{
			pDynamicProb = (CDynamicProb*)pFindObjects[i];

			pDynamicProb->Intersect(&m_pTransformCom->m_vPos ,m_pPathFindCom->m_pCell , &vNextPos , &pNextCell );
			m_pTransformCom->m_vPos = vNextPos;
			m_pPathFindCom->m_pCell = pNextCell;

		}
		pFindObjects.clear();
	}

	return NULL;
}

CPlayerState* CMonk_Male_DW_SS_Hobble_Run::Mode1()
{
	return new CMonk_Male_DW_SS_Idle;	
}

CPlayerState* CMonk_Male_DW_SS_Hobble_Run::SlotAction(int _iIndex)
{
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
		KeyMouseStop(_iIndex);
		break;
	case SLOT_ID_MONK_BREATH_OF_HEAVEN: 					// õ���� ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_SERENITY: 							// ���	
		KeyMouseStop(_iIndex);
		break;	
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
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_SALVATION: 					// ������ ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_RETRIBUTION: 				// ������ ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_HEALING: 					// ġ���� ����	
		KeyMouseStop(_iIndex);
		break;	
	case SLOT_ID_MONK_MANTRA_OF_CONVICTION: 				// �ų��� ����	
		KeyMouseStop(_iIndex);
		break;	
	}

	return NULL;	
}
