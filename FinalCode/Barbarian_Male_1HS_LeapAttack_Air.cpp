#include "StdAfx.h"
#include "Barbarian_Male_1HS_LeapAttack_Air.h"

CBarbarian_Male_1HS_LeapAttack_Air::CBarbarian_Male_1HS_LeapAttack_Air(void)
{
	m_eStateType = STATE_TYPE_BARBARIAN_MALE_1HS_LEAPATTACK_AIR;
}

CBarbarian_Male_1HS_LeapAttack_Air::~CBarbarian_Male_1HS_LeapAttack_Air(void)
{
}

void CBarbarian_Male_1HS_LeapAttack_Air::Initialize()
{
	CPlayerState::Initialize();

	// SetAnimation
	m_pOwner->SetAnimation(17);

	// Clear
	m_pPathFindCom->Clear();
	
	// Dist
	if (CInputMgr::GetInstance()->GetPickPos() != NULL)
		m_vDest = *CInputMgr::GetInstance()->GetPickPos();
	else
		m_vDest = m_pTransformCom->m_vPos;

	m_vDist = m_vDest - m_pTransformCom->m_vPos;
	m_vDest.y = 0.0f;
	
	float fLeagth = 0.0f;	
	fLeagth = D3DXVec3Length(&m_vDist);
	
	if (fLeagth >= 450.f )
		fLeagth = 450.f;
	
	m_fLeagth = fLeagth / float( m_pAnimController->m_dFrameTime - 0.15f );	
	D3DXVec3Normalize(&m_vDir , &m_vDist);
		
}

CPlayerState* CBarbarian_Male_1HS_LeapAttack_Air::Action()
{	
	if(!(Equals(m_pTransformCom->m_vPos.x, m_vDest.x, MAX_EPSILON) && Equals(m_pTransformCom->m_vPos.z, m_vDest.z, MAX_EPSILON)))
	{
		vector<CObject*> pFindObjects;
		CDynamicProb* pDynamicProb;
		CNaviCell* pNextCell;
		float fMoveLeagth;

		fMoveLeagth = m_fLeagth	* CTimeMgr::GetInstance()->GetDeltaTime();	 
		D3DXVECTOR3 vNextPos  =	 m_pTransformCom->m_vPos + ( m_vDir * fMoveLeagth);

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
		return new CBarbarian_Male_1HS_LeapAttack_End;	
	}
	return NULL;
}
