#include "StdAfx.h"
#include "DemonHunter_Female_Bow_Strafe.h"

CDemonHunter_Female_Bow_Strafe::CDemonHunter_Female_Bow_Strafe(int _iPushSlot)
{
	// StateType
	m_eStateType = STATE_TYPE_DEMONHUNTER_FEMALE_BOW_STRAFE;

	m_iPushSlot = _iPushSlot;

	m_iMode = 0;	
}

CDemonHunter_Female_Bow_Strafe::~CDemonHunter_Female_Bow_Strafe()
{
	m_pOwner->GetSlot(m_iPushSlot)->End();
}

void CDemonHunter_Female_Bow_Strafe::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(33);

	// Clear
	m_pPathFindCom->Clear();

}

CPlayerState* CDemonHunter_Female_Bow_Strafe::Action()
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

CPlayerState* CDemonHunter_Female_Bow_Strafe::Mode0()
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

		CStaticProb* pStaticProb;
		m_pOwner->GetLayer()->FindObjects(pFindObjects, _T("StaticProb"), LAYER_TYPE_STATIC_PROB);
		for(size_t i = 0; i < pFindObjects.size(); ++i)
		{
			pStaticProb = (CStaticProb*)pFindObjects[i];

			pStaticProb->Intersect(&m_pTransformCom->m_vPos ,m_pPathFindCom->m_pCell , &vNextPos , &pNextCell );
			m_pTransformCom->m_vPos = vNextPos;
			m_pPathFindCom->m_pCell = pNextCell;

		}
		pFindObjects.clear();
	}

	return NULL;
}

CPlayerState* CDemonHunter_Female_Bow_Strafe::Mode1()
{
	return new CDemonHunter_Female_Bow_Idle;
}

CPlayerState* CDemonHunter_Female_Bow_Strafe::SlotAction(int _iIndex)
{
	CSlot* pSlot = m_pOwner->GetSlot(_iIndex);

	//������ 0   �޼� 1
	if(pSlot->Begin(1) != SLOT_RESULT_NULL)
	{
		return NULL;
	}

	switch(pSlot->GetSlotID())
	{
	case  SLOT_ID_DEMONHUNTER_PUNCH:
		return NULL;

	case SLOT_ID_DEMONHUNTER_GRENADES:
		return new CDemonHunter_Female_Bow_Impale;

	case SLOT_ID_DEMONHUNTER_CHAKRAM:
		return new CDemonHunter_Female_Bow_Impale;

	case SLOT_ID_DEMONHUNTER_FAR_ATTACK:
		return new CDemonHunter_Female_Bow_Attack;		

	case SLOT_ID_DEMONHUNTER_NEAR_ATTACK:
		return NULL;

	case SLOT_ID_DEMONHUNTER_MAGIC_ATTACK:
		return NULL;			

	case SLOT_ID_DEMONHUNTER_SMOKE_SCREEN: // ����
		return NULL;			

	case SLOT_ID_DEMONHUNTER_SHADOW_POWER: // �������
		return NULL;			

	case SLOT_ID_DEMONHUNTER_PREPARATION: // �����غ�
		return NULL;			

	case SLOT_ID_DEMONHUNTER_VAULT:  // ����
		return new CDemonHunter_Female_Bow_BackFlip;

	case SLOT_ID_DEMONHUNTER_COMPANION: // �����ȯ
		return new CDemonHunter_Female_Bow_Companion;

	case SLOT_ID_DEMONHUNTER_MARKED_FOR_DEATH: // ������ ǥ��
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_SENTRY: // �ڵ����
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_FAN_OF_KNIVES:	//��ä
		return NULL;			

	case SLOT_ID_DEMONHUNTER_IMPALE:	//����
		return new CDemonHunter_Female_Bow_Impale;

	case SLOT_ID_DEMONHUNTER_CALTROPS: // ��� ��
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_SPIKE_TRAP: // ���� ��
		return new CDemonHunter_Female_Bow_Caltrop;

	case SLOT_ID_DEMONHUNTER_HUNGERING_ARROW:
		return new CDemonHunter_Female_Bow_Attack;

	case SLOT_ID_DEMONHUNTER_ENTANGLING_SHOT:
		return new CDemonHunter_Female_Bow_Attack;

	case SLOT_ID_DEMONHUNTER_BOLA:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_EVASIVE_FIRE:
		return new CDemonHunter_Female_Bow_Attack;

	case SLOT_ID_DEMONHUNTER_RAPID_FIRE:
		return new CDemonHunter_Female_Bow_BolaSlot(_iIndex);

	case SLOT_ID_DEMONHUNTER_ELEMENTAL_ARROW:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_MULTISHOT:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_CLUSTER_ARROW:
		return new CDemonHunter_Female_Bow_MultiShot;

	case SLOT_ID_DEMONHUNTER_RAIN_OF_VENGEANCE:
		return new CDemonHunter_Female_Bow_RainOfArrow;

	case SLOT_ID_DEMONHUNTER_STRAFE:
		return new CDemonHunter_Female_Bow_Strafe(_iIndex);
	}
	return  NULL;
}