#include "StdAfx.h"
#include "Barbarian_Male_2HS_Furious_Charge_Loop.h"

CBarbarian_Male_2HS_Furious_Charge_Loop::CBarbarian_Male_2HS_Furious_Charge_Loop(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_2HS_FURIOUS_CHARGE_LOOP;
}

CBarbarian_Male_2HS_Furious_Charge_Loop::~CBarbarian_Male_2HS_Furious_Charge_Loop(void)
{
}

void CBarbarian_Male_2HS_Furious_Charge_Loop::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(71);

	// Clear
	m_pPathFindCom->Clear();


	// Dist
	if (CInputMgr::GetInstance()->GetPickPos() != NULL)
		m_vDest = *CInputMgr::GetInstance()->GetPickPos();
	else
		m_vDest = m_pTransformCom->m_vPos;

	m_vDist = m_vDest - m_pTransformCom->m_vPos;


	float fLeagth = 0.0f;	
	fLeagth = D3DXVec3Length(&m_vDist);

	if (fLeagth >= 450.f )
		fLeagth = 450.f;

	m_fLeagth = fLeagth / float( m_pAnimController->m_dFrameTime - 0.15 ) ;	
	D3DXVec3Normalize(&m_vDir , &m_vDist);
}

CPlayerState* CBarbarian_Male_2HS_Furious_Charge_Loop::Action()
{
	if(!(Equals(m_pTransformCom->m_vPos.x, m_vDest.x, MAX_EPSILON) && Equals(m_pTransformCom->m_vPos.z, m_vDest.z, MAX_EPSILON)))
	{
		vector<CObject*> pFindObjects;
		CDynamicProb* pDynamicProb;
		CNaviCell* pNextCell;
		float fMoveLeagth;

		fMoveLeagth = m_fLeagth	* CTimeMgr::GetInstance()->GetDeltaTime();	 

		D3DXVECTOR3 vNextPos  =	  m_pTransformCom->m_vPos + ( m_vDir * fMoveLeagth);

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

		}pFindObjects.clear();
	}

	if(m_pAnimController->m_dFrameTime - 0.15 <= m_pAnimController->GetTrackPos())
	{
		return new CBarbarian_Male_2HS_LeapAttack_End;	
	}
	return NULL;
}
